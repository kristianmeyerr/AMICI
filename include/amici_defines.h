#ifndef AMICI_DEFINES_H
#define AMICI_DEFINES_H

/* linear solvers */
#define AMICI_DENSE       1
#define AMICI_BAND        2
#define AMICI_LAPACKDENSE 3
#define AMICI_LAPACKBAND  4
#define AMICI_DIAG        5
#define AMICI_SPGMR       6
#define AMICI_SPBCG       7
#define AMICI_SPTFQMR     8
#define AMICI_KLU         9

#define AMICI_ONEOUTPUT   5

/* Return codes */
#define AMICI_ERROR_UDATA              -99
#define AMICI_ERROR_EDATA              -98
#define AMICI_ERROR_RDATA              -97
#define AMICI_ERROR_TDATA              -96
#define AMICI_ERROR_SETUP              -95
#define AMICI_ERROR_SETUPB             -94
#define AMICI_ERROR_NOTHINGTODO        -93
#define AMICI_ERROR_FSA                -92
#define AMICI_ERROR_ASA                -91
#define AMICI_ERROR_SA                 -90
#define AMICI_ERROR_SS                 -89
#define AMICI_ERROR_DATA               -88
#define AMICI_ERROR_EVENT              -87
#define AMICI_ERROR_SIMULATION         -86
#define AMICI_ERROR_NOT_IMPLEMENTED    -85
#define AMICI_SUCCESS                    0
#define AMICI_DATA_RETURN                1
#define AMICI_ROOT_RETURN                2

#define AMICI_NORMAL                     1
#define AMICI_ONE_STEP                   2


typedef double realtype;

typedef enum {AMICI_BLAS_RowMajor=101, AMICI_BLAS_ColMajor=102} AMICI_BLAS_LAYOUT;
typedef enum {AMICI_BLAS_NoTrans=111, AMICI_BLAS_Trans=112, AMICI_BLAS_ConjTrans=113} AMICI_BLAS_TRANSPOSE;


#endif
