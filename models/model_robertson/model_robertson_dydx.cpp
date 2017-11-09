
#include <include/symbolic_functions.h>
#include <include/amici.h>
#include <include/amici_model.h>
#include <string.h>
#include <include/tdata.h>
#include <include/udata.h>
#include "model_robertson_w.h"

using namespace amici;

void dydx_model_robertson(realtype t, int it, N_Vector x, amici::TempData *tdata) {
Model *model = (Model*) tdata->model;
UserData *udata = (UserData*) tdata->udata;
realtype *x_tmp = nullptr;
if(x)
    x_tmp = N_VGetArrayPointer(x);
  tdata->dydx[0+0*3] = 1.0;
  tdata->dydx[1+1*3] = 1.0E4;
  tdata->dydx[2+2*3] = 1.0;
return;

}


