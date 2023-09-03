#ifndef APPROXIMATE_ROOTS_H
#define APPROXIMATE_ROOTS_H

typedef float (*polynomial)(float);

float approx_bisection(float, float, float, polynomial);
float approx_false_position(float, float, float, float, polynomial);

#endif
