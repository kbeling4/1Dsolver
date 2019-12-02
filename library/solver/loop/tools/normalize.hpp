template<typename T>
void getNormal(T&& scalar, int Nx){
  double max = scalar[0];
  for (int i = 0; i < Nx; ++i){
    if ( scalar[i] > max ){
      max = scalar[i];
    }
  }

  for (int i = 0; i < Nx; ++i){
    scalar[i] = scalar[i]/max;
  }
}
