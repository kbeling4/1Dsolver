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

auto printScalar = [](auto&& flux, auto&& Nx, auto&& name){
		     std::ofstream myfile (name);
		     if( myfile.is_open() )
		       {
			 for( int i = 0; i < Nx; ++i ){
			   myfile << flux[i] << " ";
			 }
			 myfile << "\n";
		       }
		     myfile.close();
		   }; 
