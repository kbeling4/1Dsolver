namespace cell
{
  template<typename T, typename O, typename M>
  double solveRight(T&& angleBound, T&& source, O&& ord, M&& mat, double deltaX, double alpha){
    double factor = (1-alpha)*mat.sigT*deltaX/(ord);
    return (angleBound + (1-alpha)*deltaX*source/(ord))/(1 + factor);
  }

  template<typename T, typename O, typename M>
  double solveLeft(T&& angleBound, T&& source, O&& ord, M&& mat, double deltaX, double alpha){
    auto factor = (1-alpha)*mat.sigT*deltaX/(std::abs(ord));
    return (angleBound + (1-alpha)*deltaX*source/std::abs(ord))/(1 + factor);
  }

  template<typename T>
  double getPhiM(T&& angleCenter, T&& angleBound, double alpha){
    return (1/(1 - alpha))*(angleCenter - alpha*angleBound);
  }

  template<typename T>
  double getPhiP(T&& angleCenter, T&& angleBound, double alpha){
    return (1/(1 - alpha))*(angleCenter - alpha*angleBound);
  }
}
