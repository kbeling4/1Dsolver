template<typename N, typename T>
auto make_cell_centers(N& Nx, T& Xmin, T& Xmax) {
  std::vector<T> grid(Nx, 0);
  T delta = (Xmax-Xmin)/Nx;
  for( int i=0; i<Nx; ++i ){
    grid[i] = ((double) i/Nx)*( Xmax - Xmin ) + Xmin + delta/2;
  }
  return grid;
};

template<typename N, typename T>
auto make_cell_bounds(N& Nx, T& Xmin, T& Xmax){
  std::vector<T> grid(Nx+1, 0);
  T delta = (Xmax-Xmin)/Nx;
  for( int i=0; i<Nx+1; ++i ){
    grid[i] = ((double) i/Nx)*( Xmax - Xmin ) + Xmin;
  }
  return grid;
};
