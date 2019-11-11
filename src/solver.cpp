#include "solver.hpp"

// Global Constants
const std::vector<int> cells{100};
const std::vector<double> bounds{0.0, 2.0};
const double alpha = 0.5;
const int Sn = 16;
const double tol = 1e-6;

// Left current boundary condition
std::string typeL ("isotropic");

// Right current boundary condition
std::string typeR ("vacuum");

// Nuclear Data
class Material{
public:
  double sigT;
  std::vector<double> sigS;
  double sigA;
  double nuSigF;

  Material(double sigT, std::vector<double> sigS, double nuSigF)
    : sigT(sigT), sigS(sigS), nuSigF(nuSigF)
  {
    sigA = sigT - sigS[0];
  }
};

// Source Function
auto sourceFunc = [](auto&& x, auto&& mu){ return 0.0*x + 0.0*mu; };


int main(){
  std::vector<double> sigS1{1.0};
  Material mat1(2.0, sigS1, 0.0);

  std::vector<Material> mats{mat1};

  int Nx = 0;
  for( unsigned int i =0; i < bounds.size(); ++i ){
    Nx += cells[i];
  }
  
  double* xCenters = (double*)calloc(Nx, sizeof(double));
  double* xBounds  = (double*)calloc(Nx+1, sizeof(double));
  double* scalarP  = (double*)calloc(Nx, sizeof(double));
  double* scalarM  = (double*)calloc(Nx, sizeof(double));
  double* idVec    = (double*)calloc(Nx, sizeof(double));
  double* right    = (double*)calloc(Sn*Nx, sizeof(double));
  double* source   = (double*)calloc(Sn*Nx, sizeof(double));
  double* angleCenter = (double*)calloc(Sn*Nx, sizeof(double));
  double* angleBound  = (double*)calloc(Sn*(Nx+1), sizeof(double));

  
  // Setup spatial grids, and compute ordinates
  solver::makeCellCenters(xCenters, bounds, cells);
  solver::makeCellBounds(xBounds, bounds, cells);
  solver::makeIdVec(idVec, bounds, cells);
  auto ord = solver::get_ordinates(Sn, -1.0, 1.0);

  // Iteration loop
  int it = 0;
  double err = 0.0;
  bool cond = true;

  do {
    // Make boundary conditions
    solver::makeBoundaryL(angleBound, ord, Nx, typeL);
    solver::makeBoundaryR(angleBound, ord, Nx, typeR);
    
    solver::computeScalarFlux(scalarM, angleCenter, ord, Nx);
    
    solver::computeSource(sourceFunc, source, xCenters, ord, Nx);
    solver::computeRight(right, angleCenter, source, ord, mats, idVec, Nx);

    solver::sweep(angleCenter, angleBound, right, ord, mats, xBounds, idVec, Nx, alpha);

    solver::computeScalarFlux(scalarP, angleCenter, ord, Nx);

    // compute error
    err = solver::compute_error(scalarP, scalarM, Nx);
    if( err <= tol || it >= 1e5 ) cond = false;
    it += 1;
    } while(cond);


  solver::printX(xCenters, Nx);
  solver::printScalar(scalarP, Nx, "scalar.txt");
  // auto bal = solver::get_balance(scalar_p, angle_flux_b, ord, bon, cen, mat1, source);

  // for(int i = 0; i < Nx; ++i){
  //   std::cout << scalarP[i] << "\n";
  // }

  free(xCenters);
  free(xBounds);
  free(scalarP);
  free(scalarM);
  free(right);
  free(idVec);
  free(source);
  free(angleCenter);
  free(angleBound);

  std::cout << "Number of iterations:  " << it << "\n";
  std::cout << "Final error:       " << std::scientific << err << "\n";

  // // Print particle balance
  // std::cout << "----------------------------- \n";
  // std::cout << "      Particle Balance \n";
  // std::cout << "----------------------------- \n";

  // // Get particle balance
  // std::cout << "------------------ \n";
  // std::cout << std::scientific << "Particle balance:  " << bal << "\n";


  // std::cout << "----------------------------- \n";
  // std::cout << "Plotter located here: cd ../../python/. \n";
  
  // solver::printScalar(scalar_p, "scalar.txt");
  // solver::printX(cen);  
}
