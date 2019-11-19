template<typename T, typename O>
double leftLeak(T&& angleBound, O&& ord, int Nx){
  double plus = 0.0;
  double minus = 0.0;
  for( int n = 0; n < static_cast<int>(ord.size()); ++n){
    if( n < static_cast<int>(ord.size()/2) ){
      minus += ord[n].weight*std::abs(ord[n].value)*angleBound[n*(Nx+1)];
    } else {
      plus += ord[n].weight*ord[n].value*angleBound[n*(Nx+1)];
    }
  }
  std::cout << "J^(-) (0) = :  " << std::scientific << minus << std::endl;
  std::cout << "J^(+) (0) = :  " << std::scientific << plus << std::endl;
  return plus - minus;
}

template<typename T, typename O>
double rightLeak(T&& angleBound, O&& ord, int Nx){
  double plus = 0.0;
  double minus = 0.0;
  for( int n = 0; n < static_cast<int>(ord.size()); ++n){
    if( n < static_cast<int>(ord.size()/2) ){
      minus += ord[n].weight*std::abs(ord[n].value)*angleBound[Nx + n*(Nx+1)];
    } else {
      plus += ord[n].weight*ord[n].value*angleBound[Nx + n*(Nx+1)];
    }
  }
  std::cout << "J^(-) (a) = :  " << std::scientific << minus << std::endl;
  std::cout << "J^(+) (a) = :  " << std::scientific << plus << std::endl;
  return plus - minus;
}

template<typename T, typename O, typename M>
double getAbsorb(T&& angleBound, O&& ord, T&& idVec, T&& xBounds, M&& mats, int Nx){
  double abs = 0.0;
  for( int i = 0; i < Nx; ++i ){
    for( int n = 0; n < static_cast<int>(ord.size()); ++n ){
      abs += mats[idVec[i]].sigA*(angleBound[n*(Nx+1)+i+1] + angleBound[n*(Nx+1)+i])*0.5
	*ord[n].weight*(xBounds[i+1] - xBounds[i]);
    }
  }
  std::cout << "absorption  :  " << abs << std::endl;
  return abs;
}

template<typename T, typename M>
double getFission(T&& scalar, T&& idVec, T&& xBounds, M&& mats, int Nx){
  double fis = 0.0;
  for( int i = 0; i < Nx; ++i ){
    fis += 0.5*mats[idVec[i]].nuSigF*scalar[i]*(xBounds[i+1] - xBounds[i]);
  }
  std::cout << "fission     :  " << fis << std::endl;
  return fis;
}

template<typename F, typename T, typename O>
double getSource(F&& sourceFunc, T&& xBounds, O&& ord, int Nx){
  double sum = 0.0;
  for( int i = 0; i < Nx; ++i ){ 
    for( int n = 0; n < static_cast<int>(ord.size()); ++n ){
      sum += sourceFunc(ord[n].value, (xBounds[i+1] + xBounds[i])/2)*ord[n].weight
	*(xBounds[i+1] - xBounds[i]);
    }
  }
  std::cout << "source      :  " << 0.5*sum << std::endl;
  return 0.5*sum;
}

template<typename T, typename F, typename O, typename M>
double getBalance(T&& angleBound, T&& scalar, F&&sourceFunc, O&& ord, M&& mats, T&& idVec, T&& xBounds, int Nx){ 
  double currentLeft  = leftLeak(angleBound, ord, Nx);
  double currentRight = rightLeak(angleBound, ord, Nx);
  double absorbtion   = getAbsorb(angleBound, ord, idVec, xBounds, mats, Nx);
  double fission      = getFission(scalar, idVec, xBounds, mats, Nx);
  double source       = getSource(sourceFunc, xBounds, ord, Nx);
  return currentLeft - currentRight - absorbtion + fission + source;
}
