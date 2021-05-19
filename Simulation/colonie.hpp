/*
 * Fichier de la classe colonie, qui contient les fourmi et le nid et toutes les donnes d'une colonie
*/

#ifndef COLONIE_HPP
#define COLONIE_HPP

#include <vector>
#include "coord.hpp"
#include "ants.hpp"
#include <stdexcept>

using namespace std;

class Colonie {
	
	// Attributs
	EnsCoord Nid;
	vector<Fourmi> colonie;
	size_t nbSucre;

	public:
		// Constructeur
		Colonie(EnsCoord nid, vector<Fourmi> c): Nid{nid}, colonie{c} {}

		// Getters
		EnsCoord coordNid() const { return Nid; }
		vector<Fourmi>& get_Colonie() { return colonie; }
		size_t get_nbSucres() { return nbSucre; }
		Fourmi& donneFourmi(int id_fourmi) { return get_Colonie()[id_fourmi]; }

		// Setters
		void ajouteSucre() { nbSucre++; }
		void enleveSucre() { nbSucre-=3; }

		// Predicats
		bool reservesVides() { return nbSucre != 0; }
		
		// Methodes (autres)
		bool estDansColonie(Fourmi f);
		void utiliseSucre();
};

// Operateurs d'affichages pour le bilan final
ostream &operator<<(ostream &out, Colonie col);

#endif // COLONIE_HPP
