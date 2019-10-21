struct Ordinate {
	double value;
	double weight;
};

double PI = std::atan(1.0) * 4.0;

double get_error(std::vector<double> &first_arr, std::vector<double> &second_arr) {
	// Return the L-2 norm of the difference between two vectors
	double error, difference, sum;

	sum = 0.0;

	for (unsigned int i = 0; i < first_arr.size(); i++) {
		difference = first_arr[i] - second_arr[i];
		sum += difference * difference;
	}

	error = std::sqrt(sum);

	return error;
}

std::vector<double> linspace(double x_start, double x_fin, int x_len) {
	// Cold-copy of the linspace command for vector datatype
	double delta_x;
	std::vector<double> arr_x;

	delta_x = (x_fin - x_start) / ((double)x_len - 1.0);
	for (int i = 0; i < x_len; i++) {
		arr_x.push_back(x_start + (double)i * delta_x);
	}

	return arr_x;
}

template<typename O, typename L, typename U>
auto get_ordinates(O order, L intv_a, U intv_b) {
  int order_place, order_one, order_two;
  double error, y_const = 2.0;
  std::vector<double> x_space(order), y_space(order), y_hold(order), prime(order);
  std::vector<std::vector<double>> legendre(order, std::vector<double>(order + 1));
  std::vector<Ordinate> ordinates(order);

  if (order < 1) {
    std::cout << "Truncation order must be an integer greater than 0\n";
    exit(EXIT_FAILURE);
  }
  
  // Used for indexing purposes
  order_place = order - 1;
  order_one = order_place + 1;
  order_two = order_place + 2;

  // Assign the arrays
  x_space = linspace(-1.0, 1.0, order_one);
  for (int i = 0; i < order_one; i++) {
    y_space[i] = std::cos((2.0 * (double)i + 1.0)
			  / (2.0 * order_place + 2.0) * PI) + (0.27 / order_one)
      * std::sin((PI * x_space[i] * order_place) / order_two);
    y_hold[i] = y_const;
  }

  error = get_error(y_space, y_hold);
  // Compute the zeros of the N+1 Legendre Polynomial using the recursion
  // relation and the Newton-Raphson method
  while (error > std::numeric_limits<double>::epsilon()) {
    for (int i = 0; i < order; i++) {
      // First Legendre polynomial
      legendre[i][0] = 1.0;
      
      // Second Legendre polynomial
      legendre[i][1] = y_space[i];

      // Remaining Legendre polynomials
      if (order > 1) {
	for (int j = 2; j < order_two; j++) {
	  legendre[i][j] = ((2.0 * (double)j - 1.0) * y_space[i] * legendre[i][j - 1] -
			    ((double)j - 1.0) * legendre[i][j - 2]) / (double)j;
	}
      }

      // Derivative of the Legendre polynomial
      prime[i] = order_two * (legendre[i][order_place] - y_space[i] * legendre[i][order_one])
	/ (1.0 - std::pow(y_space[i], 2.0));

      // Error allocation
      y_hold[i] = y_space[i];
      y_space[i] = y_hold[i] - legendre[i][order_one] / prime[i];
      error = get_error(y_space, y_hold);
    }
  }

  // Linear map from [-1, 1] to [intv_a, intv_b]
  for (int i = 0; i < order; i++) {
    // Compute the ordinate values
    ordinates[i].value = (double)intv_a * (1.0 - y_space[i]) / 2.0 + (double)intv_b
      * (1.0 + y_space[i]) / 2.0;

    // Compute the weights
    ordinates[i].weight = (double)(intv_b - intv_a)
      / ((1.0 - std::pow(y_space[i], 2.0)) * std::pow(prime[i], 2.0))
      * std::pow((double)order_two / (double)order_one, 2.0);
  }

  std::reverse(ordinates.begin(), ordinates.end());
  return ordinates;
}
