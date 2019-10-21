namespace legendre
{
  // n = 0
  auto P0 = [](auto&& x){ return 1.0; };

  // n = 1
  auto P1 = [](auto&& x){ return x; };

  // n = 2
  auto P2 = [](auto&& x){ return (3.0*x*x - 1.0)*0.5; };

/*
 *	Pn(x)
 */
  template<typename T>
  auto Pn(unsigned int n, const T& x)
  {
    if (n == 0)
    {
      return P0(x) ;
    }
    else if (n == 1)
    {
      return P1(x) ;
    }
    else if (n == 2)
    {
      return P2(x) ;
    }

    T pn1(P2(x)) ;
    T pn2(P1(x)) ;
    T pn(pn1) ;

    for (unsigned int l = 3 ; l <= n ; l++)
    { 
      pn = ((( (2.0) * static_cast<T>(l)) - (1.0))
            * x * pn1 - ((static_cast<T>(l) - (1.0)) * pn2))
              / static_cast<T>(l) ;
      pn2 = pn1;
      pn1 = pn;
    }

    return pn ;
  }
}
