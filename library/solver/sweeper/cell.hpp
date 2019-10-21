namespace cell
{

  auto solve_right = [](auto&& mat, auto&& ord, auto&& delX, auto&& phi_m, auto&& q){
		       auto factor = mat.Sig_t*delX/(2*ord);
		       return (phi_m + delX/(2*ord)*q)/(1 + factor);
		     };

  auto solve_left = [](auto&& mat, auto&& ord, auto&& delX, auto&& phi_p, auto&& q){
		      auto factor = mat.Sig_t*delX/(2*std::abs(ord));
		      return (phi_p + delX/(2*std::abs(ord))*q)/(1 + factor);
		    };

  auto get_phi_m = [](auto&& phi_c, auto&& phi_p){
		     return 2*phi_c - phi_p;
		   };

  auto get_phi_p = [](auto&& phi_c, auto&& phi_m){
		     return 2*phi_c - phi_m;
		   };
}
