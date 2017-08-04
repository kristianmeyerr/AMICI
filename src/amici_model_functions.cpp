#include "include/amici_model_functions.h"

#include "include/amici.h"
#include <cstring>

int fsy(int it, UserData *udata, TempData *tdata, ReturnData *rdata){
    // Compute sy = dydx * sx + dydp

    int status = AMICI_SUCCESS;

    for(int ip = 0; ip < udata->nplist; ++ip) {
        for(int iy = 0; iy < udata->ny; ++iy)
            // copy dydp to sy
            rdata->sy[ip * udata->nt * udata->ny + iy * udata->nt + it] = tdata->dydp[iy + ip * udata->ny];

        realtype *sx_tmp = N_VGetArrayPointer(tdata->sx[ip]);

        // compute sy = 1.0*dydx*sx + 1.0*sy
        amici_dgemv(AMICI_BLAS_ColMajor, AMICI_BLAS_NoTrans, udata->ny, udata->nx,
                    1.0, tdata->dydx, udata->ny, sx_tmp, 1,
                    1.0, &rdata->sy[it + ip * udata->nt * udata->ny], udata->nt);
    }

    return status;
}

int fsz_tf(int ie, UserData *udata, TempData *tdata, ReturnData *rdata){
    // Compute sz = dzdx * sz + dzdp

    int status = AMICI_SUCCESS;

    for(int ip = 0; ip < udata->nplist; ++ip) {
        for(int iz = 0; iz < udata->nz; ++iz)
            // copy dydp to sy
            rdata->sz[tdata->nroots[ie] + (iz + ip * udata->nz) * udata->nmaxevent ] = 0;
    }

    return status;
}

int fsJy(int it, UserData *udata, TempData *tdata, const ExpData *edata, ReturnData *rdata) {
    int status = AMICI_SUCCESS;

    // Compute dJydx*sx for current 'it'
    // dJydx        nt x nJ x nx
    // sx           nt x nx x nplist

    double *multResult = new double[udata->nJ * udata->nplist];
    double *dJydxTmp = new double[udata->nJ * udata->nx];
    double *sxTmp = new double[udata->nplist * udata->nx];
    for(int ix = 0; ix < udata->nx; ++ix){
        for(int ip = 0; ip < udata->nplist; ++ip)
            sxTmp[ix + ip * udata->nx] = rdata->sx[it + (ix + ip * udata->nx ) * udata->nt];
        for(int iJ = 0; iJ < udata->nJ; ++iJ)
            dJydxTmp[iJ + ix * udata->nJ] = tdata->dJydx[it + (iJ + ix * udata->nJ ) * udata->nt];
    }

    // C := alpha*op(A)*op(B) + beta*C,
    amici_dgemm(AMICI_BLAS_ColMajor, AMICI_BLAS_NoTrans, AMICI_BLAS_NoTrans,
                udata->nJ, udata->nplist, udata->nx,
                1.0, dJydxTmp, udata->nJ,
                sxTmp, udata->nx,
                0.0, multResult, udata->nJ);

    // multResult    nJ x nplist
    // dJydp         nJ x nplist
    // dJydxTmp      nJ x nx
    // sxTmp         nx x nplist

    // sJy += multResult + dJydp
    for(int iJ = 0; iJ < udata->nJ; ++iJ) {
        if (iJ == 0)
            for(int ip = 0; ip < udata->nplist; ++ip)
                rdata->sllh[ip] -= multResult[ip * udata->nJ] + tdata->dJydp[ip * udata->nJ];
        else
            for(int ip = 0; ip < udata->nplist; ++ip)
                rdata->s2llh[(iJ - 1) + ip * (udata->nJ-1) ] -= multResult[iJ + ip * udata->nJ] + tdata->dJydp[iJ + ip * udata->nJ];
    }

    delete[] dJydxTmp;
    delete[] multResult;
    delete[] sxTmp;

    return(status);
}

