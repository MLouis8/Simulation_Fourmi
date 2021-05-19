/**
	Fichier d'entete pour la classe Grille qui definit la grille de jeu.
**/

#ifndef GRILLE_HPP
#define GRILLE_HPP

#include <stdexcept>
#include <vector>
#include "coord.hpp"
#include "place.hpp"
#include "ants.hpp"
#include "colonie.hpp"

using namespace std;

class Grille{

    // Attributs
    vector<vector<Place>> grille;

    public:
        // Constructeurs
        Grille(int nb_col);
        
        // Acces
        Place chargePlace(Coord c) const ;
        Place chargePlaceAleaNonVide(EnsCoord e) const;
        int get_Colonie(Coord c) const ;

        // Modification
        void rangePlace(Place p);

        // Methode
        void placeNid( EnsCoord e, int col) ;
        void placeSucre( EnsCoord e);
        void placeFourmi( vector<Fourmi> TabF);
        void placeObs(EnsCoord Obs);
        void lineariserPheoNid(int col);
        void diminuePheroSucre();
        void initialiseGrille( vector<Colonie> TabCol, EnsCoord sucre, EnsCoord Obs);
        void coherence(vector<Fourmi> TabF) const;
        void ajouteSucre();
};

#endif  // GRILLE_HPP
