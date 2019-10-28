template<typename T>
double compute_error(T&& scalar_p, T&& scalar_m){
  unsigned int Nx = scalar_p.size();
  std::vector<double> error(Nx, 0.0);
  for( unsigned int i = 0; i < Nx; ++i ){
    error[i] = std::abs(scalar_p[i] - scalar_m[i])/scalar_p[i];
  }
  auto err = std::max_element(error.begin(), error.end());
  return *err;
}
