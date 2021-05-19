#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "coord.hpp"
#include "place.hpp"

using namespace std;

TEST_CASE(" test constructeur "){
    Coord c1 = Coord(3, 4);
    Place p1 = Place(c1,2);
    CHECK( p1.get_Coord() == c1);
    CHECK( p1.pheroSucre() == 0);
    CHECK( p1.pheroNid(0) == 0);
    CHECK(p1.numeroFourmi() == -1);
    CHECK_FALSE(p1.contientSucre());
    CHECK_FALSE(p1.contientNid());
    CHECK_FALSE(p1.contientFourmi());
}

TEST_CASE(" fonction deplaceFourmi"){
    Coord c1 = Coord(3, 4);
    Coord c2 = Coord(5, 2);
    Place p1 = Place(c1,2);
    Place p2 = Place(c2,2);
    Fourmi f = Fourmi(c1,0,1);
    deplaceFourmi(f,p1,p2);
    CHECK(f.get_Coord() == c2);
    CHECK_FALSE(p1.contientFourmi());
    CHECK(p2.numeroFourmi() == f.get_Num());
}
