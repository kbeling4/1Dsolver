//////////////////////////////////////////////////////////////
// -------------- Left boundary conditions -----------------//
//////////////////////////////////////////////////////////////

template<typename T, typename O>
void beamL(T&& angleBound, O&& ord, int Nx){
  angleBound[(Nx+1)*(ord.size()-1)] = 1/ord[ord.size()-1].value;
}

template<typename T, typename O>
void isotropicL(T&& angleBound, O&& ord, int Nx){
  double sum = 0.0;
  for( int n = static_cast<int>(ord.size()/2); n < static_cast<int>(ord.size()); ++n){
    sum += ord[n].value * ord[n].weight;
  }
  for( int n = static_cast<int>(ord.size()/2); n < static_cast<int>(ord.size()); ++n ){
    angleBound[(Nx+1)*(n)] = 1/sum;
  }
}

template<typename T, typename O>
void vacuumL(T&& angleBound, O&& ord, int Nx){
  for( int n = static_cast<int>(ord.size()/2); n < static_cast<int>(ord.size()); ++n ){
    angleBound[(Nx+1)*(n)] = 0.0;
  }
}

template<typename T, typename O>
void albedoL(T&& angleBound, O&& ord, int Nx, double gamma){
  int Sn = ord.size();
  for( int n = 0; n < static_cast<int>(Sn/2); ++n ){
    angleBound[(Nx+1)*Sn - (Nx+1) - n*(Nx+1)] = gamma*angleBound[n*(Nx+1)];
  }
}

template<typename T, typename O>
void makeBoundaryL(T&& angleBound, O&& ord, int Nx, std::string type, double gamma = 1.0){
  if(type == "isotropic"){
    isotropicL(angleBound, ord, Nx);
  } else if (type == "beam"){
    beamL(angleBound, ord, Nx);
  } else if (type == "vacuum"){
    vacuumL(angleBound, ord, Nx);
  } else if (type == "albedo"){
    albedoL(angleBound, ord, Nx, gamma);
  }
}

//////////////////////////////////////////////////////////////
// ------------- Right boundary conditions -----------------//
//////////////////////////////////////////////////////////////
template<typename T, typename O>
void beamR(T&& angleBound, O&& ord, int Nx){
  angleBound[(Nx)] = 1/ord[0].value;
}

template<typename T, typename O>
void isotropicR(T&& angleBound, O&& ord, int Nx){
  double sum = 0.0;
  for( int n = static_cast<int>(ord.size()/2); n < static_cast<int>(ord.size()); ++n){
    sum += ord[n].value * ord[n].weight;
  }
  for( int n = 0; n < static_cast<int>(ord.size()/2); ++n ){
    angleBound[n*(Nx+1) + Nx] = 1/sum;
  }
}

template<typename T, typename O>
void vacuumR(T&& angleBound, O&& ord, int Nx){
  for( int n = 0; n < static_cast<int>(ord.size()/2); ++n ){
    angleBound[n*Nx + Nx] = 0.0;
  }
}

template<typename T, typename O>
void albedoR(T&& angleBound, O&& ord, int Nx, double gamma){
  int Sn = ord.size();
  for( int n = static_cast<int>(Sn/2); n < static_cast<int>(Sn); ++n ){
    angleBound[(Sn - n)*(Nx + 1) - 1] = gamma*angleBound[n*(Nx+1) + Nx];
  }
}

template<typename T, typename O>
void makeBoundaryR(T&& angleBound, O&& ord, int Nx, std::string type, double gamma = 1.0){
  if (type == "isotropic") {
    isotropicR(angleBound, ord, Nx);
  } else if (type == "beam"){
    beamR(angleBound, ord, Nx);
  } else if (type == "vacuum"){
    vacuumR(angleBound, ord, Nx);
  } else if (type == "albedo"){
    albedoR(angleBound, ord, Nx, gamma);
  }
}