int fdJydp(int it, UserData *udata, TempData *tdata, const ExpData *edata, ReturnData *rdata) {
    int status = AMICI_SUCCESS;

    // dJydy         nytrue x nJ x ny
    // dydp          ny x nplist
    // dJydp         nJ x nplist

    memset(tdata->dJydp,0,udata->nJ * udata->nplist * sizeof(double));

    realtype *dJydyTmp = new double[udata->nJ * udata->ny];
    realtype *dJydsigmaTmp = new double[udata->nJ * udata->ny];

    for(int iyt=0; iyt < udata->nytrue; ++iyt) {
        if (amiIsNaN(edata->my[udata->nt * iyt + it]))
            continue;

        // copy current (iyt) dJydy and dJydsigma slices
        // dJydyTmp     nJ x ny
        // dJydsigmaTmp nJ x ny
        for(int iJ = 0; iJ < udata->nJ; ++iJ) {
            for(int iy = 0; iy < udata->ny; ++iy) {
                dJydyTmp[iJ + iy * udata->nJ] = tdata->dJydy[iyt + (iJ + iy * udata->nJ) * udata->nytrue];
                dJydsigmaTmp[iJ + iy * udata->nJ] = tdata->dJydsigma[iyt + (iJ  + iy * udata->nJ) * udata->nytrue];
            }
        }

        amici_dgemm(AMICI_BLAS_ColMajor, AMICI_BLAS_NoTrans, AMICI_BLAS_NoTrans,
                    udata->nJ, udata->nplist, udata->ny,
                    1.0, dJydyTmp, udata->nJ,
                    tdata->dydp, udata->ny,
                    1.0, tdata->dJydp, udata->nJ);

        amici_dgemm(AMICI_BLAS_ColMajor, AMICI_BLAS_NoTrans, AMICI_BLAS_NoTrans,
                    udata->nJ, udata->nplist, udata->ny,
                    1.0, dJydsigmaTmp, udata->nJ,
                    tdata->dsigmaydp, udata->ny,
                    1.0, tdata->dJydp, udata->nJ);
    }
    delete[] dJydyTmp;
    delete[] dJydsigmaTmp;

    return(status);
}

int fdJydx(int it, UserData *udata, TempData *tdata, const ExpData *edata) {
    int status = AMICI_SUCCESS;

    // dJydy         nytrue x nJ x ny
    // dydx          ny x nx
    // dJydx         nt x nJ x nx

    realtype *dJydyTmp = new realtype[udata->nJ * udata->ny];
    realtype *multResult = new realtype[udata->nJ * udata->nx]();

    for(int iyt=0; iyt < udata->nytrue; ++iyt) {
        if (amiIsNaN(edata->my[udata->nt * iyt + it]))
            continue;

        // copy current (iyt) dJydy slice
        // dJydyTmp     nJ x ny
        for(int iJ = 0; iJ < udata->nJ; ++iJ)
            for(int iy = 0; iy < udata->ny; ++iy)
                dJydyTmp[iJ + iy * udata->nJ] = tdata->dJydy[iyt + (iJ + iy * udata->nJ) * udata->nytrue];

        amici_dgemm(AMICI_BLAS_ColMajor, AMICI_BLAS_NoTrans, AMICI_BLAS_NoTrans,
                    udata->nJ, udata->nx, udata->ny,
                    1.0, dJydyTmp, udata->nJ,
                    tdata->dydx, udata->ny,
                    1.0, multResult, udata->nJ);
    }
    for(int iJ = 0; iJ < udata->nJ; ++iJ)
        for(int ix = 0; ix < udata->nx; ++ix)
            tdata->dJydx[it + (iJ + ix * udata->nJ) * udata->nt] = multResult[iJ + ix * udata->nJ];

    delete[] dJydyTmp;
    delete[] multResult;

    return(status);
}

