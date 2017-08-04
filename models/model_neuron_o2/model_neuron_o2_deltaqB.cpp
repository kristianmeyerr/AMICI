
#include <include/symbolic_functions.h>
#include <include/amici.h>
#include <string.h>
#include <include/udata.h>
#include <include/tdata.h>
#include "model_neuron_o2_w.h"

int deltaqB_model_neuron_o2(realtype t, int ie, N_Vector x, N_Vector xB, N_Vector qBdot, N_Vector xdot, N_Vector xdot_old, void *user_data, TempData *tdata) {
int status = 0;
UserData *udata = (UserData*) user_data;
realtype *x_tmp = N_VGetArrayPointer(x);
realtype *xB_tmp = N_VGetArrayPointer(xB);
realtype *xdot_tmp = N_VGetArrayPointer(xdot);
realtype *qBdot_tmp = N_VGetArrayPointer(qBdot);
realtype *xdot_old_tmp = N_VGetArrayPointer(xdot_old);
int ip;
memset(tdata->deltaqB,0,sizeof(realtype)*udata->nplist*udata->nJ);
status = w_model_neuron_o2(t,x,NULL,user_data);
for(ip = 0; ip<udata->nplist; ip++) {
switch (udata->plist[ip]) {
  case 0: {
              switch(ie) { 
              case 0: {
  tdata->deltaqB[ip+0] = (x_tmp[2]*xB_tmp[3]*(udata->p[3]+udata->p[1]*udata->p[2]+udata->p[1]*x_tmp[0]))/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2)+(x_tmp[4]*xB_tmp[5]*(udata->p[3]+udata->p[1]*udata->p[2]+udata->p[1]*x_tmp[0]))/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2)+(x_tmp[6]*xB_tmp[7]*(udata->p[3]+udata->p[1]*udata->p[2]+udata->p[1]*x_tmp[0]))/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2)+(x_tmp[8]*xB_tmp[9]*(udata->p[3]+udata->p[1]*udata->p[2]+udata->p[1]*x_tmp[0]))/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2);

              } break;

              } 

  } break;

  case 1: {
              switch(ie) { 
              case 0: {
  tdata->deltaqB[ip+0] = (x_tmp[2]*xB_tmp[3]*(udata->p[0]*udata->p[2]+udata->p[0]*x_tmp[0]))/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2)+(x_tmp[4]*xB_tmp[5]*(udata->p[0]*udata->p[2]+udata->p[0]*x_tmp[0]))/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2)+(x_tmp[6]*xB_tmp[7]*(udata->p[0]*udata->p[2]+udata->p[0]*x_tmp[0]))/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2)+(x_tmp[8]*xB_tmp[9]*(udata->p[0]*udata->p[2]+udata->p[0]*x_tmp[0]))/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2);

              } break;

              } 

  } break;

  case 2: {
              switch(ie) { 
              case 0: {
  tdata->deltaqB[ip+0] = xB_tmp[0]-(x_tmp[2]*xB_tmp[2]*(udata->p[2]*(2.0/2.5E1)-5.0))/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2)-(x_tmp[4]*xB_tmp[4]*(udata->p[2]*(2.0/2.5E1)-5.0))/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2)-(x_tmp[6]*xB_tmp[6]*(udata->p[2]*(2.0/2.5E1)-5.0))/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2)-(x_tmp[8]*xB_tmp[8]*(udata->p[2]*(2.0/2.5E1)-5.0))/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2)+(udata->p[0]*udata->p[1]*x_tmp[2]*xB_tmp[3])/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2)+(udata->p[0]*udata->p[1]*x_tmp[4]*xB_tmp[5])/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2)+(udata->p[0]*udata->p[1]*x_tmp[6]*xB_tmp[7])/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2)+(udata->p[0]*udata->p[1]*x_tmp[8]*xB_tmp[9])/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2);

              } break;

              } 

  } break;

  case 3: {
              switch(ie) { 
              case 0: {
  tdata->deltaqB[ip+0] = -xB_tmp[1]+(x_tmp[2]*xB_tmp[2])/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2)+(x_tmp[4]*xB_tmp[4])/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2)+(x_tmp[6]*xB_tmp[6])/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2)+(x_tmp[8]*xB_tmp[8])/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2)+(udata->p[0]*x_tmp[2]*xB_tmp[3])/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2)+(udata->p[0]*x_tmp[4]*xB_tmp[5])/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2)+(udata->p[0]*x_tmp[6]*xB_tmp[7])/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2)+(udata->p[0]*x_tmp[8]*xB_tmp[9])/(udata->k[1]+x_tmp[0]*5.0-x_tmp[1]+(x_tmp[0]*x_tmp[0])*(1.0/2.5E1)+1.4E2);

              } break;

              } 

  } break;

}
}
return(status);

}

