template<typename T, typename M>
void checkForErrors(std::vector<int> cells, std::vector<double> bounds, int Sn, M&& mats, T&& params){
  try{
    if(Sn % 2 != 0) {
      throw 10;
    } else if (cells.size() != bounds.size() - 1 ){
      throw 20;
    } else if (cells.size() != mats.size() ){
      throw 30;
    } else if (params[0].compare("k-value")   != 0 && params[0].compare("source") != 0){
      throw 40;
    } else if (params[1].compare("isotropic") != 0 && params[1].compare("beam")   != 0 &&
	       params[1].compare("vacuum")    != 0 && params[1].compare("albedo") != 0) {
      throw 50;
    } else if (params[2].compare("isotropic") != 0 && params[2].compare("beam")   != 0 &&
	       params[2].compare("vacuum")    != 0 && params[2].compare("albedo") != 0) {
      throw 60;
    }
  }
  catch (int& e){
    if( e == 10 ){
      std::cout << "Error " << e << ": Odd number of ordinates used" << std::endl;
    } else if (e == 20 ){
      std::cout << "Error " << e << ": Number of cell regions not equal to number of regions" << std::endl;
    } else if (e == 30 ){
      std::cout << "Error: Number of materials not equal to number of regions" << std::endl;
    } else if (e == 40 ){
      std::cout << "Error " << e << ": Invalid problem type" << std::endl;
      std::cout << "valid types are: \n";
      std::cout << "- k-value\n";
      std::cout << "- source\n";
    } else if (e == 50 ){
      std::cout << "Error " << e << ": Invalid left boundary condition type" << std::endl;
      std::cout << "valid types are: \n";
      std::cout << "- isotropic\n";
      std::cout << "- beam\n";
      std::cout << "- vacuum\n";
      std::cout << "- albedo\n";
    } else if (e == 60 ){
      std::cout << "Error " << e << ": Invalid right boundary condition type" << std::endl;
      std::cout << "valid types are: \n";
      std::cout << "- isotropic\n";
      std::cout << "- beam\n";
      std::cout << "- vacuum\n";
      std::cout << "- albedo\n";
    }
    exit (EXIT_FAILURE);
  }
}
