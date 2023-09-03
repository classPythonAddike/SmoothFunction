#define NUM_SAMPLES 10000

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct data_point {
    float x;
    float h_x;
};

typedef float (*polynomial)(float);

struct data_point data[NUM_SAMPLES];
float step_size;

// Check if a * b is positive.
int product_is_positive(float a, float b) {
    int a_pos = a > 0, b_pos = b > 0;
    return (a_pos && b_pos) || (!a_pos && !b_pos);
}

float f(float x) {
    return -25 + 82 * x - 90 * powf(x, 2) + 44 * powf(x, 3) - 8 * powf(x, 4) + 0.7 * powf(x, 5);
}

float noisy_f(float x) {
    return f(x) + (float)rand() / RAND_MAX - 0.5;
}

// Read the polynomial h(x) into discrete values.
void discretize_polynomial(float x_lower, float x_upper, polynomial h) {
    srand(time(NULL));
    step_size = (x_upper - x_lower) / (NUM_SAMPLES - 1);

    for (int i = 0; i < NUM_SAMPLES; i++) {
        data[i].x = i * step_size + x_lower;
        data[i].h_x = h(data[i].x);
    }
}

// Read a value x from the discretized data, using binary search.
float read_data(float x) {
    if (x >= data[NUM_SAMPLES - 1].x)
        return data[NUM_SAMPLES - 1].h_x;
    else if (x <= data[0].x)
        return data[0].h_x;
    
    struct data_point *start_ptr = data, middle;
    int width = NUM_SAMPLES;

    while (width > 1) {
        middle = *(start_ptr + (width >> 1));

        if (fabsf(middle.x - x) < step_size) {
            return middle.h_x;
        } else {
            width = width >> 1;
            if (middle.x < x) {
                start_ptr = start_ptr + width;
            }
        }
    }

    return middle.h_x;
}

// Write the discretized data to a file.
void write_data(char* filename) {
    FILE* file = fopen(filename, "w");

    for (int i = 0; i < NUM_SAMPLES; i++) {
        fprintf(file, "%f %f\n", data[i].x, data[i].h_x);
    }

    fclose(file);
}

// Find the weighted average of the previous and next `width` readings.
float weighted_average_h_x(struct data_point *start, int width) {
    float sum = 0;
    for (int i = -width; i <= width; i++) {
        if (i != 0)
            sum += fabsf((float)i) * (start + i + width)->h_x;
        else
            sum += (start + i + width)->h_x;
    }

    return sum / (width * (width + 1) + 1);
}

// Smoothen the data using weighted moving average.
void smooth_data() {
    int width = 100;
    for (int i = width; i < NUM_SAMPLES - width; i++) {
        data[i].h_x = weighted_average_h_x(data + i - width, width);
    }
}
