#ifndef _amici_model_jakstat_adjoint_o2_h
#define _amici_model_jakstat_adjoint_o2_h
/* Generated by amiwrap (R2017b) 667c9f20a05dd5266e9453b50081d7fb933f7389 */
#include <cmath>
#include <memory>
#include "amici/defines.h"
#include <sunmatrix/sunmatrix_sparse.h> //SUNMatrixContent_Sparse definition
#include "amici/solver_cvodes.h"
#include "amici/model_ode.h"

namespace amici {

class Solver;

namespace model_model_jakstat_adjoint_o2{

extern void J_model_jakstat_adjoint_o2(realtype *J, const realtype t, const realtype *x, const double *p, const double *k, const realtype *h, const realtype *w, const realtype *dwdx);
extern void JB_model_jakstat_adjoint_o2(realtype *JB, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *xB, const realtype *w, const realtype *dwdx);
extern void JDiag_model_jakstat_adjoint_o2(realtype *JDiag, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *dwdx);
extern void JSparse_model_jakstat_adjoint_o2(SUNMatrixContent_Sparse JSparse, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *dwdx);
extern void JSparseB_model_jakstat_adjoint_o2(SUNMatrixContent_Sparse JSparseB, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *xB, const realtype *w, const realtype *dwdx);
extern void Jy_model_jakstat_adjoint_o2(double *nllh, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my);
extern void dJydsigma_model_jakstat_adjoint_o2(double *dJydsigma, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my);
extern void dJydy_model_jakstat_adjoint_o2(double *dJydy, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my);
extern void dsigmaydp_model_jakstat_adjoint_o2(double *dsigmaydp, const realtype t, const realtype *p, const realtype *k, const int ip);
extern void dwdp_model_jakstat_adjoint_o2(realtype *dwdp, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *tcl, const realtype *stcl);
extern void dwdx_model_jakstat_adjoint_o2(realtype *dwdx, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *tcl);
extern void dxdotdp_model_jakstat_adjoint_o2(realtype *dxdotdp, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip, const realtype *w, const realtype *dwdp);
extern void dydp_model_jakstat_adjoint_o2(double *dydp, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip, const realtype *w, const realtype *dwdp);
extern void dydx_model_jakstat_adjoint_o2(double *dydx, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *dwdx);
extern void sigmay_model_jakstat_adjoint_o2(double *sigmay, const realtype t, const realtype *p, const realtype *k);
extern void sx0_model_jakstat_adjoint_o2(realtype *sx0, const realtype t,const realtype *x0, const realtype *p, const realtype *k, const int ip);
extern void w_model_jakstat_adjoint_o2(realtype *w, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *tcl);
extern void x0_model_jakstat_adjoint_o2(realtype *x0, const realtype t, const realtype *p, const realtype *k);
extern void xdot_model_jakstat_adjoint_o2(realtype *xdot, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w);
extern void y_model_jakstat_adjoint_o2(double *y, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w);

class Model_model_jakstat_adjoint_o2 : public amici::Model_ODE {
public:
    Model_model_jakstat_adjoint_o2() : amici::Model_ODE(162,
                    9,
                    162,
                    9,
                    0,
                    54,
                    3,
                    0,
                    0,
                    0,
                    18,
                    10,
                    2,
                    30,
                    0,
                    {},
                    384,
                    8,
                    154,
                    amici::SecondOrderMode::full,
                    std::vector<realtype>(17,1.0),
                    std::vector<realtype>(2,1.0),
                    std::vector<int>(),
                    std::vector<realtype>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    std::vector<int>{})
                    {};

    virtual amici::Model* clone() const override { return new Model_model_jakstat_adjoint_o2(*this); };

    const  std::string getAmiciCommit() const override { return "667c9f20a05dd5266e9453b50081d7fb933f7389"; };

    virtual void fJ(realtype *J, const realtype t, const realtype *x, const double *p, const double *k, const realtype *h, const realtype *w, const realtype *dwdx) override {
        J_model_jakstat_adjoint_o2(J, t, x, p, k, h, w, dwdx);
    }

    virtual void fJB(realtype *JB, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *xB, const realtype *w, const realtype *dwdx) override {
        JB_model_jakstat_adjoint_o2(JB, t, x, p, k, h, xB, w, dwdx);
    }

    virtual void fJDiag(realtype *JDiag, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *dwdx) override {
        JDiag_model_jakstat_adjoint_o2(JDiag, t, x, p, k, h, w, dwdx);
    }

    virtual void fJSparse(SUNMatrixContent_Sparse JSparse, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *dwdx) override {
        JSparse_model_jakstat_adjoint_o2(JSparse, t, x, p, k, h, w, dwdx);
    }

    virtual void fJSparseB(SUNMatrixContent_Sparse JSparseB, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *xB, const realtype *w, const realtype *dwdx) override {
        JSparseB_model_jakstat_adjoint_o2(JSparseB, t, x, p, k, h, xB, w, dwdx);
    }

    virtual void fJrz(double *nllh, const int iz, const realtype *p, const realtype *k, const double *rz, const double *sigmaz) override {
    }

    virtual void fJy(double *nllh, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my) override {
        Jy_model_jakstat_adjoint_o2(nllh, iy, p, k, y, sigmay, my);
    }

