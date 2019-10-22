template<typename O, typename A>
auto make_boundary(std::string type, O&& ord, A&& angle_b){
  isotropic(ord, angle_b);
}

template<typename O, typename A>
auto isotropic(O&& ord, A&& angle_b){
  double sum = 0.0;
  for( int n = int(ord.size()/2); n < ord.size(); ++n){
    sum += ord[n].value * ord[n].weight;
  }
  auto Nx = angle_b[0].size();
  for( int n = 0; n < ord.size(); ++n ){
    if( n < int(ord.size()/2) ){
      angle_b[n][Nx-1] = 1/sum;
    } else {
      angle_b[n][0] = 1/sum;
    }
  }
};
