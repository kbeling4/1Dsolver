#include "solver.hpp"

std::size_t Nx = 10;
double Xmin = 0.0;
double Xmax = 1.0;
std::size_t Sn = 4;
unsigned int l = 1;


// Nuclear Data
struct material1{
  double Sig_t = 3; // cm^-1
  std::vector<double> Sig_s{0.5}; // cm^-1
  double nuSig_f = 0.0;
};

auto source = [](auto&& x, auto&& mu){ return 0; };


int main(){
  material1 mat1;
  auto cen = solver::make_cell_centers(Nx, Xmin, Xmax);
  auto bon = solver::make_cell_bounds(Nx, Xmin, Xmax);
  auto ord = solver::get_ordinates(Sn, -1.0, 1.0);

  std::vector< std::vector<double> > angle_flux_c( Sn, std::vector<double> (Nx,   0.0) );
  std::vector< std::vector<double> > angle_flux_b( Sn, std::vector<double> (Nx+1, 0.0) );
  std::vector< std::vector<double> > right(Sn, std::vector<double> (Nx, 0.0) );

  std::string type ("isotropic");
  solver::make_boundary(type, ord, angle_flux_b);  

  for( int i = 0; i < 100; ++i){
    solver::compute_right(right, angle_flux_c, ord, source, mat1);
    solver::sweep(mat1, angle_flux_c, angle_flux_b, right, ord, bon);
  }

  solver::printX(cen);
  solver::printMU(ord);
  solver::printFlux(angle_flux_c, "cFlux.txt");
  solver::printFlux(angle_flux_b, "bFlux.txt");
  
  std::cout << "--------------" << std::endl;
  
  for( auto thing : angle_flux_b ){
    for( auto point : thing ){
      std::cout << point << " ";
    }
    std::cout << "\n";
  }
}
