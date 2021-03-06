#include "../include/Planification.h"

//Créer la matrice d'adjacence symétrique
int **matrice_adjacence_GNO (int N, float K)
{
	int **T = (int**)malloc(N*sizeof(int*));
	for (int i = 0; i < N; i++)
	{
		T[i] = (int*) malloc(N*sizeof(int));
	}

	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			T[i][j] = 0;
		}
	}

	float x = 0.0;
	srand(time(NULL));
	for (int j = 0; j < N; j++){
		for(int i = j; i < N; i++){
			x = rand()%100;
			if ((x <= (K*100)) && (i !=j)){
				T[i][j] = 1;
				T[j][i] = 1;
			}
			else{
				T[i][j] = 0;
				T[j][i] = 0;
			}
		}
	}
	return T;
}

//Attribue les salles aux cours en donnant une couleur à chaque cours
int *coloration (int N, int Nb)
{
	int *T = (int*)malloc(N*sizeof(int*));
	for(int i = 0; i < N; i++){
		T[i] = 0;
	}

	int couleur = 0;
	srand(time(NULL));
	for (int i = 0; i < N; i++)
	{
		couleur = rand()%(Nb);
		T[i] = couleur;
	}
	return T;
}

//Oriente la matrice du graphe non orienté en mettant les liens du sommet d'indice
//le plus faible vers le sommet d'indice le plus fort
int **matrice_graphe_oriente (int **T, int N){
	int **TO = (int**)malloc(N*sizeof(int*));
	for (int i = 0; i < N; i++){
		TO[i] = (int*) malloc(N*sizeof(int));
	}

	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			TO[i][j] = 0;
		}
	}

	for (int j = 0; j < N; j++){
		for(int i = j; i < N; i++){
			if(T[i][j] == 1){
				TO[i][j] = 1;
			}
			else {
				TO[i][j] = 0;
			}
		}
	}
	return TO;
}

//0 un TD, 1 un CM
//attribu un type a chaque cours
int *type_cours (int N)
{
	int type = 0;
	int *T = (int*)malloc(N*sizeof(int*));
	for(int i = 0; i < N; i++){
		T[i] = 0;
	}

	srand(time(NULL));
	for (int i = 0; i < N; i++)
	{
		type = rand()%100;
		if (type <= 75)
		{
			T[i] = 0;
		}
		else
		{
			T[i] = 1;
		}
	}
	return T;
}

//attribu un nombre d'élèves a chaque cours
int *nb_eleves (int *TYPE, int N)
{
	int nb = 0;
	int *T = (int*)malloc(N*sizeof(int*));
	for(int i = 0; i < N; i++){
		T[i] = 0;
	}

	srand(time(NULL));
	for (int i = 0; i < N; i++){
		if(TYPE[i] == 0){
			nb = (rand()%16) + 16;
			T[i] = nb;
		}
		else{
			nb = (rand()%84) + 16;
			T[i] = nb;
		}
	}
	return T;
}

int plusGrand(int* T, int i, int j){
	int grand = T[i];
	int indice = i;
	for(int k = i; k < j; k++){
		if(T[k] > grand){
			grand = T[k];
			indice = k;
		}
	}
	return indice;
}

int* tabCours(int* nbEleves, int N){
	int *tabNbEleveDesc = (int*)malloc(N*sizeof(int*));;
	for(int i = 0; i < N; i++){
		tabNbEleveDesc[i] = 0;
	}

	int indice = 0;
	int temp;
	printf("Cours avec le plus d'élèves -> moins d'élèves\n");
	for(int i = 0; i < N; i++){
		indice = plusGrand(nbEleves, i, N);
		tabNbEleveDesc[i] = indice;
		// printf("%d ", T[i]);
		temp = nbEleves[i];
		nbEleves[i] = nbEleves[indice];
		nbEleves[indice] = temp;
	}
	return tabNbEleveDesc;
}

//Test s une planification est valide en terme de coloration uniquement
bool test_coloration(int *Horaires, int *couleur, int N, int *TYPE, int heure_a_teste, int sommet_a_teste)
{
	int duree1 = 0;
	int duree2 = 0;
	for(int i = 0; i < N; i++){
		if((couleur[i] == couleur[sommet_a_teste])&& (sommet_a_teste != i)){
			if(TYPE[i] == 0){duree1 = 12;}else{duree1 = 6;}
			if(TYPE[sommet_a_teste] == 0){duree2 = 12;}else{duree2 = 6;}
			if(((heure_a_teste + duree2 >= Horaires[i]) &&  (heure_a_teste + duree2 <= Horaires[i] + duree1)) 
				|| ((Horaires[i] + duree1 >= heure_a_teste) && (Horaires[i] <= heure_a_teste + duree2))){
				return false;
			}
		}
	}
	return true;
}