int fsJz(int ie, UserData *udata, TempData *tdata, const ExpData *edata, ReturnData *rdata) {
    int status = AMICI_SUCCESS;

    // sJz           nJ x nplist
    // dJzdp         nJ x nplist
    // dJzdx         nmaxevent x nJ x nx
    // sx            nt x nx x nplist

    // Compute dJzdx*sx for current 'ie'
    // dJzdx        nt x nJ x nx
    // sx           nt x nx x nplist

    realtype *multResult = new realtype[udata->nJ * udata->nplist]();
    realtype *dJzdxTmp = new realtype[udata->nJ * udata->nx];
    realtype *sxTmp = new realtype[udata->nplist * udata->nx];
    realtype *sx_tmp;
    for(int ip = 0; ip < udata->nplist; ++ip){
        sx_tmp = NV_DATA_S(tdata->sx[ip]);
        if(!sx_tmp) return AMICI_ERROR_FSA;
        for(int ix = 0; ix < udata->nx; ++ix)
            sxTmp[ix + ip * udata->nx] = sx_tmp[ix];
    }

    for(int ix = 0; ix < udata->nx; ++ix)
        for(int iJ = 0; iJ < udata->nJ; ++iJ)
            dJzdxTmp[iJ + ix * udata->nJ] = tdata->dJzdx[tdata->nroots[ie] + (iJ + ix * udata->nJ) * udata->nmaxevent];

    // C := alpha*op(A)*op(B) + beta*C,
    amici_dgemm(AMICI_BLAS_ColMajor, AMICI_BLAS_NoTrans, AMICI_BLAS_NoTrans,
                udata->nJ, udata->nplist, udata->nx,
                1.0, dJzdxTmp, udata->nJ,
                sxTmp, udata->nx,
                1.0, multResult, udata->nJ);

    // sJy += multResult + dJydp
    for(int iJ = 0; iJ < udata->nJ; ++iJ) {
        if (iJ == 0)
            for(int ip = 0; ip < udata->nplist; ++ip)
                rdata->sllh[ip] -= multResult[ip * udata->nJ] + tdata->dJzdp[ip * udata->nJ];
        else
            for(int ip = 0; ip < udata->nplist; ++ip)
                rdata->s2llh[(iJ - 1) + ip * (udata->nJ-1)] -= multResult[iJ + ip*udata->nJ] + tdata->dJzdp[iJ + ip*udata->nJ];
    }

delete[] dJzdxTmp;
delete[] multResult;
delete[] sxTmp;

return(status);
}

int fdJzdp(int ie, UserData *udata, TempData *tdata, const ExpData *edata, ReturnData *rdata) {
    int status = AMICI_SUCCESS;

    // dJzdz         nztrue x nJ x nz
    // dJzdsigma     nztrue x nJ x nz
    // dzdp          nz x nplist
    // dJzdp         nJ x nplist

    memset(tdata->dJzdp,0,udata->nJ * udata->nplist * sizeof(double));

    realtype *dJzdzTmp = new double[udata->nJ * udata->nz];
    realtype *dJzdsigmaTmp = new double[udata->nJ * udata->nz];
    realtype *dJrzdsigmaTmp = NULL;
    if (tdata->t == udata->ts[udata->nt-1]) {
        dJrzdsigmaTmp = new double[udata->nJ * udata->nz];
    }

    for(int izt=0; izt < udata->nztrue; ++izt) {
        if (amiIsNaN(edata->mz[tdata->nroots[ie] + izt * udata->nmaxevent]))
            continue;

        // copy current (izt) dJzdz and dJzdsigma slices
        // dJzdzTmp     nJ x nz
        // dJzdsigmaTmp nJ x nz


        if (tdata->t < udata->ts[udata->nt-1]) {
            for(int iJ = 0; iJ < udata->nJ; ++iJ) {
                for(int iz = 0; iz < udata->nz; ++iz) {
                    dJzdzTmp[iJ  + iz * udata->nJ] = tdata->dJzdz[izt + (iJ  + iz * udata->nJ) * udata->nztrue];
                }
            }
        } else {
            for(int iJ = 0; iJ < udata->nJ; ++iJ) {
                for(int iz = 0; iz < udata->nz; ++iz) {
                    dJzdzTmp[iJ  + iz * udata->nJ] = tdata->dJrzdz[izt + (iJ  + iz * udata->nJ) * udata->nztrue];
                    dJrzdsigmaTmp[iJ  + iz * udata->nJ] = tdata->dJrzdsigma[izt + (iJ  + iz * udata->nJ) * udata->nztrue];
                }
            }
            amici_dgemm(AMICI_BLAS_ColMajor, AMICI_BLAS_NoTrans, AMICI_BLAS_NoTrans,
                        udata->nJ, udata->nplist, udata->nz,
                        1.0, dJrzdsigmaTmp, udata->nJ,
                        tdata->dsigmazdp, udata->nz,
                        1.0, tdata->dJzdp, udata->nJ);
        }

        amici_dgemm(AMICI_BLAS_ColMajor, AMICI_BLAS_NoTrans, AMICI_BLAS_NoTrans,
                    udata->nJ, udata->nplist, udata->nz,
                    1.0, dJzdzTmp, udata->nJ,
                    tdata->dzdp, udata->nz,
                    1.0, tdata->dJzdp, udata->nJ);

        for(int iJ = 0; iJ < udata->nJ; ++iJ) {
            for(int iz = 0; iz < udata->nz; ++iz) {
                dJzdsigmaTmp[iJ  + iz * udata->nJ] = tdata->dJzdsigma[izt + (iJ  + iz * udata->nJ) * udata->nztrue];
            }
        }

        amici_dgemm(AMICI_BLAS_ColMajor, AMICI_BLAS_NoTrans, AMICI_BLAS_NoTrans,
                    udata->nJ, udata->nplist, udata->nz,
                    1.0, dJzdsigmaTmp, udata->nJ,
                    tdata->dsigmazdp, udata->nz,
                    1.0, tdata->dJzdp, udata->nJ);

    }
    delete[] dJzdzTmp;
    delete[] dJzdsigmaTmp;
    if(dJrzdsigmaTmp) delete[] dJrzdsigmaTmp;


    return(status);
}

