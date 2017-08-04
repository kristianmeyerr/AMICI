
#include <include/symbolic_functions.h>
#include <include/amici.h>
#include <string.h>
#include <include/udata.h>
#include "model_neuron_o2_w.h"

int dwdx_model_neuron_o2(realtype t, N_Vector x, N_Vector dx, void *user_data) {
int status = 0;
UserData *udata = (UserData*) user_data;
realtype *x_tmp = N_VGetArrayPointer(x);
memset(udata->dwdx,0,sizeof(realtype)*2);
status = w_model_neuron_o2(t,x,NULL,user_data);
  udata->dwdx[0] = 2.0/2.5E1;
  udata->dwdx[1] = udata->dwdx[0];
return(status);

}

