#include "solver.hpp"

// Global Constants
unsigned int Nx = 100;
double Xmin  = 0.0;
double Xmax  = 5.0;
double alpha = 0.5;
int Sn = 8;
unsigned int l = 1; // Scattering order
double tol = 1e-6;

// Left current boundary condition
std::string type_l ("beam");

// Right current boundary condition
std::string type_r ("vacuum");

// Nuclear Data
struct Material{
  double Sig_t = 1.0; // cm^-1
  std::vector<double> Sig_s{0.50}; // cm^-1
  double Sig_a = Sig_t - Sig_s[0];
  double nuSig_f = 0.0;
};

// Source Function
auto source = [](auto&& x, auto&& mu){ return 0.0*x + 0.0*mu; };


int main(){
  // Setup materials
  Material mat1;

  // Output running parameters
  std::cout.precision(3);
  std::cout << "----------------------------- \n";
  std::cout << "      Input Parameters \n";
  std::cout << "----------------------------- \n";
  std::cout << std::scientific << "L     = " << Xmax << "\n";
  std::cout << "I     = " << Nx << "\n";
  std::cout << "Sn    = " << Sn << "\n";
  std::cout << "alpha = " << alpha << "\n";
  std::cout << "tol   = " << tol << "\n";
  std::cout << "\n";
  std::cout << "-- Nuclear Data -- \n";
  std::cout << std::scientific << "Sig_s = " << mat1.Sig_s[0] << "\n";
  std::cout << std::scientific << "Sig_f = " << mat1.nuSig_f << "\n";
  std::cout << std::scientific << "Sig_t = " << mat1.Sig_t << "\n";
  std::cout << "\n";
  std::cout << "-- Boundary Conditions -- \n";
  std::cout << "Left:  " << type_l << "\n";
  std::cout << "Right: " << type_r << "\n";

  std::cout << "----------------------------- \n";
  std::cout << "      Problem Running \n";
  std::cout << "----------------------------- \n";

  
  // Setup spatial grids, and compute ordinates
  auto cen = solver::make_cell_centers(Nx, Xmin, Xmax);
  auto bon = solver::make_cell_bounds(Nx, Xmin, Xmax);
  auto ord = solver::get_ordinates(Sn, -1.0, 1.0);

  // Zero out all vectors and arrays
  std::vector< std::vector<double> > angle_flux_c( Sn, std::vector<double> (Nx,   0.0) );
  std::vector< std::vector<double> > angle_flux_b( Sn, std::vector<double> (Nx+1, 0.0) );
  std::vector< std::vector<double> > right(Sn, std::vector<double> (Nx, 0.0) );
  std::vector<double> scalar_p(Nx, 0.0);
  std::vector<double> scalar_m(Nx, 0.0);

  // Iteration loop
  int it = 0;
  double err = 0.0;
  bool cond = true;
  do {
    // set boundary conditions
    solver::make_boundary_l(type_l, ord, angle_flux_b);
    solver::make_boundary_r(type_r, ord, angle_flux_b);

    // compute phi_(k-1)
    solver::compute_scalar_flux(scalar_m, angle_flux_c, ord);

    // compute source on right
    solver::compute_right(right, angle_flux_c, ord, source, mat1);

    // sweep 
    solver::sweep(mat1, angle_flux_c, angle_flux_b, right, ord, bon, alpha);

    // compute phi_(i)
    solver::compute_scalar_flux(scalar_p, angle_flux_c, ord);

    // compute error
    err = solver::compute_error(scalar_p, scalar_m);
    if( err <= tol || it >= 1e5 ) cond = false;
    it += 1;
  } while(cond);

  std::cout << "Number of iterations:  " << it << "\n";
  std::cout << "Final error:       " << std::scientific << err << "\n";

  // Print particle balance
  std::cout << "----------------------------- \n";
  std::cout << "      Particle Balance \n";
  std::cout << "----------------------------- \n";

  // Get particle balance
  auto bal = solver::get_balance(scalar_p, angle_flux_b, ord, bon, cen, mat1, source);
  std::cout << "------------------ \n";
  std::cout << std::scientific << "Particle balance:  " << bal << "\n";


  std::cout << "----------------------------- \n";
  std::cout << "Plotter located here: cd ../../python/. \n";
  
  solver::printScalar(scalar_p, "scalar.txt");
  solver::printX(cen);  
}
