#include "include/edata.h"

#include "include/amici_defines.h"
#include "include/amici_model.h"
#include <cstring>
#include <include/udata.h>

ExpData::ExpData() : nytrue(0), nztrue(0), nt(0), nmaxevent(0) {}

ExpData::ExpData(const UserData *udata, Model *model)
    : nytrue(model->nytrue), nztrue(model->nztrue), nt(udata->nt),
      nmaxevent(udata->nmaxevent) {
    /**
     * constructor that initializes with UserData and model
     *
     * @param[out] udata pointer to the return data struct @type ReturnData
     * @param[in] model pointer to model specification object @type Model
     */
    if (udata) {
        my = new double[udata->nt * model->nytrue]();
        sigmay = new double[udata->nt * model->nytrue]();
        mz = new double[udata->nmaxevent * model->nztrue]();
        mrz = new double[udata->nmaxevent * model->nztrue]();
        sigmaz = new double[udata->nmaxevent * model->nztrue]();
    }
}

void ExpData::setObservedData(const double *observedData) {
    /**
     * set function that copies data from input to ExpData::my
     *
     * @param[in] observedData observed data @type *double
     */
    memcpy(my, observedData, nytrue * nt * sizeof(double));
}

void ExpData::setObservedDataStdDev(const double *observedDataStdDev) {
    /**
     * set function that copies data from input to ExpData::sigmay
     *
     * @param[in] observedDataStdDev standard deviation of observed data @type *double
     */
    memcpy(sigmay, observedDataStdDev, nytrue * nt * sizeof(double));
}

void ExpData::setObservedEvents(const double *observedEvents) {
    /**
     * set function that copies data from input to ExpData::mz
     *
     * @param[in] observedEvents observed event data @type *double
     */
    memcpy(mz, observedEvents, nmaxevent * nztrue * sizeof(double));
}

void ExpData::setObservedRoots(const double *observedRoots) {
    /**
     * set function that copies data from input to ExpData::mrz
     *
     * @param[in] observedRoots observed roots of event data @type *double
     */
    memcpy(mrz, observedRoots, nmaxevent * nztrue * sizeof(double));
}

void ExpData::setObservedEventsStdDev(const double *observedEventsStdDev) {
    /**
     * set function that copies data from input to ExpData::sigmaz
     *
     * @param[in] observedEventsStdDev standard deviation of observed event data @type *double
     */
    memcpy(sigmaz, observedEventsStdDev, nmaxevent * nztrue * sizeof(double));
}

ExpData::~ExpData() {
    if (my)
        delete[] my;
    if (sigmay)
        delete[] sigmay;
    if (mz)
        delete[] mz;
    if (mrz)
        delete[] mrz;
    if (sigmaz)
        delete[] sigmaz;
}
