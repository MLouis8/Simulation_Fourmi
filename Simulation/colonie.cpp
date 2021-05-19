#include "colonie.hpp"


bool Colonie::estDansColonie(Fourmi f) {
	for (Fourmi fourmi : get_Colonie())
	{
		if (fourmi.get_Coord() == f.get_Coord()) return true;
	}
	return false;
}

void Colonie::utiliseSucre() {
	if (get_nbSucres() > 2) 
	{
		Coord c = coordNid().getTabCoord()[0];
		c = Coord(c.getX()+2,c.getY()+2);
		Fourmi f = Fourmi(c, get_Colonie().size(), get_Colonie()[0].get_Colonie());
		colonie.push_back(f);
		enleveSucre();
	}
}

ostream &operator<<(ostream &out, Colonie col) {
	int nbMortes = 0;
	for (Fourmi f : col.get_Colonie())
	{
		if (not f.enVie()) nbMortes++;
	}
	out << "Nombre de fourmies mortes : " << nbMortes << endl;
	out << "Nombre de fourmies vivantes : " << 12-nbMortes << endl;
	out << "Nombre de sucres restants :" << col.get_nbSucres() << endl;
	return out;
}
