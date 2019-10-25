template<typename T>
std::vector<T> make_cell_centers(unsigned int Nx, T& Xmin, T& Xmax) {
  std::vector<T> grid(Nx, 0);
  T delta = (Xmax-Xmin)/Nx;
  for( unsigned int i=0; i<Nx; ++i ){
    grid[i] = (static_cast<double>(i)/Nx)*( Xmax - Xmin ) + Xmin + delta/2;
  }
  return grid;
}

template<typename T>
std::vector<T> make_cell_bounds(unsigned int Nx, T& Xmin, T& Xmax){
  std::vector<T> grid(Nx+1, 0);
  for( unsigned int i=0; i<Nx+1; ++i ){
    grid[i] = (static_cast<double>(i)/Nx)*( Xmax - Xmin ) + Xmin;
  }
  return grid;
}
