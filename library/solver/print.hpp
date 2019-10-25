auto printX = [](auto&& grid){
		std::ofstream myfile ("x_grid.txt");
		if( myfile.is_open() )
		  {
		    for( auto point : grid ){
		      myfile << point << "\n";
		    }
		  }
		myfile.close();
	      };

auto printMU = [](auto&& ord){
		 std::ofstream myfile ("mu_grid.txt");
		 if( myfile.is_open() )
		   {
		     for( auto pair : ord ){
		       myfile << pair.value << "\n";
		     }
		   }
		 myfile.close();
	       }; 

auto printScalar = [](auto&& flux, auto&& name){
		     std::ofstream myfile (name);
		     if( myfile.is_open() )
		       {
			 for( auto&& val : flux ){
			   myfile << val << " ";
			 }
			 myfile << "\n";
		       }
		     myfile.close();
		   };  

auto printFlux = [](auto&& flux, auto&& name){
		   std::ofstream myfile (name);
		   if( myfile.is_open() )
		     {
		       for( auto row : flux ){
			 for( auto val : row ){
			   myfile << val << " ";
			 }
			 myfile << "\n";
		       }
		     }
		   myfile.close();
		 };
