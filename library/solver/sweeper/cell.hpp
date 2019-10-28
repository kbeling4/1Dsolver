namespace cell
{
  auto solve_right = [](auto&& mat, auto&& ord, auto&& delX, auto&& phi_m,
			auto&& q, auto&& alpha){
		       auto factor = (1-alpha)*mat.Sig_t*delX/(ord);
		       return (phi_m + (1-alpha)*delX*q/(ord))/(1 + factor);
		     };

  auto solve_left = [](auto&& mat, auto&& ord, auto&& delX, auto&& phi_p,
		       auto&& q, auto&& alpha){
		      auto factor = (1-alpha)*mat.Sig_t*delX/(std::abs(ord));
		      return (phi_p + (1-alpha)*delX*q/std::abs(ord))/(1 + factor);
		    };

  auto get_phi_m = [](auto&& phi_c, auto&& phi_p, auto&& alpha){
		     return (1/(1 - alpha))*(phi_c - alpha*phi_p);
		   };

  auto get_phi_p = [](auto&& phi_c, auto&& phi_m, auto&& alpha){
		     return (1/(1 - alpha))*(phi_c - alpha*phi_m);
		   };
}
