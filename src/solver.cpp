#include "solver.hpp"

std::size_t Nx = 20;
double Xmin = 0.0;
double Xmax = 4.0;
std::size_t Sn = 4;
unsigned int l = 4;

// Nuclear Data
struct material1{
  double Sig_t = 2.0; // cm^-1
  std::vector<double> Sig_s{0.5, 0.25, 0.0, 0.05}; // cm^-1
  double nuSig_f = 0.0;
};

auto source = [](auto&& x){ return 1; };

int main(){
  material1 mat;
  auto cen = solver::make_cell_centers(Nx, Xmin, Xmax);
  auto bon = solver::make_cell_bounds(Nx, Xmin, Xmax);
  auto ord = solver::get_ordinates(Sn, -1.0, 1.0);
  
  std::vector< std::vector<double> > angle_flux( Sn, std::vector<double> (2*Nx+1, 1.0) );
  std::vector<double> scalar_flux( Nx );

  auto right = solver::compute_right(mat, ord, angle_flux, Nx);
  for( auto thing : right ){
    for( auto point : thing ){
      std::cout << point << " ";
    }
    std::cout << std::endl;
  }
}
