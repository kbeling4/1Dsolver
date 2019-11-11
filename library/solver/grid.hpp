template<typename T, typename B>
void makeCellCenters(T&& xCenters, B&& bounds, std::vector<int> cells) {
  int cell_n = 0;
  int cell_o = 0;
  for( int n = 0; n < static_cast<int>(cells.size()); ++n ){ 
    double delta = (bounds[n+1] - bounds[n])/cells[n];
    cell_n += cells[n];
    for( int i = cell_o; i < cell_n; ++i ){
      xCenters[i] = (static_cast<double>(i-cell_o)/cells[n])*( bounds[n+1] - bounds[n] ) + bounds[n] + delta/2;
    }
    cell_o += cells[n];
  }
}

template<typename T, typename B>
void makeCellBounds(T&& xBounds, B&& bounds, std::vector<int> cells){
  int cell_n = 0;
  int cell_o = 0;
  for( int n = 0; n < static_cast<int>(cells.size()); ++n ){ 
    cell_n += cells[n];
    for( int i = cell_o; i < cell_n+1; ++i ){
      xBounds[i] = (static_cast<double>(i-cell_o)/cells[n])*( bounds[n+1] - bounds[n] ) + bounds[n];
    }
    cell_o += cells[n];
  }
}

template<typename T, typename B>
void makeIdVec(T&& idVec, B&& bounds, std::vector<int> cells) {
  int cell_n = 0;
  int cell_o = 0;
  for( int n = 0; n < static_cast<int>(cells.size()); ++n ){ 
    cell_n += cells[n];
    for( int i = cell_o; i < cell_n; ++i ){
      idVec[i] = n;
    }
    cell_o += cells[n];
  }
}
