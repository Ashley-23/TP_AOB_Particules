<!-- ENAYATI Yas et SATCHIVI Ashley -->

# IMPLEMENTATION DES FONCTIONS MANQUANTES

## Fonctions basiques
1. add_vectors 
    Signature de la fonction : vector add_vectors (vector a, vector b)
        *   Objectif : 
                cette fonction additionne deux vecturs 
        *   Notes :
                Cette fonction prend 2 vecteurs "a" et "b" et retourne un vecteur. 
                La fonction associe à l'abscisse du vecteur retourné, la somme des abcisses de "a" et "b", et associe la somme des ordonnées de "a" et "b" à l'ordonnée du vecteur retournée.     


2. sub_vectors
    Signature de la fonction : vector sub_vectors (vector a, vector b)
    *   Objectif : cette fonction fait la soustraction de deux vecteurs
    *   Notes :
            Cette fonction prend 2 vecteurs "a" et "b" et retourne un vecteur. 
            La fonction associe :
                - à l'abscisse du vecteur retourné, l'abcisse de "a" moins l'abcisse de "b". 
                - à l'ordonnée du vecteur retourné, l'ordonnée de "a" moins l'ordonnée de "b".   


3. mod 
    Signature de la fonction : f64 mod (vector a)

    *   Objectif : cette fonction calcule la distance euclidienne d'un vecteur

    ![alt text](images_readme/image1.png)

    *   Notes : 
            Cette fonction prend un vecteur "a" et retourne un nombre de type double qui est la racine carrée de la somme des carrés de l'abcisse et de l'ordonnée.


4. Scale_vector 
    Signature de la fonction : vector scale_vector (f64 b, vector a)
    *   Objectif :
            cette fonction multiplie un vecteur avec un nombre réel 
    *   Notes :
            Cette fonction prend 1 vecteurs "a", un réel "b" et retourne un vecteur. 
            La fonction associe :
                - à l'abscisse du vecteur retourné, l'abcisse de "a" fois "b". 
                - à l'ordonnée du vecteur retourné, l'ordonnée de "a" fois "b".      



## Fonctions de simulation 

1. compute_accelerations
    Signature de la fonction : void compute_accelerations (i32 nbodies, vector *accelerations, f64 *masses, vector *positions)

    *   objectif : cette fonction permet de calculer l'accélération d'une particule  

    ![alt text](images_readme/image2.png)

    *   Notes : 
            Cette fonction calcule l'accélération subie par chaque corps sous l'effet de la gravité exercée par les autres corps.
            On a 2 variables i et j qui parcourent le nombre de particules.
            *   Pour chaque corps i :
                    on initialise son accélération à 0
            *   Pour chaque corps j :
                    - on calcule le vecteur distance entre "i" et "j"
                    - on calcule l'intensité de la force gravitationnelle
                    - on transforme cette force en accélération vectorielle
                    - on l'ajoute à l'accélération totale de "i"
    


2. compute_positions
    Signature de la fonction : void compute_positions (i32 nbodies, vector *positions, vector *velocities, vector *accelerations)
    *   objectif : 
        La fonction compute_positions calcule la position de la particule en fonction de sa vitesse et de sa position à t-1.

    ![alt text](images_readme/image4.png)

    * Notes : 
        on parcourt le nombre de particules et pour chaque particules, on calcule sa position par rapport à la vitesse et sa position.
        A la fin, on vérifie la position de la particule avec la fonction check_position 


3. compute_velocities 
    Signature de la fonction : void compute_velocities (i32 nbodies, vector *velocities, vector *accelerations)
    *   objectif : 
            La fonction compute_velocities permet de calculer la vélocité (vitesse) de chaque particule pour chaque pas de temps.

    ![alt text](images_readme/image3.png)

    *   Notes : 
            Pour chaque particules, la nouvelle vitesse de la particule est égale à l'ancienne vitesse de la particule + l'accélération de la particule 


4. resolve_collision 
    Signature de la fonction : void resolve_collisions (i32 nbodies, vector *positions, vector *velocities)
    *   objectif : 
            Elle échange la vitesse de 2 particules qui rentrent en collision
    *   Notes : 
            2 particules sont en collision quand elles ont la position
            On a 2 variables i et j qui parcourent le nombre de particules.
            i prend en compte une particule et j toutes les autres particules 
            Quand deux particules différentes (i!=j) rentrent en collision (position[i] == position[j]), on affecte la vitesse de la particule "i" à la particule "j" et inversement.


5. check position
    Signature de la fonction : vector check_position (vector a)
    *   objectif : cette fonction permet au particules qui sortent de la fenêtre de rentrer par le coté opposé.
    *   Note : 
        * Si la particule sort par la droite (a.x>= DIM_WINDOW), on le fait rentrer par la gauche ( a.x = 0) et inversement 
        * Si la particule sort par le bas ( a.y>= DIM_WINDOW), on le fait rentrer par le haut (a.y = 0) et inversement


# OPTIMISATION DU CODE 

