template<typename T, typename M>
double updateK(double k, T&& scalarP, T&& scalarM, T&& idVec, M&& mats, T&& xBounds, int Nx){
  double plus  = 0;
  double minus = 0;
  for(int i = 0; i < Nx; ++i){
    plus  += mats[idVec[i]].nuSigF*scalarP[i]*(xBounds[i+1]-xBounds[i]);
    minus += mats[idVec[i]].nuSigF*scalarM[i]*(xBounds[i+1]-xBounds[i]);
  }
  return (k)*(plus/minus);
}

template<typename T, typename O, typename M>
void computeFission(double k, T&& angleCenter, T&& fissionS, O&& ord, M&& mats, T&& idVec, int Nx){
  for( int i = 0; i < Nx; ++i ){
    double fission = 0.0;  
    for( int n = 0; n < static_cast<int>(ord.size()); ++n ){
      fission += (1/k)*(mats[idVec[i]].nuSigF/2)*ord[n].weight*angleCenter[n*Nx + i];
    }
    fissionS[i] = fission;
  }
}

double getKError(double kNew,double kOld){
  return std::abs( kNew - kOld)/kNew;
}

template<typename T>
void updatePhi(T&& outer, T&& inner, int Nx){
  for( int i = 0; i < Nx; ++i ){
    outer[i] = inner[i];
  }
}

template<typename T>
void setToOne(T&& phi, int Nx){
  for( int i = 0; i < Nx; ++i ){
    phi[i] = 1.0;
  }
}

template<typename T, typename O>
void setAngleOne(T&& phi, O&& ord, int Nx){
  for( int i = 0; i < static_cast<int>(ord.size())*(Nx); ++i ){
    phi[i] = 1.0;
  }
}
