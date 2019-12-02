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

const std::vector<int>       CELLS  = {3000, 3000};
const std::vector<double>    BOUNDS = {0.0, 2.0, 5.0};

const std::string PROBLEM_TYPE ("k-value");

const std::string BOUNDARY_L   ("albedo");

const std::string BOUNDARY_R   ("vacuum");

const bool NORMALIZE_SCALAR = true;

const std::vector<bool> PRINTER = {true, false, true};

///////////////////////////////////////////////////////////////
// -------------------- Source Function -------------------- //
///////////////////////////////////////////////////////////////

const auto SOURCE_FUNCTION = [](auto&& x){
			       double s = 0.0;

			       // if( x < 2.0 ){
			       // 	 s = 50.0;
			       // } else if(x > 5.0 && x < 6.0){
			       // 	 s = 1.0;
			       // }
				 
			       return s + 0.0*x; };

///////////////////////////////////////////////////////////////
// -------------------- Material Setup --------------------- //
///////////////////////////////////////////////////////////////

// --------------- Scattering Cross Sections --------------- //
// const std::vector<double> sigS1{0.0};
// const std::vector<double> sigS2{0.0};
// const std::vector<double> sigS3{0.0};
// const std::vector<double> sigS4{0.9};
// const std::vector<double> sigS5{0.9};

const std::vector<double> sigS1{0.5};
const std::vector<double> sigS2{0.4};

// ------------------- Create Materials -------------------- //
// const solver::Material mat1(50.0, sigS1, 0.0 );
// const solver::Material mat2( 5.0, sigS2, 0.0 );
// const solver::Material mat3( 0.0, sigS3, 0.0 );
// const solver::Material mat4( 1.0, sigS4, 0.0 );
// const solver::Material mat5( 1.0, sigS5, 0.0 );

const solver::Material mat1( 1.0, sigS1, 1.0 );
const solver::Material mat2( 0.8, sigS2, 0.0 );

// ---------------- Put Materials in Vector ---------------- //
const std::vector<solver::Material> MATS{mat1, mat2};

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