### OPTIMISATION 1 : changement de add_vectors(), scale_vector(), sub_vectors() et mod()
On retourne directement un vecteur au lieu de créé un vecteur temporaire sur lequel faire les opérations 

        * Objectif : éliminé les variables temporaires et permettre au compilateur d'optimiser les retours au moyen des registres du processeur.


Les fonctions deviennent :

vector
add_vectors (vector a, vector b)
{
  return (vector){a.x+b.x, a.y+b.y};
}

vector
scale_vector (f64 b, vector a)
{
  return (vector){a.x*b,  a.y*b};
}

vector
sub_vectors (vector a, vector b)
{
  return (vector){a.x-b.x, a.y-b.y};
}

f64
mod (vector a)
{ 
  return sqrt((a.x*a.x) + (a.y*a.y));
}


### OPTIMISATION 2 : modification de la fonction compute_accelerations()

on a remplacer x/y par (1/y)*x et pow(x,3) 

        * Objectif : Réduire le coût des opérations arithmétiques, car la multiplication est généralement plus rapide que la division.

### OPTIMISATION 3 : inversion de boucle 

inversion des boucles i et j au niveau de resolve_collisions ( on parcoure j avant i )

        * Objectif : Améliorer la localité spatiale des accès mémoire en optimisant l'ordre de parcours des données.

### OPTIMISATION 4 : changement de sqrt en sqrtf 
Dans la fonction mod(), nous avons changé l'appel de sqrt à l'appel de sqrtf

        * Objectif : Utiliser l'opération en simple précision (32 bits) au lieu de double précision (64 bits) pour accélérer le calcul de la racine carrée en exploitant des instructions processeur plus rapides.

### OPtimisation 5 : modification de compute_accelerations

        * Objectif : Améliorer l'accès mémoire en séparant la phase d'initialisation de la phase de calcul.

Au lieu de mettre acceleration[i].x et acceleration[i].y à 0 à chaque fois qu'on rentre dans la boucle, on fait une boucle qui les mets à 0 avant de commencer la modification. 

void
compute_accelerations (i32 nbodies, vector *accelerations, f64 *masses,
                       vector *positions)
{
  for (int i = 0; i < nbodies; i++) {
    accelerations[i].x = 0;
    accelerations[i].y = 0;
  }
  
    for (int i = 0; i < nbodies; i++) {
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


### OPTIMISATION 6 : modification de compute_velocities

on retourne directement la valeur au lieu de créé une variable intermédiaire.

        * Objectif : Éliminer les variables intermédiaires inutiles pour réduire les opérations de copie et l'utilisation de la pile.

### OPTIMISATION 7 : O2
compilation du code avec l'option O2

        * Objectif : activer les optimisations standards du compilateur sans augmenter le temps de compilation

### OPTIMISATION 8 : O3
compilation du code avec l'option O3

        * Objectif : c'est une optimisation standard du compilateur qui : déroule de boucles, élimine de code mort et optimise des expressions. 

### OPTIMISATION 9 : Ofast
compilation du code avec l'option Ofast

        * Objectif : permettre des optimisations mathématiques non conformes aux standards IEEE pour gagner en vitesse au détriment de la précision


### OPTIMISATION 10 : -O3 -march=native
compilation du code avec l'option Ofast

        * Objectif : exploiter les instructions spécifiques du processeur (SIMD, AVX, ...) pour maximiser les performances.

### OPTIMISATION 11 : static inline
On a mis toutes les fonctions de bases ( add_vectors(), scale_vector(), sub_vectors() et mod() ) dans l'en-tête kernel.h précédé des commandes "static inline" 

        * Objectif : Normalement, quand le code appelle une fonction f(x), le processeur doit faire un saut vers une autre partie de la mémoire, copier les arguments, exécuter le code puis revenir. Le fait de mettre inline suggère au compilateur de ne pas faire ce saut mais de copier-coller directement le contenu de la fonction là où elle a été appellée. 



# PERFORMANCES 

## Code de base 

Pour nbodies =1000 et time_stemp = 300
On est à 20 fps

## Après OPTIMISATION 1 

Pour nbodies =1000 et time_stemp = 300
On est à 21 fps à peu près. Le nombre de frames par secondes augmente légèrement 

## Après OPTIMISATION 2

Pour nbodies =1000 et time_stemp = 300
On est à 30 fps

## Après OPTIMISATION 3 

Le nombre de frames par seconde n'a pas augmenté donc nous gardons la place des boucles. 

## Après l'optimisation 4

Le nombre de fps a diminué

## Après l'optimisation 5 

Pas de changement notable 

## Après l'optimisation 6 

Pour nbodies =1000 et time_stemp = 300
On est à 33 fps

## Après l'optimisation 7

Pour nbodies =1000 et time_stemp = 300
On est à 202 fps

## Après l'optimisation 8

Pour nbodies =1000 et time_stemp = 300
On est à 120 fps


## Après l'optimisation 9

Pour nbodies =1000 et time_stemp = 300
On est à 125 fps

## Après l'optimisation 10

Pour nbodies =1000 et time_stemp = 300
On est à 126 fps

## Après l'optimisation 11 

Pour nbodies =1000 et time_stemp = 300
On est à 30 fps