    virtual void fJz(double *nllh, const int iz, const realtype *p, const realtype *k, const double *z, const double *sigmaz, const double *mz) override {
    }

    virtual void fdJrzdsigma(double *dJrzdsigma, const int iz, const realtype *p, const realtype *k, const double *rz, const double *sigmaz) override {
    }

    virtual void fdJrzdz(double *dJrzdz, const int iz, const realtype *p, const realtype *k, const double *rz, const double *sigmaz) override {
    }

    virtual void fdJydsigma(double *dJydsigma, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my) override {
        dJydsigma_model_jakstat_adjoint_o2(dJydsigma, iy, p, k, y, sigmay, my);
    }

    virtual void fdJydy(double *dJydy, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my) override {
        dJydy_model_jakstat_adjoint_o2(dJydy, iy, p, k, y, sigmay, my);
    }

    virtual void fdJzdsigma(double *dJzdsigma, const int iz, const realtype *p, const realtype *k, const double *z, const double *sigmaz, const double *mz) override {
    }

    virtual void fdJzdz(double *dJzdz, const int iz, const realtype *p, const realtype *k, const double *z, const double *sigmaz, const double *mz) override {
    }

    virtual void fdeltaqB(double *deltaqB, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip, const int ie, const realtype *xdot, const realtype *xdot_old, const realtype *xB) override {
    }

    virtual void fdeltasx(double *deltasx, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const int ip, const int ie, const realtype *xdot, const realtype *xdot_old, const realtype *sx, const realtype *stau) override {
    }

    virtual void fdeltax(double *deltax, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ie, const realtype *xdot, const realtype *xdot_old) override {
    }

    virtual void fdeltaxB(double *deltaxB, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ie, const realtype *xdot, const realtype *xdot_old, const realtype *xB) override {
    }

    virtual void fdrzdp(double *drzdp, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip) override {
    }

    virtual void fdrzdx(double *drzdx, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h) override {
    }

    virtual void fdsigmaydp(double *dsigmaydp, const realtype t, const realtype *p, const realtype *k, const int ip) override {
        dsigmaydp_model_jakstat_adjoint_o2(dsigmaydp, t, p, k, ip);
    }

    virtual void fdsigmazdp(double *dsigmazdp, const realtype t, const realtype *p, const realtype *k, const int ip) override {
    }

    virtual void fdwdp(realtype *dwdp, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *tcl, const realtype *stcl) override {
        dwdp_model_jakstat_adjoint_o2(dwdp, t, x, p, k, h, w, tcl, stcl);
    }

    virtual void fdwdx(realtype *dwdx, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *tcl) override {
        dwdx_model_jakstat_adjoint_o2(dwdx, t, x, p, k, h, w, tcl);
    }

    virtual void fdxdotdp(realtype *dxdotdp, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip, const realtype *w, const realtype *dwdp) override {
        dxdotdp_model_jakstat_adjoint_o2(dxdotdp, t, x, p, k, h, ip, w, dwdp);
    }

    virtual void fdydp(double *dydp, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip, const realtype *w, const realtype *dwdp) override {
        dydp_model_jakstat_adjoint_o2(dydp, t, x, p, k, h, ip, w, dwdp);
    }

    virtual void fdydx(double *dydx, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *dwdx) override {
        dydx_model_jakstat_adjoint_o2(dydx, t, x, p, k, h, w, dwdx);
    }

    virtual void fdzdp(double *dzdp, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip) override {
    }

    virtual void fdzdx(double *dzdx, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h) override {
    }

    virtual void froot(realtype *root, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h) override {
    }

    virtual void frz(double *rz, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h) override {
    }

    virtual void fsigmay(double *sigmay, const realtype t, const realtype *p, const realtype *k) override {
        sigmay_model_jakstat_adjoint_o2(sigmay, t, p, k);
    }

    virtual void fsigmaz(double *sigmaz, const realtype t, const realtype *p, const realtype *k) override {
    }

    virtual void fsrz(double *srz, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *sx, const int ip) override {
    }

    virtual void fstau(double *stau, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *sx, const int ip, const int ie) override {
    }

    virtual void fsx0(realtype *sx0, const realtype t,const realtype *x0, const realtype *p, const realtype *k, const int ip) override {
        sx0_model_jakstat_adjoint_o2(sx0, t, x0, p, k, ip);
    }

    virtual void fsz(double *sz, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *sx, const int ip) override {
    }

    virtual void fw(realtype *w, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *tcl) override {
        w_model_jakstat_adjoint_o2(w, t, x, p, k, h, tcl);
    }

    virtual void fx0(realtype *x0, const realtype t, const realtype *p, const realtype *k) override {
        x0_model_jakstat_adjoint_o2(x0, t, p, k);
    }

    virtual void fxdot(realtype *xdot, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w) override {
        xdot_model_jakstat_adjoint_o2(xdot, t, x, p, k, h, w);
    }

    virtual void fy(double *y, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w) override {
        y_model_jakstat_adjoint_o2(y, t, x, p, k, h, w);
    }

    virtual void fz(double *z, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h) override {
    }

};

} // namespace model_model_jakstat_adjoint_o2

} // namespace amici 

#endif /* _amici_model_jakstat_adjoint_o2_h */
