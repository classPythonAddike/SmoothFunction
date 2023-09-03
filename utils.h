#ifndef UTILS_H
#define UTILS_H

typedef float (*polynomial)(float);

int product_is_positive(float, float);

float f(float);
float noisy_f(float);

void discretize_polynomial(float, float, polynomial);
float read_data(float);
void write_data(char*);

void smoothen_data();

#endif
