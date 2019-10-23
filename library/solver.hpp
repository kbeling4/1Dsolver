#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <type_traits>
#include <string>

#include <boost/python.hpp>

namespace solver{

#include "solver/grid.hpp"
#include "solver/ordinates.hpp"
#include "solver/sweeper.hpp"
#include "solver/source.hpp"
#include "solver/boundary.hpp"
#include "solver/print.hpp"
#include "solver/error.hpp"
  
}

#endif
