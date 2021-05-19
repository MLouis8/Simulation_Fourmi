/**
	Fichier d'entete pour la classe Coord et la classe EnsCoord pour gerer les coordonnees.
**/

#ifndef COORD_HPP
#define COORD_HPP

#include <utility>
#include <cmath>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

const int TAILLEGRILLE = 50; // metre a 10 pour les tests de grille

class Coord {

        // Attribut
        pair<int, int> coords;


    public:
        // Constructeur
		Coord(int lig, int col);

        // Getter
        int getX() const { return coords.first; }
        int getY() const { return coords.second; }

		// Surcharges
		bool operator==(const Coord &coord) const;
        bool operator!=(const Coord &coord) const;

    
};

class EnsCoord {

	    // Attribut
        vector<Coord> tabCoord;

        // Méthode
        int position(Coord c) const;


    public:
        // Contructeurs
		EnsCoord(): tabCoord{{}} {}
        EnsCoord(vector<Coord> tabC) : tabCoord{tabC} {}

        // Getter
        vector<Coord> getTabCoord() const { return tabCoord; }

        // Méthodes
        bool contient(Coord c) const;
        void ajoute(Coord c);
        void supprime(Coord c);
        bool estVide() const;
        int taille() const { return tabCoord.size() ;}
        Coord ieme(int n) const { return tabCoord[n]; }
        Coord choixHasard() const;

};

/*
 * Fonction qui renvoie un ensemble de coordonnees de toutes les cases voisines
 *	De la coordonnees passee en parametre
*/
EnsCoord voisines(Coord c);

// Operateurs d'affichages
ostream &operator<<(ostream &out, const Coord &coord);
ostream &operator<<(ostream &out, const EnsCoord c);

#endif // COORD_HPP

