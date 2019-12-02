#include "solver.hpp"
#include "input.hpp"

int main(){
  const std::vector<std::string> PARAMS{PROBLEM_TYPE, BOUNDARY_L, BOUNDARY_R};

  // Check for Errors
  solver::checkForErrors(CELLS, BOUNDS, SN, MATS, PARAMS, PRINTER);
  
  // Run Problem
  solver::looper(CELLS, BOUNDS, PARAMS, MATS, SOURCE_FUNCTION, ALPHA, SN, TOLERANCE, NORMALIZE_SCALAR, PRINTER);
}
