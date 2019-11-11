template<typename T>
double compute_error(T&& scalarP, T&& scalarM, int Nx){
  std::vector<double> error(Nx, 0.0);
  for( int i = 0; i < Nx; ++i ){
    error[i] = std::abs(scalarP[i] - scalarM[i])/scalarP[i];
  }
  auto err = std::max_element(error.begin(), error.end());
  return *err;
}
