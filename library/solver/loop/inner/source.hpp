#include "source/legendre.hpp"

template<typename T, typename O, typename M>
double computeScatter(T&& angleCenter, O&& ord, M&& mats, T&& idVec, int Nx, double mu_n, int i){
  double scatter = 0.0;
  for( int l = 0; l < static_cast<int>(mats[idVec[i]].sigS.size()); ++l ){
    for( int n = 0; n < static_cast<int>(ord.size()); ++n ){
      auto mu = ord[n].value;
      auto temp = ((2*static_cast<double>(l) + 1)/2)*mats[idVec[i]].sigS[l]
	*legendre::Pn(l, mu_n)*ord[n].weight*legendre::Pn(l, mu)*angleCenter[n*Nx + i];
      scatter += temp;
    }
  }
  return scatter;
}

template<typename F>
double getSource(double xVal, F&& sourceFunc){
  return sourceFunc(xVal)/2;
}

template<typename T, typename F, typename O, typename M>
void computeRight(T&& right, T&& angleCenter, T&& fissionS, F&& sourceFunc, O&& ord, M&& mats, T&& xCenters,
		  T&& idVec, int Nx){
  for( int n = 0; n < static_cast<int>(ord.size()); ++n ){
    for( int i = 0; i < Nx; ++i ){
      right[n*Nx + i] = computeScatter(angleCenter, ord, mats, idVec, Nx, ord[n].value, i)
	+ fissionS[i] + getSource(xCenters[i], sourceFunc);
    }
  }
}
