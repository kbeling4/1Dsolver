#include "source/legendre.hpp"

template<typename M, typename O, typename A>
double compute_scatter(M&& mat, O&& ord, A&& angle_flux, double mu_n, int i){
  double scatter = 0.0;
  for( unsigned int l = 0; l < mat.Sig_s.size(); ++l ){
    for( unsigned int n = 0; n < ord.size(); ++n ){
      auto mu = ord[n].value;
      auto temp = ((2*(double)l + 1)/((double)2))*mat.Sig_s[l]
	*legendre::Pn(l, mu_n)*ord[n].weight*legendre::Pn(l, mu)
	*angle_flux[n][i];
      scatter += temp;
    }
  }
  return scatter;
}


template<typename M, typename O, typename A>
double compute_fission(M&& mat, O&& ord, A&& angle_flux, int i){
  double fission = 0.0;  
  for( unsigned int n=0; n < ord.size(); ++n ){
    fission += (mat.nuSig_f/2)*ord[n].weight*angle_flux[n][i];
  }
  return fission;
}


template<typename M, typename O, typename A>
double compute_cell_source(M&& mat, O&& ord, A&& angle_flux, double mu_n, int i){
  return compute_scatter(mat, ord, angle_flux, mu_n, i)
    + compute_fission(mat, ord, angle_flux, i);;
}


template<typename F, typename N, typename O>
auto compute_source(F&& func, N&& Nx, O&& ord){
  std::vector< std::vector<double>> source(ord.size(), std::vector<double> (Nx, 0.0));
  for( unsigned int n = 0; n < ord.size(); ++n ){
    for( unsigned int i = 0; i < Nx; ++i ){
      source[n][i] = func(i, ord[n].value)/2;
    }
  }
  return source;
}


template<typename R, typename A, typename O, typename F, typename M>
void compute_right(R&& right, A&& angle_flux, O&& ord, F&& func, M&& mat){
  double Sn = ord.size();
  auto Nx = angle_flux[0].size();
  auto source = compute_source(func, Nx, ord);

  for( unsigned int n = 0; n < Sn; ++n ){
    for( unsigned int i = 0; i < Nx; ++i ){
      right[n][i] = compute_cell_source(mat, ord, angle_flux, ord[n].value, i) + source[n][i];
    }
  }
}
