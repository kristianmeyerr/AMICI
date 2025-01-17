# Contents of `scripts/`

This directory contains a number of build, installation, and CI scripts. 

* `buildAll.sh`
   
   Build AMICI along with dependencies and test suite

* `buildAmici.sh`

   Build AMICI library and test models

* `buildBNGL.sh`

   Download and build 
   [BioNetGen](https://github.com/RuleWorld/bionetgen) (required for some tests)
  
* `buildSuiteSparse.sh`

   Build [SuiteSparse](http://faculty.cse.tamu.edu/davis/suitesparse.html)
   included in this repository
   
* `buildSundials.sh`

   Build [Sundials](https://computation.llnl.gov/projects/sundials/)
   included in this repository

* `buildSuperLUMT.sh`

   Download and build the SuperLU-MT solver. Required to build CVODES/AMICI
   with SuperLU-MT support.

* `buildValgrind.sh`

   Download and build [Valgrind](http://valgrind.org/).
   This is used if Valgrind versions provided by homebrew or apt are buggy.

* `buildXcode.sh`

   Build AMICI and C++ test models and test with XCode

* `downloadAndBuildSwig.sh`

  Download and build [SWIG](http://www.swig.org/) 

* `installAmiciArchive.sh`

  Create a Python virtual environment and do an AMICI development installation

* `installAmiciSource.sh`
  
  Create a Python virtual environment and do a regular AMICI installation

* `run-codecov.sh`

  Script for Python test code coverage analysis

* `run-cppcheck.sh`

  Run static code analysis

* `run-cpp-tests.sh`

  Run C++ unit and integration tests

* `run-doxygen.sh`

  Run doxygen to create AMICI documentation

* `runNotebook.sh`

  Script for running Jupyter notebooks from the command line. Used for CI
  to ensure functioning notebooks.

* `run-python-tests.sh`

  Run the AMICI Python test suite

* `run-SBMLTestsuite.sh`

  Download and run the semantic 
  [SBML Test Suite](https://github.com/sbmlteam/sbml-test-suite/)

* `run-valgrind.sh`

  Run memory leak check using valgrind for all unit and integration tests.
  Assumes they have been built before in the default location. 
