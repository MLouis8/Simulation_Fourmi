/**
	Fichier d'entete pour la classe Fourmi qui definit les fourmis du jeu.
**/

#ifndef ANTS_HPP
#define ANTS_HPP

#include <vector>
#include "coord.hpp"

using namespace std;

class Fourmi{

    // Attributs
    bool sucre;
    Coord coord;
    int indTab;
    int colonie;
    bool vie;

    public:

        // Constructeurs
        Fourmi(Coord c, int ind, int col) : sucre{false}, coord{c}, indTab{ind}, colonie{col}, vie{true} {} 

        // Acces
        Coord get_Coord() const { return coord; }
        int get_Num() const { return indTab; }
        int get_Colonie() const { return colonie; }

        // Predicat
        bool porteSucre() const { return sucre; }
        bool enVie() const { return vie; }
        
        // Modification 
        void meurt() { vie = false; }
        void ressucite() { vie = true; }
        void prendSucre() { sucre = true; }
        void poseSucre() { sucre = false; }
        void deplace(Coord c) { coord = c; }
        
};

/*
 * Fonction qui prend en parametre un ensemble de coordonnees
 * cree une fourmi par coordonnes et renvoie le tableau de toutes les fourmis
*/
vector<Fourmi> creeTabFourmis( EnsCoord e, int col);


#endif // ANTS_HPP
