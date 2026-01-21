#ifndef KERNELS_H
#define KERNELS_H

#include "types.h"
#include <stdio.h>
#include <math.h>

/*
  Add vector a with vector b
  input :
    - vector
    - vector
  output : vector
*/
static inline vector
add_vectors (vector a, vector b)
{
  return (vector){a.x+b.x, a.y+b.y};
}

/*
  Multiply vector a with b value
  input :
    - f64
    - vector
  output : vector
*/
static inline vector
scale_vector (f64 b, vector a)
{
  return (vector){a.x*b,  a.y*b};
}

/*
  Substitute vector b from the vector a
  input :
    - vector
    - vector
  output : vector
  */
static inline vector
sub_vectors (vector a, vector b)
{
  return (vector){a.x-b.x, a.y-b.y};
}

/*
  Eclidian distance of vector
  input :
    - vector
  output : f64
*/
static inline f64
mod (vector a)
{ 
  return sqrt((a.x*a.x) + (a.y*a.y));
}


void simulate (i32 nbodies, f64 *masses, vector *positions, vector *velocities,
               vector *accelerations);
void init_system (i32 nbodies, f64 *masses, vector *positions,
                  vector *velocities);
void free_memory (i32 nbodies, f64 *masses, vector *positions,
                  vector *velocities, vector *accelerations);



#endif
 