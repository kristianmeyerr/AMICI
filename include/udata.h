#ifndef AMICI_UDATA_H
#define AMICI_UDATA_H

#include "include/amici_defines.h"
#include "include/symbolic_functions.h" //getNaN
#include <cmath>
#include <vector>

namespace amici {
class UserData;
}

namespace boost { namespace serialization {
template <class Archive>
void serialize(Archive &ar, amici::UserData &u, const unsigned int version);
}}

namespace amici {
    
class Model;

template <class mxArray>
UserData *userDataFromMatlabCall(const mxArray *prhs[], int nrhs);
    
template <class hid_t>
UserData *AMI_HDF5_readSimulationUserDataFromFileObject(hid_t fileId,
                                                        const char *datasetPath);

/** @brief struct that stores all user provided data
 * NOTE: multidimensional arrays are expected to be stored in column-major order
 * (FORTRAN-style)
 */


class UserData {

  public:
    /**
     * @brief UserData
     * @param np total number of model parameters
     * @param nk number of fixed parameters
     * @param nx number of states
     */
    UserData(const int np, const int nk, const int nx);

    /**
     * @brief Default constructor for testing and serialization
     */
    UserData();

    /** Copy constructor
     * @param other object to copy from
     */
    UserData (const UserData &other);

    /** Copy assignment is disabled until const members are removed
     * @param other object to copy from
     * @return
     */
    UserData& operator=(UserData const &other)=delete;

    void unscaleParameters(double *bufferUnscaled) const;

    /**
     * @brief setTimepoints
     * @param timepoints
     * @param numTimepoints
     */
    void setTimepoints(const double *timepoints, int numTimepoints);

    /**
     * @brief setParameters
     * @param parameters
     */
    void setParameters(const double *parameters);

    /**
     * @brief setConstants
     * @param constants
     */
    void setConstants(const double *constants);

    /**
     * @brief setPlist set parameter selection and ordering.
     * accepts array of doubles to deal with user input from matlab.
     * @param plist
     * @param nplist length of plist
     */
    void setPlist(const double *plist, int nplist);
    /**
     * @brief setPlist set parameter selection and ordering.
     * accepts array of ints.
     * @param plist
     * @param nplist length of plist
     */
    void setPlist(const int *plist, int nplist);

    /**
     * @brief Require computation of sensitiivities for all parameters p [0..np[
     * in natural order.
     */
    void requireSensitivitiesForAllParameters();
    
    /**
     * @brief setPScale.
     * @param pscale
     */
    void setPScale(const AMICI_parameter_scaling pscale);
    
    /**
     * @brief getPScale.
     * @return pscale
     */
    const AMICI_parameter_scaling getPScale() const;

    /**
     * @brief setPbar. Must not be called before setPlist
     * @param parameterScaling
     */
    void setPbar(const double *parameterScaling);
    
    /**
     * @brief getPbar
     * @return parameterScaling
     */
    const double *getPbar() const;
    
    /**
     * @brief setXbar.
     * @param stateScaling
     */
    void setXbar(const double *stateScaling);

    /**
     * @brief setStateInitialization
     * @param stateInitialization
     */
    void setStateInitialization(const double *stateInitialization);

    /**
     * @brief setSensitivityInitialization
     * @param sensitivityInitialization
     */
    void setSensitivityInitialization(const double *sensitivityInitialization);
    
    const LinearMultistepMethod getLinearMultistepMethod() const;
    
    const NonlinearSolverIteration getNonlinearSolverIteration() const;
    
    const InterpolationType getInterpolationType() const;
    
    const StateOrdering getStateOrdering() const;
    
    const int getStabilityLimitFlag() const;

    ~UserData();

    /* Options */


    /** number of parameters in plist 
     *  @return length of plist
     */
    const int nplist() const{
        return p_index.size();
    };
    
    /** initial timepoint
     *  @return timepoint
     */
    const double t0() const{
        return tstart;
    }

    /** number of timepoints
     *  @return nt
     */
    const int nt() const{
        return ts.size();
    }

    /** function to print the contents of the UserData object */
    void print() const;

    /** total number of model parameters
     * @return np
     */
    const int np() const{
        return par.size();
    };
    
    /** number of fixed parameters
     * @return nk
     */
    const int nk() const{
        return konst.size();
    };
    /** number of states
     * @return nx
     */
    const int nx() const{
        return sizex;
    };
    
    /** max number of events
     * @return nmaxevent
     */
    const int nme() const{
        return nmaxevent;
    };
    
    /** sensitivity method
     * @return method enum
     */
    const int sensmeth() const{
        return sensi_meth;
    };
    
    /** timepoints
     * @return pointer to timepoints array
     */
    const double *t() const{
        return ts.data();
    };
    
    /** timepoint in timepoints array
     * @param pos index
     * @return timepoints
     */
    const double t(int pos) const{
        return ts.at(pos);
    };
    
    /** parameters
     * @return pointer to parameter array
     */
    const double *p() const{
        return par.data();
    };
    
