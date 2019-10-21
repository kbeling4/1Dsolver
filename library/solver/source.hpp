#include "source/legendre.hpp"

template<typename M, typename O, typename A, typename U, typename I>
auto compute_scatter(M&& mat, O&& ord, A&& angle_flux, U mu_n, I i){
  double scatter = 0.0;
  for( int l = 0; l < mat.Sig_s.size(); ++l ){
    for( int n = 0; n < ord.size(); ++n ){
      auto mu = ord[n].value;
      auto temp = ((2*(double)l + 1)/((double)2))*mat.Sig_s[l]
	*legendre::Pn(l, mu_n)*ord[n].weight*legendre::Pn(l, mu)
	*angle_flux[n][i];
      scatter += temp;
    }
  }
  return scatter;
};

template<typename M, typename O, typename A, typename I>
auto compute_fission(M&& mat, O&& ord, A&& angle_flux, I i){
  double fission = 0.0;  
  for( int n=0; n < ord.size(); ++n ){
    fission += (mat.nuSig_f/2)*ord[n].weight*angle_flux[n][i];
  }
  return fission;
};

template<typename M, typename O, typename A, typename N, typename I>
auto compute_cell_source(M&& mat, O&& ord, A&& angle_flux, N mu_n, I i){
  auto scatter = compute_scatter(mat, ord, angle_flux, mu_n, i);
  auto fission = compute_fission(mat, ord, angle_flux, i);
  return scatter + fission;
};

template<typename S, typename N>
auto compute_source(S&& func, N&& Nx){
  std::vector<double> source(Nx, 0.0);
  for( int i = 0; i < Nx; ++i ){
    source[i] = func(i);
  }
  return source;
};

template<typename M, typename O, typename A, typename F>
auto compute_right(M&& mat, O&& ord, A&& angle_flux, F&& func){
  double Sn = ord.size();
  auto Nx = angle[0].size();
  std::vector< std::vector<double> > right(Sn, std::vector<double> (Nx, 0.0) );
  for( int n = 0; n < Sn; ++n ){
    for( int i = 0; i < Nx; ++i ){
      right[n][i] = compute_cell_source(mat, ord, angle_flux, ord[n].value, i);
    }
  }
  return right;
};
