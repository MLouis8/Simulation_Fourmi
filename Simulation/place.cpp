/**
    Fichier de code pour la classe Place qui defini les cellules de notre carte.
**/

#include "place.hpp"

Place::Place(Coord c, int nb_col): coordonnees{c}, sucre{false}, nid{-1}, fourmi{-1}, pheroS{0.}, coloF{-1}, FenVie{false}, obstacle{false}, pheroN{{}}
{
    for (size_t i = 0; i < nb_col; i++)
    {
        pheroN.push_back(0.);
    }
    
}

void deplaceFourmi(Fourmi& f, Place& p1, Place& p2) {
    if (p2.estVide())
    {
        f.deplace(p2.get_Coord());
        p1.enleveFourmi();
        p2.poseFourmi(f);
        
    }/* else {
		cout << "p2 n'est pas vide apparement (F/N/S)" << p2.contientFourmi() << p2.contientNid() << p2.contientSucre() << p2.get_Coord() << endl;
        f.deplace(p2.get_Coord());
        p1.enleveFourmi();
        p2.poseFourmi(f);
	}*/
}

bool estPlusProcheNid(Place p1, Place p2, int col) {
    return p1.pheroNid(col) >= p2.pheroNid(col);
}
