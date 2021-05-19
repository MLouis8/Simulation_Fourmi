#include "coord.hpp"

//////////////////////////////////////////////////////////////////////////////////////
////////////////////////  CLASS Coord  //////////////////////////////////////////////

Coord::Coord(int lig, int col) : coords{lig,col} {
    if ( ((lig < 0) or (lig >= TAILLEGRILLE)) or ((col < 0) or (col >= TAILLEGRILLE)) )
	    throw invalid_argument("Coordonées invalides");
}

ostream &operator<<(ostream &out, const Coord &coord) {
    out << " Coordonnées : (" << coord.getX() << "," << coord.getY() << ").";
    return out;
}

bool Coord::operator==(const Coord &coord) const{
    return (getX() == coord.getX() and getY() == coord.getY());
}

bool Coord::operator!=(const Coord &coord) const{
    return not(*this == coord);
}


//////////////////////////////////////////////////////////////////////////////////////
////////////////////////  CLASS EnsCoord  ///////////////////////////////////////////

ostream &operator<<(ostream &out, EnsCoord c){
	for (size_t i = 0; i < c.getTabCoord().size(); i++)
	{
		out<< "Coordonnées " << i << " : " << c.getTabCoord()[i] << endl;
    	}
    	return out;
}

int EnsCoord::position(Coord c) const{
    for (size_t i = 0; i < tabCoord.size(); i++)
    {
        if (tabCoord[i] == c)
        {
            return i;
        }
    }
    return -1;
}

bool EnsCoord::contient(Coord c) const{
    if( position(c) != -1){
        return true;
    }
    else{
        return false;
    }
}

void EnsCoord::ajoute(Coord c){
    if( not(contient(c)) ){
        tabCoord.push_back(c);
    }
}

void EnsCoord::supprime(Coord c){
    if( not(contient(c)) ){
        throw invalid_argument("l'ensemble ne contient pas la coordonnée");
    }
    int pos = position(c);
    tabCoord.erase(tabCoord.begin() + pos);
}

bool EnsCoord::estVide() const{
    if(tabCoord.size() == 0){
        return true;
    }
    else{
        return false;
    }
}


Coord EnsCoord::choixHasard() const{
	int r = rand()%taille();
	return ieme(r);
}


EnsCoord voisines(Coord c) {
	EnsCoord E = EnsCoord();

	int imin = max(c.getX()-1, 0), imax = min(c.getX()+1, TAILLEGRILLE-1);
	int jmin = max(c.getY()-1, 0), jmax = min(c.getY()+1, TAILLEGRILLE-1);

	for (int i = imin ; i <= imax ; i++) {
		for (int j = jmin ; j <= jmax ; j++) {
			Coord cbis = Coord(i,j);
			if (cbis != c) E.ajoute(cbis);
		}
	}
	return E;
}
