#include "source/legendre.hpp"

template<typename T, typename O, typename M>
double compute_scatter(T&& angleCenter, O&& ord, M&& mats, T&& idVec, int Nx, double mu_n, int i){
  double scatter = 0.0;
  for( int l = 0; l < static_cast<int>(mats[idVec[i]].sigS.size()); ++l ){
    for( int n = 0; n < static_cast<int>(ord.size()); ++n ){
      auto mu = ord[n].value;
      auto temp = ((2*static_cast<double>(l) + 1)/2)*mats[idVec[i]].sigS[l]
	*legendre::Pn(l, mu_n)*ord[n].weight*legendre::Pn(l, mu)*angleCenter[n*Nx + i];
      scatter += temp; //(1/2)*mats[idVec[i]].sigS[0]*ord[n].weight*angleCenter[n*Nx + i];
    }
  }
  return scatter;
}


// template<typename M, typename O, typename A>
// double compute_fission(M&& mat, O&& ord, A&& angle_flux, int i){
//   double fission = 0.0;  
//   for( unsigned int n=0; n < ord.size(); ++n ){
//     fission += (mat.nuSig_f/2)*ord[n].weight*angle_flux[n][i];
//   }
//   return fission;
// }


template<typename T, typename O, typename M>
double computeCellSource(T&& angleCenter, O&& ord, M&& mats, T&& idVec, int Nx, double mu_n, int i){
  return compute_scatter(angleCenter, ord, mats, idVec, Nx, mu_n, i);
  // + compute_fission(mat, ord, angle_flux, i);;
}

template<typename T, typename F, typename O>
auto computeSource(F&& func, T&& source, T&& xCenters, O&& ord, int Nx){
  for( unsigned int n = 0; n < ord.size(); ++n ){
    for( unsigned int i = 0; i < Nx; ++i ){
      source[n*Nx + i] = func(xCenters[i], ord[n].value)/2;
    }
  }
  return source;
}


template<typename T, typename O, typename M>
void computeRight(T&& right, T&& angleCenter, T&& source, O&& ord, M&& mats, T&& idVec, int Nx){
  for( int n = 0; n < static_cast<int>(ord.size()); ++n ){
    for( int i = 0; i < Nx; ++i ){
      right[n*Nx + i] = computeCellSource(angleCenter, ord, mats, idVec, Nx, ord[n].value, i) + source[n*Nx + i];
    }
  }
}
