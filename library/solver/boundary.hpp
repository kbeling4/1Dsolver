template<typename O, typename A>
void make_boundary(std::string type, O&& ord, A&& angle_b){
  if(type == "isotropic_l"){
    isotropic_l(ord, angle_b);
  } else if (type == "isotropic_r") {
    isotropic_r(ord, angle_b);
  } else if (type == "vacuum_l"){
    vacuum_l(ord, angle_b);
  } else if (type == "vacuum_r"){
    vacuum_r(ord, angle_b);
  }
}


template<typename O, typename A>
void isotropic_l(O&& ord, A&& angle_b){
  double sum = 0.0;
  for( unsigned int n = static_cast<unsigned int>(ord.size()/2); n < ord.size(); ++n){
    sum += ord[n].value * ord[n].weight;
  }
  for( unsigned int n = 0; n < ord.size(); ++n ){
    if( n >= static_cast<unsigned int>(ord.size()/2) ){
      angle_b[n][0] = 1/sum/2;
    }
  }
}

template<typename O, typename A>
void isotropic_r(O&& ord, A&& angle_b){
  double sum = 0.0;
  for( unsigned int n = static_cast<unsigned int>(ord.size()/2); n < ord.size(); ++n){
    sum += ord[n].value * ord[n].weight;
  }
  unsigned int Nx = angle_b[0].size();
  for( unsigned int n = 0; n < ord.size(); ++n ){
    if( n < static_cast<unsigned int>(ord.size()/2) ){
      angle_b[n][Nx-1] = 1/sum;
    }
  }
}

template<typename O, typename A>
void vacuum_l(O&& ord, A&& angle_b){
  for( unsigned int n = 0; n < ord.size(); ++n ){
    if( n >= static_cast<unsigned int>(ord.size()/2) ){
      angle_b[n][0] = 0.0;
    }
  }
}

template<typename O, typename A>
void vacuum_r(O&& ord, A&& angle_b){
  unsigned int Nx = angle_b[0].size();
  for( unsigned int n = 0; n < ord.size(); ++n ){
    if( n < static_cast<unsigned int>(ord.size()/2) ){
      angle_b[n][Nx-1] = 0.0;
    }
  }
}
