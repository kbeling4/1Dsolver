# 1D Neutron Transport Solver
This repository contains a one dimensional Sn neutron transport solver that solves both the source and k-eigenvalue problem using a weighted diamond difference method for the spatial variable.

## Build Code Using CMake
Requirements:
* CMake version 3.10 or later
* C++ std::17 or later

This code was developed using using the following compilers:
* gcc/6.5.0
* gcc/9.2.0
* llvm/7.1.0
* llvm/9.0.0

Setup and Build Code:
1. Clone this repository
    * `git clone https://github.com/kbeling4/1Dsolver.git`
2. Use CMake to generate the make files and then make
    * `mkdir build`
    * `cd build`
    * `cmake ..`
    * `make`
    
## Running the Code
The file [input.hpp](https://github.com/kbeling4/1Dsolver/blob/master/src/input.hpp) contains all the input parameters for the code, this is where the user can make edits, NO OTHER file should be edited in this repository. All of the input parameters that are availible to the codes user are defined in the file [manual.hpp](https://github.com/kbeling4/1Dsolver/blob/master/src/manual.hpp).
