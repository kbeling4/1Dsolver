auto get_abs = [](auto&& scalar, auto&& mat, auto&& grid_b){
		 double abs = 0.0;
		 for( unsigned int i = 0; i < scalar.size(); ++i ){
		   abs += mat.Sig_a*scalar[i]*(grid_b[i+1] - grid_b[i]);
		 }
		 return abs;
	       };

auto left_leak = [](auto&& angle_b, auto&& ord){
		   double plus = 0.0;
		   double minus = 0.0;
		   for( unsigned int n = 0; n < ord.size(); ++n){
		     if( n < ord.size()/2 ){
		       minus += ord[n].weight*std::abs(ord[n].value)*angle_b[n][0];
		     } else {
		       plus += ord[n].weight*ord[n].value*angle_b[n][0];
		     }
		   }
		   return plus - minus;
		 };

auto right_leak = [](auto&& angle_b, auto&& ord){
		    unsigned int Nx = angle_b[0].size();
		    double plus = 0.0;
		    double minus = 0.0;
		    for( unsigned int n = 0; n < ord.size(); ++n){
		      if( n < ord.size()/2 ){
			minus += ord[n].weight*std::abs(ord[n].value)*angle_b[n][Nx-1];
		      } else {
			plus += ord[n].weight*ord[n].value*angle_b[n][Nx-1];
		      }
		    }
		    return plus - minus;
		  };

template<typename S, typename A, typename O, typename G, typename M>
double get_balance(S&& scalar, A&& flux_a, O&& ord, G&& grid, M&& mat){
  auto current_left  = left_leak(flux_a, ord);
  auto current_right = right_leak(flux_a, ord);
  auto absorbtion    = get_abs(scalar, mat, grid);
  return current_left - current_right - absorbtion;
}
