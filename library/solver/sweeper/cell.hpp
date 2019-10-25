namespace cell
{
  auto solve_right = [](auto&& mat, auto&& ord, auto&& delX, auto&& phi_m,
			auto&& q, auto&& alpha){
		       auto factor = alpha*mat.Sig_t*delX/(ord);
		       return (phi_m + alpha*delX/(ord)*q)/(1 + factor);
		     };

  auto solve_left = [](auto&& mat, auto&& ord, auto&& delX, auto&& phi_p,
		       auto&& q, auto&& alpha){
		      auto factor = alpha*mat.Sig_t*delX/(std::abs(ord));
		      auto res = (phi_p + alpha*delX/(std::abs(ord))*q)/(1 + factor);
		      return res;
		    };

  auto get_phi_m = [](auto&& phi_c, auto&& phi_p, auto&& alpha){
		     return (1/alpha)*(phi_c - (1 - alpha)*phi_p);
		   };

  auto get_phi_p = [](auto&& phi_c, auto&& phi_m, auto&& alpha){
		     return (1/alpha)*(phi_c - (1 - alpha)*phi_m);
		   };
}
