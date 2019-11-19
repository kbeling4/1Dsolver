///////////////////////////////////////////////////////////////
// ----------------------- Input File ---------------------- //
///////////////////////////////////////////////////////////////
/*
Input  file  for  the  1d   neutron   transport  code  in  this 
repository. For instructions on how to use the input file refer 
to the file "manual.hpp". The actual program is run in the file 
"solver.cpp", and SHOULD NOT be modified. All of the  functions
are located in the directory "library" that parallels the "src" 
directory.
*/
///////////////////////////////////////////////////////////////
// ------------------- Problem Parameters ------------------ //
///////////////////////////////////////////////////////////////

constexpr int             SN        = 32;
const std::vector<double> TOLERANCE = {1e-6, 1e-9};
constexpr double          ALPHA     = 0.5;

///////////////////////////////////////////////////////////////
// -------------------- Problem Geometry ------------------- //
///////////////////////////////////////////////////////////////

const std::vector<int>       CELLS  = {100};
const std::vector<double>    BOUNDS = {0.0, 100.0};

const std::string PROBLEM_TYPE ("source");

const std::string BOUNDARY_L   ("vacuum");

const std::string BOUNDARY_R   ("vacuum");

///////////////////////////////////////////////////////////////
// -------------------- Source Function -------------------- //
///////////////////////////////////////////////////////////////

const auto SOURCE_FUNCTION = [](auto&& x, auto&& mu){
			       double s = 1.0;
			       return s + 0.0*x + 0.0*mu; };

///////////////////////////////////////////////////////////////
// -------------------- Material Setup --------------------- //
///////////////////////////////////////////////////////////////

// --------------- Scattering Cross Sections --------------- //
const std::vector<double> sigS1{0.99};

// ------------------- Create Materials -------------------- //
const solver::Material mat1( 1.0, sigS1, 0.0 );

// ---------------- Put Materials in Vector ---------------- //
const std::vector<solver::Material> MATS{mat1};

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
