/*
 * Description: Estimate the root of f(x) = -25 + 82x - 90 x^2 + 44 x^3 - 8 x^4 + 0.7 x^5 through bisection method and false position method.
 * Output: The estimated value for the root of f(x).
 * Indentation: 4 spaces
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "approximate_roots.h"

int main() {
    // Initialise boundary values and tolerance.
    float x_lower = 0.5, x_upper = 1.0, tolerance = 0.0001;
    
    discretize_polynomial(x_lower, x_upper, f); // Read f(x) into discrete values.
    write_data("normal.dat");
    
    printf("Bisection method: %f\n", approx_bisection(x_lower, x_upper, tolerance, read_data));
    printf("False Position method: %f\n", approx_false_position(x_lower, x_upper, read_data(x_lower), tolerance, read_data));

    discretize_polynomial(x_lower, x_upper, noisy_f); // Read a noisy f(x) into discrete values.
    write_data("noisy.dat");

    printf("Bisection method with noise: %f\n", approx_bisection(x_lower, x_upper, tolerance, read_data));
    printf("False Position method with noise: %f\n", approx_false_position(x_lower, x_upper, read_data(x_lower), tolerance, read_data));

    smooth_data(); // Smoothen the noisy data present.
    write_data("smooth.dat");

    printf("Bisection method after smoothing: %f\n", approx_bisection(x_lower, x_upper, tolerance, read_data));
    printf("False Position method after smoothing: %f\n", approx_false_position(x_lower, x_upper, read_data(x_lower), tolerance, read_data));
}