//Test si le graphe est bien connexe
bool testConnnexe(int **T, int N, int sommet){
	int degre = 0;
	for(int i = 0; i < N; i ++){
		degre += T[sommet][i];
	}
	for(int i = 0; i < N; i++){
		degre += T [i][sommet];
	}
	if (degre != 0){
		return true;
	}
	return false;
}

//Test si une planification est valide vis a vis des liens entre les sommets
bool test_lien(int *Horaires, int N, int **T, int heure_a_teste, int sommet_a_teste, int *TYPE)
{
	int duree = 0;
	for (int i = 0; i < N; i++){
		if(TYPE[i] == 0){ 
			duree = 12;
		} 
		else {
			duree = 6;
		}
		if((T[sommet_a_teste][i] == 1) && (heure_a_teste >= Horaires[i]) && (heure_a_teste <= Horaires[i] + duree) && (sommet_a_teste != i)){
			return false;
		}
	}
	return true;
}

//Pour le moment TD c'est 3h et CM 1h30, a changer ptet je sais pas 
//Pour représenter les heures par créneau de 15 min :
//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34: indices
//    8       9       10          11          12          13          14          15          16: heure
//C'est la planification initiale
int *planification(int **T, int sommet_depart, int *couleur, int N, int *TYPE){
	int *Horaires = (int*)malloc(N*sizeof(int*));
	for (int i = 0; i < N; i++){
		Horaires[i] = 0;
	}

	for(int i = 1; i < N; i++){
		for(int k = 0; k < N; k++){
			if(T[i][k] == 1){
				if(TYPE[i] == 0){//si le cours est un td
					for(int j = 0; j <= 36; j++){
						if(test_coloration(Horaires, couleur, N, TYPE, Horaires[k] + 13 + j, i) == true){
							if(test_lien(Horaires, N, T, Horaires[k] + 13 + j, i, TYPE) == true){
								Horaires[i] = Horaires[k] + 13 + j;
								break;
							}
						}
					}

				}
				else //si le cours est un cm
				{
					for(int j = 0; j <= 36; j++)
					{
						if(test_coloration(Horaires, couleur, N, TYPE, Horaires[k] + 7 + j,i) == true)
						{
							if(test_lien(Horaires, N, T, Horaires[k] + 7 + j, i, TYPE) == true)
							{
								Horaires[i] = Horaires[k] + 7 + j;
								//printf("Horaire de %d : %d\n",i,Horaires[i]);
								break;
							}
						}
					}
				}
			}
			else {
				if(testConnnexe(T, N, i) == true){
					if(TYPE[k] == 0)//si le cours est un td
					{
						for(int j = 0; j <= 36; j++)
						{
							if(test_coloration(Horaires, couleur, N, TYPE, Horaires[k] + 13  + j, i) == true)
							{
								if(test_lien(Horaires, N, T, Horaires[k] + 13 + j, i, TYPE) == true)
								{
									Horaires[i] = Horaires[k] + 13 + j;
									//printf("Horaire de %d : %d\n",i,Horaires[i]);
									break;
								}
							}
						}
					}
					else //si le cours est un cm
					{
						for(int j = 0; j <= 36; j++)
						{
							if(test_coloration(Horaires, couleur, N, TYPE, Horaires[k] + 7 + j,i) == true)
							{
								if(test_lien(Horaires, N, T, Horaires[k] + 7 + j, i, TYPE) == true)
								{
									Horaires[i] = Horaires[k] + 7 + j;
									//printf("Horaire de %d : %d\n",i,Horaires[i]);
									break;
								}
							}
						}
					}
				}
			}	
		}
	}
	for (int i = 0; i < N; i++)
	{
		Horaires[i] += 2;
	} 
	return Horaires;
}

//Test si une planification est valide, si elle respecte toutes les contraintes
bool test_solution_valide(int *Horaires, int N, int *couleur, int *TYPE, int **TO){	
	//TEST COLORATION
	int dureei, dureej;
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			if((couleur[i] == couleur[j]) && (i != j)) {
				
				if(TYPE[i] == 0) {dureei = 13;} else {dureei = 7;}
				if(TYPE[j] == 0) {dureej = 13;} else {dureej = 7;}
			if(Horaires[i] > Horaires[j]){
				
					if(Horaires[j] +dureej > Horaires[i])
					{
						return false;	
					}		
				}
				else {
					
					if(Horaires[i] + dureei > Horaires[j])
					{
						return false;
					}
				}
			}
		}
	}

	//TEST LIEN
	int duree = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = i; j < N; j++)
		{
			if(TO[i][j] == 1) {
				if(TYPE[j] == 0) duree = 12; else duree = 6;
			if((test_lien(Horaires, N, TO, Horaires[i] + duree, j, TYPE) == false) && (i != j))
			{
				return false;
			}
		}
		}
	}
	return true;
}


