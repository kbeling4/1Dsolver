auto get_abs = [](auto&& scalar, auto&& mat, auto&& grid_b){
		 double abs = 0.0;
		 for( unsigned int i = 0; i < scalar.size(); ++i ){
		   abs += mat.Sig_a*scalar[i]*(grid_b[i+1] - grid_b[i]);
		 }
		 std::cout << "absorption  :  " << abs << std::endl;
		 return abs;
	       };

auto get_fission = [](auto&& scalar, auto&& mat, auto&& grid_b){
		     double fis = 0.0;
		     for( unsigned int i = 0; i < scalar.size(); ++i ){
		       fis += mat.nuSig_f*scalar[i]*(grid_b[i+1] - grid_b[i]);
		     }
		     std::cout << "fission     :  " << fis << std::endl;
		     return fis;
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
		   std::cout << "J^(-) (0) = :  " << std::scientific << minus << std::endl;
		   std::cout << "J^(+) (0) = :  " << std::scientific << plus << std::endl;
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
		    std::cout << "J^(-) (a) = :  " << std::scientific << minus << std::endl;
		    std::cout << "J^(+) (a) = :  " << std::scientific << plus << std::endl;
		    return plus - minus;
		  };

auto get_source = [](auto&& func, auto&& scalar, auto&& grid_b, auto&& grid_c, auto&& ord){
		    unsigned int Nx = scalar.size();
		    unsigned int N  = ord.size();
		    double sum = 0.0;
		    for( unsigned int i = 0; i < Nx; ++i ){ 
		      for( unsigned int n = 0; n < N; ++n ){
			sum += func(ord[n].value,grid_c[i])*ord[n].weight
			  *(grid_b[i+1] - grid_b[i]);
		      }
		    }
		    std::cout << "source      :  " << sum/2 << std::endl;
		    return sum/2;
		  };

template<typename S, typename A, typename O, typename G, typename M, typename F>
double get_balance(S&& scalar, A&& flux_a, O&& ord, G&& grid_b, G&& grid_c, M&& mat, F&& func){
  auto current_left  = left_leak(flux_a, ord);
  auto current_right = right_leak(flux_a, ord);
  auto absorbtion    = get_abs(scalar, mat, grid_b);
  auto fission       = get_fission(scalar, mat, grid_b);
  auto source        = get_source(func, scalar, grid_b, grid_c, ord);
  return current_left - current_right - absorbtion + source + fission;
}
