#ifndef Algo_H
#define Algo_H

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int *Tri_nb_eleves(int *Nb_eleves);
int *Algo_glouton(int **T, int sommet_depart, int *couleur, int N, int *TYPE, int *Nb_eleves);
int *Algo_tabou(int *Horaires, int N, int sommet_depart, int *couleur, int *Type, int **T, int Nb_iterations);

int *planification2(int *Horaires, int sommet_depart, int *couleur, int N, int *TYPE, int sommet_fixe, int **T);

#endif // Bus_H