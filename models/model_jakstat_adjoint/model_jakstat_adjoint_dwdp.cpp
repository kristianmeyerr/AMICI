
#include <include/symbolic_functions.h>
#include <include/amici.h>
#include <include/amici_model.h>
#include <string.h>
#include <include/tdata.h>
#include <include/udata.h>
#include "model_jakstat_adjoint_w.h"

using namespace amici;

void dwdp_model_jakstat_adjoint(realtype t, N_Vector x, N_Vector dx, void *user_data) {
TempData *tdata = (TempData*) user_data;
Model *model = (Model*) tdata->model;
UserData *udata = (UserData*) tdata->udata;
realtype *x_tmp = nullptr;
if(x)
    x_tmp = N_VGetArrayPointer(x);
realtype *dx_tmp = nullptr;
if(dx)
    dx_tmp = N_VGetArrayPointer(dx);
memset(tdata->dwdp,0,sizeof(realtype)*5);
w_model_jakstat_adjoint(t,x,NULL,tdata);
  tdata->dwdp[0] = am_Dspline_pos(4,t,5,0.0,tdata->p[5],5.0,tdata->p[6],1.0E1,tdata->p[7],2.0E1,tdata->p[8],6.0E1,tdata->p[9],0.0,0.0);
  tdata->dwdp[1] = am_Dspline_pos(6,t,5,0.0,tdata->p[5],5.0,tdata->p[6],1.0E1,tdata->p[7],2.0E1,tdata->p[8],6.0E1,tdata->p[9],0.0,0.0);
  tdata->dwdp[2] = am_Dspline_pos(8,t,5,0.0,tdata->p[5],5.0,tdata->p[6],1.0E1,tdata->p[7],2.0E1,tdata->p[8],6.0E1,tdata->p[9],0.0,0.0);
  tdata->dwdp[3] = am_Dspline_pos(10,t,5,0.0,tdata->p[5],5.0,tdata->p[6],1.0E1,tdata->p[7],2.0E1,tdata->p[8],6.0E1,tdata->p[9],0.0,0.0);
  tdata->dwdp[4] = am_Dspline_pos(12,t,5,0.0,tdata->p[5],5.0,tdata->p[6],1.0E1,tdata->p[7],2.0E1,tdata->p[8],6.0E1,tdata->p[9],0.0,0.0);
return;

}


