
#include <include/symbolic_functions.h>
#include <include/amici.h>
#include <include/amici_model.h>
#include <string.h>
#include <include/tdata.h>
#include <include/rdata.h>
#include <include/edata.h>
#include "model_dirac_w.h"

int dJzdsigma_model_dirac(realtype t, int ie, N_Vector x, TempData *tdata, const ExpData *edata, ReturnData *rdata) {
int status = 0;
Model *model = (Model*) tdata->model;
UserData *udata = (UserData*) tdata->udata;
realtype *x_tmp = N_VGetArrayPointer(x);
memset(tdata->dJzdsigma,0,sizeof(realtype)*model->nztrue*model->nz*model->nJ);
status = w_model_dirac(t,x,NULL,tdata);
return(status);

}


