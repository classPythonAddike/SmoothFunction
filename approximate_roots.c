#include <math.h>

#include "utils.h"

typedef float (*polynomial)(float);

float approx_bisection(float x_lower, float x_upper, float tolerance, polynomial h) {
    float x_guess = (x_lower + x_upper) / 2; // Compute the midpoint of the range, for the next guess.
    float err = fabsf((x_lower - x_upper) / (x_lower + x_upper)); // Calculate the error associated with the guess.
    
    if (err < tolerance) {
        return x_guess;
    }

    float h_x_guess = h(x_guess);
    
    if (h_x_guess == 0) {
        return x_guess; // Guess is correct.
    } else if (product_is_positive(read_data(x_upper), h_x_guess)) {
        return approx_bisection(x_lower, x_guess, tolerance, h); // Take the lower range.
    } else {
        return approx_bisection(x_guess, x_upper, tolerance, h); // Take the upper range.
    }
}


float approx_false_position(float x_lower, float x_upper, float h_prev_x_guess, float tolerance, polynomial h) {
    float h_x_lower = h(x_lower), h_x_upper = h(x_upper);
    float x_guess = x_upper - (h_x_upper * (x_upper - x_lower)) / (h_x_upper - h_x_lower); // Calculate the next guess.
    float h_x_guess = h(x_guess); // Find h(guess)
    float err = fabsf((h_x_guess - h_prev_x_guess) / h_x_guess); // Calculate the error associated with the guess.

    if (err < tolerance) {
        return x_guess;
    }
    
    if (h_x_guess == 0) {
        return x_guess; // Guess is correct.
    } else if (product_is_positive(h_x_upper, h_x_guess)) {
        return approx_false_position(x_lower, x_guess, h_x_lower, tolerance, h); // Take the lower range.
    } else {
        return approx_false_position(x_guess, x_upper, h_x_guess, tolerance, h); // Take the upper range.
    }
}
