template<typename O, typename A>
void make_boundary(std::string type, O&& ord, A&& angle_b, double gamma = 1.0){
  if(type == "isotropic_l"){
    isotropic_l(ord, angle_b);
  } else if (type == "beam_l"){
    beam_l(ord, angle_b);
  } else if (type == "vacuum_l"){
    vacuum_l(ord, angle_b);
  } else if (type == "albedo_l"){
    albedo_l(ord, angle_b, gamma);
  } else if (type == "isotropic_r") {
    isotropic_r(ord, angle_b);
  } else if (type == "beam_r"){
    beam_r(ord, angle_b);
  } else if (type == "vacuum_r"){
    vacuum_r(ord, angle_b);
  } else if (type == "albedo_r"){
    albedo_r(ord, angle_b, gamma);
  }
}

template<typename O, typename A>
void beam_l(O&& ord, A&& angle_b){
  unsigned int N = ord.size();
  angle_b[N-1][0] = 1/ord[N-1].value;
}

template<typename O, typename A>
void isotropic_l(O&& ord, A&& angle_b){
  double sum = 0.0;
  for( unsigned int n = static_cast<unsigned int>(ord.size()/2); n < ord.size(); ++n){
    sum += ord[n].value * ord[n].weight;
  }
  for( unsigned int n = 0; n < ord.size(); ++n ){
    if( n >= static_cast<unsigned int>(ord.size()/2) ){
      angle_b[n][0] = 1/sum;
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
void albedo_l(O&& ord, A&& angle_b, double gamma){
  unsigned int Sn = ord.size();
  for( unsigned int n = 0; n < Sn/2; ++n ){
    angle_b[Sn - n - 1][0] = gamma*angle_b[n][0];
  }
}

template<typename O, typename A>
void beam_r(O&& ord, A&& angle_b){
  unsigned int Nx = angle_b[0].size();
  angle_b[0][Nx-1] = 1/std::abs(ord[0].value);
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
void vacuum_r(O&& ord, A&& angle_b){
  unsigned int Nx = angle_b[0].size();
  for( unsigned int n = 0; n < ord.size(); ++n ){
    if( n < static_cast<unsigned int>(ord.size()/2) ){
      angle_b[n][Nx-1] = 0.0;
    }
  }
}

template<typename O, typename A>
void albedo_r(O&& ord, A&& angle_b, double gamma){
  unsigned int Nx = angle_b[0].size();
  unsigned int Sn = ord.size();
  for( unsigned int n = Sn/2; n < Sn; ++n ){
    angle_b[Sn - n - 1][Nx-1] = gamma*angle_b[n][Nx-1];
    angle_b[n][Nx] = (1-gamma)*angle_b[n][Nx-1];
  }
}