int fdJzdx(int ie, UserData *udata, TempData *tdata, const ExpData *edata) {
    int status = AMICI_SUCCESS;

    // dJzdz         nztrue x nJ x nz
    // dzdx          nz x nx
    // dJzdx         nmaxevent x nJ x nx

    realtype *dJzdzTmp = new realtype[udata->nJ * udata->nz];
    realtype *multResult = new realtype[udata->nJ * udata->nx]();
    for(int izt=0; izt < udata->nztrue; ++izt) {
        if (amiIsNaN(edata->mz[tdata->nroots[ie] + izt * udata->nmaxevent]))
            continue;

        // copy current (izt) dJzdz slice
        // dJzdzTmp     nJ x nz
        if (tdata->t < udata->ts[udata->nt-1]) {
            for(int iJ = 0; iJ < udata->nJ; ++iJ)
                for(int iz = 0; iz < udata->nz; ++iz)
                    dJzdzTmp[iJ + iz * udata->nJ] = tdata->dJzdz[izt + (iJ + iz * udata->nJ) * udata->nztrue];



            amici_dgemm(AMICI_BLAS_ColMajor, AMICI_BLAS_NoTrans, AMICI_BLAS_NoTrans,
                        udata->nJ, udata->nx, udata->nz,
                        1.0, dJzdzTmp, udata->nJ,
                        tdata->dzdx, udata->nz,
                        1.0, multResult, udata->nJ);
        } else {
            for(int iJ = 0; iJ < udata->nJ; ++iJ) {
                for(int iz = 0; iz < udata->nz; ++iz) {
                    dJzdzTmp[iJ  + iz * udata->nJ] = tdata->dJrzdz[izt + (iJ  + iz * udata->nJ) * udata->nztrue];
                }
            }

            amici_dgemm(AMICI_BLAS_ColMajor, AMICI_BLAS_NoTrans, AMICI_BLAS_NoTrans,
                        udata->nJ, udata->nx, udata->nz,
                        1.0, dJzdzTmp, udata->nJ,
                        tdata->drzdx, udata->nz,
                        1.0, multResult, udata->nJ);
        }

    }
    for(int iJ = 0; iJ < udata->nJ; ++iJ)
        for(int ix = 0; ix < udata->nx; ++ix)
            tdata->dJzdx[tdata->nroots[ie] + (iJ + ix * udata->nJ ) * udata->nmaxevent] = multResult[iJ + ix * udata->nJ];

    delete[] dJzdzTmp;
    delete[] multResult;

    return(status);
}