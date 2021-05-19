#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "ants.hpp"

// Test de la classe Fourmi

EnsCoord ensembledetest() {
	vector<Coord> v = {Coord(0,0), Coord(5,1), Coord(2,3), Coord(7,0)};
	EnsCoord E = EnsCoord(v);
	return E;
}

TEST_CASE("test des methodes et predicat Sucre") {
	Coord c1 = Coord(0,0);
	Coord c2 = Coord(2,2);
	Fourmi f1 = Fourmi(c1, 1,1);
	Fourmi f2 = Fourmi(c2, 2,2);
	CHECK_FALSE(f1.porteSucre());
	f2.poseSucre();
	CHECK_FALSE(f2.porteSucre());
	f1.prendSucre();
	CHECK(f1.porteSucre());
}

TEST_CASE("test du modificateur deplace") {
	Fourmi f1 = Fourmi(Coord(1,1), 4,1);
	CHECK(f1.get_Coord() == Coord(1,1));
	f1.deplace(Coord(1,2));
	CHECK(f1.get_Coord() == Coord(1,2));
	f1.deplace(Coord(4,1));
	CHECK(f1.get_Coord() == Coord(4,1));
}

TEST_CASE("test de creeTabFourmis") {
	EnsCoord e = ensembledetest();
	vector<Fourmi> tableau = creeTabFourmis(e,1);
	CHECK(tableau[0].get_Coord() == Coord(0,0));
	for ( size_t i=0 ; i < tableau.size() ; i++)
	{
		CHECK(tableau[i].get_Num() == i);
	}
	CHECK_FALSE(tableau[tableau.size()-1].porteSucre());
}
