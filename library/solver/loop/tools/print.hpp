auto printX = [](auto&& grid, auto&& Nx){
		std::ofstream myfile ("x_grid.txt");
		if( myfile.is_open() )
		  {
		    for( int i = 0; i < Nx; ++i ){
		      myfile << grid[i] << "\n";
		    }
		  }
		myfile.close();
	      };

auto printScalar = [](auto&& flux, auto&& grid, auto&& Nx, auto&& name){
		     std::ofstream myfile (name);
		     if( myfile.is_open() )
		       {
			 for( int i = 0; i < Nx; ++i ){
			   myfile << grid[i] << " " << flux[i] << "\n";
			 }
			 myfile << "\n";
		       }
		     myfile.close();
		   }; 

auto printK = [](auto&& kVec, auto&& name){
		std::ofstream myfile (name);
		if( myfile.is_open() )
		  {
		    for( int i = 0; i < static_cast<int>(kVec.size()); ++i ){
		      myfile << i << " " << kVec[i] << "\n";
		    }
		    myfile << "\n";
		  }
		myfile.close();
	      };

auto printErr = [](auto&& err, auto&& name){
		  std::ofstream myfile (name);
		  if( myfile.is_open() )
		    {
		      for( int i = 0; i < static_cast<int>(err.size()); ++i ){
			myfile << i << " " << err[i] << "\n";
		      }
		      myfile << "\n";
		    }
		  myfile.close();
		}; 
		

template<typename T>
void printer(std::vector<bool> params, T&& scalar, T&& xGrid, std::vector<double> errIn,
	     std::vector<double> errOut, std::vector<double> kVec, int Nx){
  for (int i = 0; i < static_cast<int>(params.size()); ++i){
    if (i == 0 and params[i]){
      printScalar(scalar, xGrid, Nx, "scalar.txt");
    } else if (i == 1 and params[i]){
      printErr(errIn, "error_In.txt");
    } else if (i == 2 and params[i]){
      printK(kVec, "k_vals.txt");      
    } else if (i == 3 and params[i]){
      printErr(errOut, "error_Out.txt");
    }
  }
}
