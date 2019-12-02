template<typename T, typename O>
auto computeScalarFlux(T&& scalar, T&& angleCenter, O&& ord, int Nx){
  for( int i = 0; i < Nx; ++i ){
    scalar[i] = 0;
    for( int n = 0; n < static_cast<int>(ord.size()); ++n ){
      scalar[i] += angleCenter[Nx*n + i]*ord[n].weight;
    }
  }
  return scalar;
}
