#include "kernels.h"
#include "random.h"
#include "types.h"
#include <SDL2/SDL_surface.h>
#include <time.h>

#include <cblas.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void
unimplemented ()
{
  puts ("unimplemented functions called");
}
 


/*
  Initialize the system by setting random values
  input :
    - i32
    - f64 *
    - vector *
    - vector *
  output : void
*/
void
init_system (i32 nbodies, f64 *masses, vector *positions, vector *velocities)
{
  //
  srand (time (NULL));
  //
  for (i32 i = 0; i < nbodies; i++)
    {
      masses[i] = 5;

      positions[i].x = randxy (10, DIM_WINDOW);
      positions[i].y = randxy (10, DIM_WINDOW);

      velocities[i].x = randreal ();
      velocities[i].y = randreal ();
    }
}

/*
  This function interverts the velocity of 2 particles if they are in collision
*/
void
resolve_collisions (i32 nbodies, vector *positions, vector *velocities)
{
  int i = 0, j= 0;
  vector temp;
  for(i=0; i< nbodies; i++){
    for(j=0; j< nbodies; j++){
      if( (i != j )  && (positions[i].x == positions[j].x && positions[i].x == positions[j].x) ){
        temp = velocities[i];
        velocities[i] = velocities[j];
        velocities[j] = temp;
      }
    }
  }
}


void
compute_accelerations (i32 nbodies, vector *accelerations, f64 *masses,
                       vector *positions)
{
  for (int i = 0; i < nbodies; i++) {
  accelerations[i].x = 0;
  accelerations[i].y = 0;
    for ( int j = 0; j< nbodies; j++) {
      if (i==j) continue;
      vector diff = sub_vectors(positions[j], positions[i]);
      vector diff2 = sub_vectors(positions[i], positions[j]);
      f64  d = ( mod(diff2)*mod(diff2)*mod(diff2) ) + 1e7;
      f64 f = GRAVITY * masses[i] * (1/d); 
      vector a_ij = scale_vector(f, diff);
      accelerations[i] = add_vectors(accelerations[i], a_ij);
    }         
  }
}



//
void
compute_velocities (i32 nbodies, vector *velocities, vector *accelerations)
{
  int i = 0;
  for(i=0; i< nbodies; i++){
    velocities[i] = add_vectors(velocities[i], accelerations[i]);
  }
}

/*
  This function allows particules which quit the box to reenter from the
  opposite side.
*/
vector
check_position (vector a)
{
  if(a.x >= DIM_WINDOW ){ // droite
    a.x = 0;
  }else if(a.x < 0){ // gauche
    a.x = DIM_WINDOW;
  }
  
  if(a.y >= DIM_WINDOW){ // bas
    a.y = 0;
  }else if(a.y < 0 ){ // haut
    a.y = DIM_WINDOW;
  }
  return a;
}

//
void
compute_positions (i32 nbodies, vector *positions, vector *velocities,
                   vector *accelerations)
{
  vector pos;

  int i = 0;
  for(i=0; i< nbodies; i++){
    pos = add_vectors(positions[i], add_vectors(velocities[i], (scale_vector(0.5, accelerations[i]))));
    positions[i]= pos;

    positions[i] = check_position(positions[i]);
  }
}

/*
  Simulate is the main simulation function which calls all steps
  input :
    - i32
    - f64 *
    - vector *
    - vector *
    - vector *
  output : void
*/
void
simulate (i32 nbodies, f64 *masses, vector *positions, vector *velocities,
          vector *accelerations)
{
  compute_accelerations (nbodies, accelerations, masses, positions);
  compute_positions (nbodies, positions, velocities, accelerations);
  compute_velocities (nbodies, velocities, accelerations);
  resolve_collisions (nbodies, positions, velocities);
}

/*
  Free all allocated memory
*/
void
free_memory (i32 nbodies, f64 *masses, vector *positions, vector *velocities,
             vector *accelerations)
{
  free (positions);
  free (velocities);
  free (accelerations);
  free (masses);
}

