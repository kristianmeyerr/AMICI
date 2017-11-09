
#include <include/symbolic_functions.h>
#include <include/amici.h>
#include <include/amici_model.h>
#include <string.h>
#include <include/tdata.h>
#include <include/udata.h>
#include <include/rdata.h>
#include "model_steadystate_w.h"

using namespace amici;

void y_model_steadystate(realtype t, int it, N_Vector x, void *user_data, amici::ReturnData *rdata) {
TempData *tdata = (TempData*) user_data;
Model *model = (Model*) tdata->model;
UserData *udata = (UserData*) tdata->udata;
realtype *x_tmp = nullptr;
if(x)
    x_tmp = N_VGetArrayPointer(x);
w_model_steadystate(t,x,NULL,tdata);
  rdata->y[it + udata->nt*0] = x_tmp[0];
  rdata->y[it + udata->nt*1] = x_tmp[1];
  rdata->y[it + udata->nt*2] = x_tmp[2];
return;

}


