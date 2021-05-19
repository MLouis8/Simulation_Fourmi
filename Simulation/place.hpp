/**
	Fichier d'entete pour la classe Place qui defini les cellule de notre carte.
**/

#ifndef PLACE_HPP
#define PLACE_HPP
#pragma GCC diagnostic ignored "-Wreorder"
#pragma GCC diagnostic ignored "-Wsign-compare"

#include <vector>
#include "coord.hpp"
#include "ants.hpp"

using namespace std;

class Place {

	// Attributs
	Coord coordonnees;
	size_t sucre;
	int nid;
	int fourmi; // est egale a l'indice de la fourmi contenue ou -1 si sans fourmie
	int coloF; // est egale a l'indice de la colonie de la fourmi ou -1 si pas de fourmie
	bool FenVie;
	float pheroS;
	vector<float> pheroN;
	bool obstacle;	


	public:
		/*Constructeur : cree une Place vide (sans sucre, sans nid et sans fourmi)*/
		Place(Coord c, int nb_col);

		// Getters
		Coord get_Coord() const { return coordonnees; }
		float pheroSucre() const { return pheroS; }
		float pheroNid(int col) const { return pheroN[col]; }
		int get_Nid() const { return nid;}
		int numeroFourmi() const { return fourmi; }
		int qteSucre() const { return sucre; }
		int get_colonie_f() const { return coloF; }
		bool fourmi_en_vie() const { return FenVie; }

		// Predicats
		bool contientSucre() const { return sucre > 0; }
		bool contientNid() const { return nid != -1; }
		bool contientFourmi() const { return fourmi != -1; }
		bool contientObstacle() const { return obstacle; }
		bool estSurUnePiste() const { return pheroS != 0; }
		bool estVide() const { return (not contientFourmi()) and (not contientNid()) and (not contientSucre()) and (not contientObstacle()); }

		// Setters
		void poseSucre() { sucre += 1; }
		void enleveSucre() { sucre -= 1; }
		void rempliSucre() { sucre = 10; } // Quantite max de sucre
		void poseObstacle() { obstacle = true; }
		void poseNid(int col) { nid = col; } // Ajouter la colonie
		void poseFourmi(Fourmi f) { fourmi = f.get_Num(); coloF = f.get_Colonie(); FenVie = true; }
		void enleveFourmi() { fourmi = -1; coloF = -1; FenVie = false; };
		void Fmeurt() { FenVie = false; }
		void Fvie() { FenVie = true; }
		void posePheroNid(float qte, int col) { pheroN[col] = qte; }
		void posePheroSucre() { pheroS = 255; }
		void diminuePheroSucre() { pheroS -= 5; }
		
};

/*
	Fonction qui deplace une fourmie d'une place a l'autre
*/
void deplaceFourmi(Fourmi& f, Place& p1, Place& p2);

/*
	Fonction qui renvoie si la premiere place est plus proche d'un nid que l'autre
	Pour cela il suffit de comparer le taux de pheromones de nid.
*/
bool estPlusProcheNid(Place p1, Place p2, int col);

#endif // PLACE_HPP
