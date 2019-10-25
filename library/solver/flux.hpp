template<typename S, typename F, typename O>
auto compute_scalar_flux(S&& scalar, F&& a_flux_c, O&& ord){
  for( unsigned int i = 0; i < a_flux_c[0].size(); ++i ){
    scalar[i] = 0;
    for( unsigned int n = 0; n < ord.size(); ++n ){
      scalar[i] += a_flux_c[n][i]*ord[n].weight;
    }
  }
  return scalar;
}
