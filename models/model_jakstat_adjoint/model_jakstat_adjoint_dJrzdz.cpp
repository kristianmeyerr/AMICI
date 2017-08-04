
#include <include/symbolic_functions.h>
#include <include/amici.h>
#include <string.h>
#include <include/udata.h>
#include <include/tdata.h>
#include <include/rdata.h>
#include <include/edata.h>
#include "model_jakstat_adjoint_w.h"

int dJrzdz_model_jakstat_adjoint(realtype t, int ie, N_Vector x, void *user_data, TempData *tdata, const ExpData *edata, ReturnData *rdata) {
int status = 0;
UserData *udata = (UserData*) user_data;
realtype *x_tmp = N_VGetArrayPointer(x);
memset(tdata->dJrzdz,0,sizeof(realtype)*udata->nz*udata->nztrue*udata->nJ);
status = w_model_jakstat_adjoint(t,x,NULL,user_data);
return(status);

}

