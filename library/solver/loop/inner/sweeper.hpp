#include "sweeper/cell.hpp"

template<typename T, typename O, typename M>
void LSweep(T&& angleCenter, T&& angleBound, T&& right, O&& ord, M&& mats, T&& xBounds, T&& idVec, int n, int Nx,
	    double alpha){
  for( int i = 0; i < Nx; ++i ){
    unsigned int j = Nx - i - 1;
    double deltaX = xBounds[j+1] - xBounds[j];
    angleCenter[n*Nx + j] = cell::solveLeft(angleBound[n*Nx + j + n + 1], right[n*Nx + j], ord[n].value,
    					    mats[idVec[j]], deltaX, alpha);
    angleBound[n*Nx + j + n] = cell::getPhiM(angleCenter[n*Nx + j], angleBound[n*Nx + j + n + 1],
    						 alpha);
  }
}

template<typename T, typename O, typename M>
void RSweep(T&& angleCenter, T&& angleBound, T&& right, O&& ord, M&& mats, T&& xBounds, T&& idVec, int n, int Nx,
	    double alpha){
  for( int i = 0; i < Nx; ++i ){
    double deltaX = xBounds[i+1] - xBounds[i];
    angleCenter[n*Nx + i] = cell::solveRight(angleBound[n*Nx + i + n], right[n*Nx + i], ord[n].value,
     					     mats[idVec[i]], deltaX, alpha);
    angleBound[n*Nx + i + n + 1] = cell::getPhiP(angleCenter[n*Nx +i], angleBound[n*Nx + i + n], alpha);
  }
}

template<typename T, typename O, typename M>
void sweep(T&& angleCenter, T&& angleBound, T&& right, O&& ord, M&& mats, T&& xBounds, T&& idVec, int Nx,
	   double alpha){
  for( int n = 0; n < static_cast<int>(ord.size()); ++n ){
    if(n < static_cast<int>(ord.size()/2) ){
      LSweep(angleCenter, angleBound, right, ord, mats, xBounds, idVec, n, Nx, alpha);
    } else {
      RSweep(angleCenter, angleBound, right, ord, mats, xBounds, idVec, n, Nx, alpha);
    }
  }
}
