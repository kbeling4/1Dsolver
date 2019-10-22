#include "sweeper/cell.hpp"

// template<typename M, typename F, typename R, typename O, typename G, typename N>
// auto left_sweep(M mat, F&& a_flux_c, F&& a_flux_b, R right, O ord, G grid, N n){
//   for( int i = a_flux_c[0].size()-1; i > 0; i-- ){
//     double dX = grid[i] - grid[i-1];
//     a_flux_c[n][i] = cell::solve_left(mat, ord, dX, a_flux_b[n][i], right[n][i]);
//   }
//   return a_flux_c;
// };

auto l_sweep = [&](auto mat, auto&& a_flux_c, auto&& a_flux_b, auto right, auto ord,
		   auto grid, auto n){
		 for( int i = a_flux_c[0].size()-1; i >= 0; i-- ){
		   double dX = grid[i] - grid[i-1];
		   a_flux_c[n][i] = cell::solve_left(mat, ord[n].value, dX,
						     a_flux_b[n][i+1], right[n][i]);
		   a_flux_b[n][i] = cell::get_phi_m(a_flux_c[n][i], a_flux_b[n][i+1]);
		 }
	       };

auto r_sweep = [&](auto mat, auto&& a_flux_c, auto&& a_flux_b, auto right, auto ord,
		   auto grid, auto n){
		 for( int i = 0; i < a_flux_c[0].size(); ++i ){
		   double dX = grid[i+1] - grid[i];
		   a_flux_c[n][i] = cell::solve_right(mat, ord[n].value, dX,
						     a_flux_b[n][i], right[n][i]);
		   a_flux_b[n][i+1] = cell::get_phi_p(a_flux_c[n][i], a_flux_b[n][i]);
		 }
	       };

template<typename M, typename F, typename R, typename O, typename G>
auto sweep(M mat, F&& a_flux_c, F&& a_flux_b, R right, O ord, G grid){
  for( int n = 0; n < ord.size(); ++n ){
    if(n < int(ord.size()/2) ){
      l_sweep(mat, a_flux_c, a_flux_b, right, ord, grid, n);
    } else {
      r_sweep(mat, a_flux_c, a_flux_b, right, ord, grid, n);
    }
  }
};
