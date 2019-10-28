#include "solver.hpp"

// Global Constants
unsigned int Nx = 100;
double Xmin  = 0.0;
double Xmax  = 100.0;
double alpha = 0.5;
int Sn = 8;
unsigned int l = 1;
double tol = 1e-8;


// Nuclear Data
struct material1{
  double Sig_t = 1.0; // cm^-1
  std::vector<double> Sig_s{0.99}; // cm^-1
  double Sig_a = Sig_t - Sig_s[0];
  double nuSig_f = 0.0;
};

// Source Function
auto source = [](auto&& x, auto&& mu){ return 0.0*x + 0.0*mu; };


int main(){
  // Setup materials
  material1 mat1;

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

  // Left current boundary condition
  std::string type_l ("beam_l");

  // Right current boundary condition
  std::string type_r ("vacuum_r");

  // Iteration loop
  int it = 0;  
  for( int i = 0; i < 1e5; ++i){
    // set boundary conditions
    solver::make_boundary(type_l, ord, angle_flux_b);
    solver::make_boundary(type_r, ord, angle_flux_b, 1.0);

    // compute phi_(k-1)
    solver::compute_scalar_flux(scalar_m, angle_flux_c, ord);

    // compute source on right
    solver::compute_right(right, angle_flux_c, ord, source, mat1);

    // sweep 
    solver::sweep(mat1, angle_flux_c, angle_flux_b, right, ord, bon, alpha);

    // compute phi_(i)
    solver::compute_scalar_flux(scalar_p, angle_flux_c, ord);

    // compute error
    double err = solver::compute_error(scalar_p, scalar_m);
    it += 1;
    if( err <= tol ){
      break;
    }
  }

  // Get particle balance
  auto bal = solver::get_balance(scalar_p, angle_flux_b, ord, bon, mat1);

  // Print results
  std::cout << "Solver Complete \n";
  std::cout << "- number of iterations: " << it << "\n";
  std::cout << "- particle balance: " << bal << "\n";
  std::cout << scalar_p[0] << "\n";

  solver::printScalar(scalar_p, "scalar.txt");
  solver::printX(cen);  
}
