///////////////////////////////////////////////////////////////
// ------------------------- Manual ------------------------ //
///////////////////////////////////////////////////////////////
/*
// -------------------- Code Description ------------------- //
This is a simple 1D  neutron  transport  code. All  parameters, 
geometry,  and  materials  should be  input by the  user in the 
adjacent  file  "input.hpp". The  main devolper on this project 
was Kyle Beling. This file should be left alone.

// ------------------- Problem Paramters ------------------- //
SN: number of ordinates, must be an even number

TOLERANCE: [inner loop error, outer loop error]

ALPHA:  alpha = 0.0 step differencing, 
        alpha = 0.5 diamond differencing

// ------------------- Problem Geometry ------------------- //
CELLS:  vector containing the number of cells in each region, 
        length = number of regions

BOUNDS: vector containing the region boundaries of the problem,
        length = number of regions + 1

PROBLEM_TYPE: two problem types are availible:
        1) k-value: runs a k-value search
	2) source:  no k-search, however a source must 
	            be provided to get a non-zero flux

BOUNDARY_L: left boundary condition, availible options:
        1) isotrpic source
	2) beam
	3) vacuum
	4) albedo (must provide a gamma value)

BOUNDARY_R: right boundary condition, availible options:
        1) isotrpic source
	2) beam
	3) vacuum
	4) albedo (must provide a gamma value)

// -------------------- Source Function -------------------- //
SOURCE_FUNCTION:  input  source function, should be modified to 
        match  desired  input. Note, both x and mu must be used 
	to avoid compiler errors

// -------------------- Material Setup -------------------- //
std::vector<double> sigS(s0, s1, ...):  vector  for   material 
        class containing the materials scattering cross sections.

solver::Material mat(sigT, sigS, nuSigF): creates a material 
        class containing:
	sigT
	sigS
	sigA = sigT - sigS[0]
	nuSigF
  
std::vector<solver::Material> mats{mat1, mat2, ...}: vector 
        containing the materials for each region of the problem
*/
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
