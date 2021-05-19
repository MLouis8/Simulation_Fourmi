#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "place.hpp"
#include "grille.hpp"
#include "coord.hpp"
#include "ants.hpp"
#include <iostream>

// Test de la classe Grille

TEST_CASE("Taille de la grille") {
    /** 
        Pour lineariser phero ni les calculs de test
        ont ete effectue pour une grille de taille
        10 x 10
    **/
    WARN(TAILLEGRILLE == 10);
}

EnsCoord ensembledetest() {
	vector<Coord> v = {Coord(0,0), Coord(5,1), Coord(2,3), Coord(7,0)};
	EnsCoord E = EnsCoord(v);
	return E;
}

TEST_CASE("test de placeNid") {
    EnsCoord e = ensembledetest();
    Grille G = Grille(2);
    G.placeNid(e,1);

    Place p1 = G.chargePlace(Coord(0,0));
    Place p2 = G.chargePlace(Coord(5,1));
    Place p3 = G.chargePlace(Coord(2,3));
    Place p4 = G.chargePlace(Coord(7,0));
    CHECK(p1.contientNid());
    CHECK(p2.contientNid());
    CHECK(p3.contientNid());
    CHECK(p4.contientNid());
    CHECK(p1.pheroNid(1) == 1);
    CHECK(p2.pheroNid(1) == 1);
    CHECK(p3.pheroNid(1) == 1);
    CHECK(p4.pheroNid(1) == 1);
}

TEST_CASE("test de placeSucre") {
    EnsCoord e = ensembledetest();
    Grille G = Grille(2);
    G.placeSucre(e);

    Place p1 = G.chargePlace(Coord(0,0));
    Place p2 = G.chargePlace(Coord(5,1));
    Place p3 = G.chargePlace(Coord(2,3));
    Place p4 = G.chargePlace(Coord(7,0));
    CHECK(p1.contientSucre());
    CHECK(p2.contientSucre());
    CHECK(p3.contientSucre());
    CHECK(p4.contientSucre());
}

vector<Fourmi> tableaufourmidetest() {
    EnsCoord e = ensembledetest();
    return creeTabFourmis(e,1);
}

TEST_CASE("test de placeFourmi") {
    vector<Fourmi> tabf = tableaufourmidetest();
    Grille G = Grille(2);
    G.placeFourmi(tabf);

    Place p1 = G.chargePlace(Coord(0,0));
    Place p2 = G.chargePlace(Coord(5,1));
    Place p3 = G.chargePlace(Coord(2,3));
    Place p4 = G.chargePlace(Coord(7,0));
    CHECK(p1.contientFourmi());
    CHECK(p2.contientFourmi());
    CHECK(p3.contientFourmi());
    CHECK(p4.contientFourmi());
}

EnsCoord ensembledetestv2() {
	vector<Coord> v = {Coord(5,4), Coord(7,9)};
	EnsCoord E = EnsCoord(v);
	return E;
}

bool CompareFloat(float a, float b) {
	float epsilon = 0.001;
	return a-b <= epsilon;
}

TEST_CASE("test de lineariserPheoNid") {
    Grille G = Grille(2);
    EnsCoord e = ensembledetestv2();
    G.placeNid(e,0);
    G.lineariserPheoNid(2);

    Place p1 = G.chargePlace(Coord(0,0));
    Place p2 = G.chargePlace(Coord(5,3));
    Place p3 = G.chargePlace(Coord(6,4));
    Place p4 = G.chargePlace(Coord(7,8));
    Place p5 = G.chargePlace(Coord(6,9));
    Place p6 = G.chargePlace(Coord(6,7));

    CHECK( CompareFloat(p1.pheroNid(0), 0.5f) );
    CHECK( CompareFloat(p2.pheroNid(0), 0.9f) );
    CHECK( CompareFloat(p3.pheroNid(0), 0.9f) );
    CHECK( CompareFloat(p4.pheroNid(0), 0.9f) );
    CHECK( CompareFloat(p5.pheroNid(0), 0.9f) );
    CHECK( CompareFloat(p6.pheroNid(0), 0.8f) );
}


EnsCoord ensembledetestv3() {
	vector<Coord> v = {Coord(1,0), Coord(7,1), Coord(1,5), Coord(7,4)};
	EnsCoord E = EnsCoord(v);
	return E;
}
/*
TEST_CASE("test de initialiseGrille") {
    vector<Fourmi> tabf = tableaufourmidetest();
    EnsCoord s = ensembledetestv2();
    EnsCoord n = ensembledetestv3();
    vector<EnsCoord> ens = {n};
    Grille G = Grille(2);
    G.initialiseGrille(tabf, s, ens);

    Place p1 = G.chargePlace(Coord(0,0));
    Place p2 = G.chargePlace(Coord(5,1));
    Place p3 = G.chargePlace(Coord(5,4));
    Place p4 = G.chargePlace(Coord(7,9));
    Place p5 = G.chargePlace(Coord(1,5));
    Place p6 = G.chargePlace(Coord(7,4));


    CHECK(p1.contientFourmi());
    CHECK(p2.contientFourmi());
    CHECK_FALSE(p3.contientFourmi());
    CHECK(p3.contientSucre());
    CHECK(p4.contientSucre());
    CHECK_FALSE(p5.contientSucre());
    CHECK(p5.contientNid());
    CHECK(p6.contientNid());
    CHECK_FALSE(p1.contientNid());
}
*/
int main(int argc, const char **argv) {
	doctest::Context context(argc, argv);
	int test_result = context.run();
	if (context.shouldExit()) return test_result;

    /*
    vector<Fourmi> tabf = tableaufourmidetest();
    EnsCoord s = ensembledetestv2();
    EnsCoord n = ensembledetestv3();
    Grille G = Grille(2);
    G.initialiseGrille(tabf, s, {n});
    for (size_t i = 0; i < TAILLEGRILLE; i++)
    {
        for (size_t j = 0; j < TAILLEGRILLE; j++)
        {
            Coord c = Coord(i,j);
            Place p = G.chargePlace(c); 
            cout << p.pheroNid(0) << " ";
        }
        cout << endl;
    }
    */
	

	return 0;
}