    /** unscaled parameters
     * @return pointer to array of unscaled parameters
     */
    const double *unp() const{
        return unpar.data();
    };
    
    /** constants
     * @return pointer to constants array
     */
    const double *k() const{
        return konst.data();
    };
    
    /** entry in parameter list
     * @param pos index
     * @return entry
     */
    const int plist(int pos) const{
        return p_index.at(pos);
    };
    
    /** parameter list as int vector
     * @return int vector
     */
    const std::vector<int> plist() const{
        return p_index;
    };
    
    /** user provided initial values for state variables
     * @return vector with values
     */
    std::vector<double> getInitialStates() const {
        return x0data;
    }
    
    /** user provided initial values for state variables
     * @return vector with values
     */
    std::vector<double> getInitialSensitivityStates() const {
        return sx0data;
    }

    /**
     * @brief Serialize UserData (see boost::serialization::serialize)
     * @param ar Archive to serialize to
     * @param r Data to serialize
     * @param version Version number
     */
    template <class Archive>
    friend void boost::serialization::serialize(Archive &ar, UserData &r, const unsigned int version);
    
    /** maximum number of allowed Newton steps for steady state computation */
    int newton_maxsteps = 0;
    
    /** maximum number of allowed linear steps per Newton step for steady state
     * computation */
    int newton_maxlinsteps = 0;
    
    /** Preequilibration of model via Newton solver? */
    int newton_preeq = false;
    
    /** Which preconditioner is to be used in the case of iterative linear
     * Newton solvers */
    int newton_precon = 1;
    
    /** internal sensitivity method flag used to select the sensitivity solution
     * method. Only applies for Forward Sensitivities. */
    InternalSensitivityMethod ism = SIMULTANEOUS;
    
    /** linear solver specification */
    LinearSolver linsol = AMICI_KLU;
    
    /** absolute tolerances for integration */
    double atol = 1e-16;
    
    /** relative tolerances for integration */
    double rtol = 1e-8;
    
    /** maximum number of allowed integration steps */
    int maxsteps = 0;
    
    /** absolute tolerances for backward quadratures */
    double quad_atol = 1e-8;
    
    /** relative tolerances for backward quadratures */
    double quad_rtol = 1e-6;
    
    /** maximum number of allowed integration steps for backward problem */
    int maxstepsB = 0;
    
    /** flag indicating whether sensitivities are supposed to be computed */
    AMICI_sensi_order sensi = AMICI_SENSI_ORDER_NONE;
    
private:
    /** maximal number of events to track */
    int nmaxevent = 10;
    
    /** positivity flag (size nx) */
    std::vector<int>qpositivex;
    
    /** parameter selection and reordering (size nplist) */
    std::vector<int>p_index;
    
    
    const int sizex;
    /** parameter array (size np) */
    std::vector<double>par;
    
    /** unscaled parameter array (size np) */
    std::vector<double>unpar;
    
    /** constants array (size nk) */
    std::vector<double>konst;
    
    /** starting time */
    double tstart = 0.0;
    
    /** parameter transformation of p */
    AMICI_parameter_scaling pscale = AMICI_SCALING_NONE;
    
    /** timepoints (size nt) */
    std::vector<double>ts;
    
    /** scaling of parameters (size nplist) */
    std::vector<double>pbar;
    
    /** scaling of states (size nx)
     * NOTE: currently not used */
    std::vector<double>xbar;
    
    /** method for sensitivity computation */
    AMICI_sensi_meth sensi_meth = AMICI_SENSI_FSA;
    
    /** interpolation type for the forward problem solution which
     * is then used for the backwards problem.
     */
    InterpolationType interpType = HERMITE;
    
    /** specifies the linear multistep method.
     */
    LinearMultistepMethod lmm = BDF;
    
    /**
     * specifies the type of nonlinear solver iteration
     */
    NonlinearSolverIteration iter = NEWTON;
    
    /** flag controlling stability limit detection */
    booleantype stldet = true;
    
    /** state initialisation (size nx) */
    std::vector<double>x0data;
    
    /** sensitivity initialisation (size nx * nplist) */
    std::vector<double>sx0data;
    
    /** state ordering */
    StateOrdering ordering = AMD;
    
    /**
     * @brief userDataFromMatlabCall addition.
     * @relates userDataFromMatlabCall
     */
    template <class mxArray>
    friend UserData *userDataFromMatlabCall(const mxArray *prhs[], int nrhs);
    
    /**
     * @brief AMI_HDF5_readSimulationUserDataFromFileObject addition.
     * @relates AMI_HDF5_readSimulationUserDataFromFileObject
     * @param fileId HDF5 file ID
     * @param datasetPath path to data within HDF5 file
     */
    template <class hid_t>
    friend UserData *AMI_HDF5_readSimulationUserDataFromFileObject(hid_t fileId,
                                                                   const char *datasetPath);
};

} // namespace amici

#endif /* _MY_UDATA */
