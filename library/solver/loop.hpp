#include "loop/inner.hpp"
#include "loop/outer.hpp"
#include "loop/tools.hpp"

template<typename M, typename F>
void looper(std::vector<int> cells, std::vector<double> bounds, std::vector<std::string> params, M&& mats,
	    F&& sourceFunc, double alpha, int Sn, std::vector<double> tol, bool normalize,
	    std::vector<bool> pParams){

  // Compute number of cells
  int Nx = 0;
  for( unsigned int i =0; i < bounds.size(); ++i ){
    Nx += cells[i];
  }

  // Allocate variables to the stack
  double* xCenters = (double*)calloc(Nx, sizeof(double));
  double* xBounds  = (double*)calloc(Nx+1, sizeof(double));

  double* scalarP  = (double*)calloc(Nx, sizeof(double));
  double* scalarM  = (double*)calloc(Nx, sizeof(double));

  double* scalarPl = (double*)calloc(Nx, sizeof(double));
  double* scalarMi = (double*)calloc(Nx, sizeof(double));
  double* fissionS = (double*)calloc(Nx, sizeof(double));
  
  double* idVec    = (double*)calloc(Nx, sizeof(double));

  double* right     = (double*)calloc(Sn*Nx, sizeof(double));
  double* angleCenter = (double*)calloc(Sn*Nx, sizeof(double));
  double* angleBound  = (double*)calloc(Sn*(Nx+1), sizeof(double));

  // Setup Problem
  tools::makeCellCenters(xCenters, bounds, cells);
  tools::makeCellBounds(xBounds, bounds, cells);
  tools::makeIdVec(idVec, cells);
  auto ord = tools::get_ordinates(Sn, -1.0, 1.0);

  // Setup k-value problem
  outer::setToOne(scalarP, Nx);
  outer::setToOne(scalarM, Nx);
  outer::setAngleOne(angleCenter, ord, Nx);  

  std::vector<double> k{1.0};
  std::vector<double> errOut;
  std::vector<double> errIn;
  int itK = 0;
  int itI = 0;
  
  bool condK = true;
  do {
    // Update Phi
    outer::updatePhi(scalarMi, scalarP, Nx);
    
    // Compute Fission Source
    outer::computeFission(k[itK], angleCenter, fissionS, ord, mats, idVec, Nx);

    // Setup inner Loop
    bool cond = true;
    int it = 0;
    do {
      // Boundary conditions
      inner::makeBoundaryL(angleBound, ord, Nx, params[1]);
      inner::makeBoundaryR(angleBound, ord, Nx, params[2]);
    
      // Get Scalar Flux
      inner::computeScalarFlux(scalarM, angleCenter, ord, Nx);

      // Compute Right source
      inner::computeRight(right, angleCenter, fissionS, sourceFunc, ord, mats, xCenters, idVec, Nx);

      // Sweep from left to right
      inner::sweep(angleCenter, angleBound, right, ord, mats, xBounds, idVec, Nx, alpha);

      // Compute new scalar flux
      inner::computeScalarFlux(scalarP, angleCenter, ord, Nx);

      // compute error
      errIn.push_back(tools::compute_error(scalarP, scalarM, Nx));
      if( errIn[itI] < tol[0] || it >= 1e5 ) {
	cond = false; }
      it  += 1;
      itI += 1;
    } while(cond);
    
    if(params[0] == "k-value") {
      outer::updatePhi(scalarPl, scalarP, Nx);
      k.push_back (outer::updateK(k[itK], scalarPl, scalarMi, idVec, mats, xBounds, Nx));
      errOut.push_back (outer::getKError(k[itK+1], k[itK]));
      if( errOut[itK] < tol[1] || itK >= 1e3 ) condK = false;
      itK += 1;
    } else {
      condK = false;
    }

  } while(condK);
  
  // Print outputs
  std::cout << "--------------------------\n";
  std::cout << "----- Output Values ------\n";
  std::cout << "--------------------------\n";
  std::cout << std::endl;
  if(params[0] == "k-value"){
    std::cout << "k-value:        " << k[itK] << std::endl;
    std::cout << "k-value Err:    " << errOut[itK-1] << std::endl;
    std::cout << "Total Flux Err: " << errIn[itI-1] << std::endl;
    std::cout << "k-value Itt:    " << itK << std::endl;
    std::cout << "Total Flux Itt: " << itI << std::endl;
    std::cout << std::endl;
  } else {
    std::cout << "Scalar Flux Err: " << errIn[itI-1] << std::endl;
    std::cout << "Scalar Flux Itt: " << itI << std::endl;
    std::cout << std::endl;
  }
  
  std::cout << "--------------------------\n";
  std::cout << "---- Particle Balance ----\n";
  std::cout << "--------------------------\n";
  std::cout << std::endl;
  
  // Particle Balance
  double bal = tools::getBalance(angleBound, scalarP, sourceFunc, ord, mats, idVec, xBounds, k[itK], Nx);
  std::cout << "total bal   :  " << bal << std::endl;
  std::cout << std::endl;
  std::cout << "--------------------------\n";

  // Normalize Scalar Flux
  if (normalize){
    tools::getNormal(scalarP, Nx);
  }

  // Print Results to File
  tools::printer(pParams, scalarP, xCenters, errIn, errOut, k, Nx);
  
  // Free all heap allocations
  free(xCenters);
  free(xBounds);
  free(scalarP);
  free(scalarM);
  free(scalarPl);
  free(scalarMi);
  free(fissionS);
  free(right);
  free(idVec);
  free(angleCenter);
  free(angleBound);
}
