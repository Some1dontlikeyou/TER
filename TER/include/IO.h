#ifndef IO_H
#define IO_H

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include "Algo.h"

using namespace std;

//// Variables golables ////
#define nbResults 10
#define lapseHeure 15
#define debOrange 40
#define debRouge 50

void initFichier();
void ecrireInformation(string s);
void ecrireSolution(int* horaires, int* salles, int horaireMax, int nbBus, int congestionTotale);
void ecrirePlanification(int* horaires, int* salle, int tailleTab);
void ecrireCongestionBus(int* bus, int heureMax);
void ecrireCongestionTotale(int congestionTotale, int nbbus);
void ecrireInformationCongestion(string s);

float lectureProbabilite();
int lectureNombreCours();
int lectureNombreSalles();
int lectureNombreBus();
int lectureNombreIterations();

#endif //IO_H
