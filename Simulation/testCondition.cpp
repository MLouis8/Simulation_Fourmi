#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "condition.hpp"
#include "doctest.h"

#include <iostream> // pour les tests

TEST_CASE("test de condition_n") {

	Place p1 = Place(Coord(0,0), 1); p1.posePheroNid(0.25, 1);
	Place p2_a = Place(Coord(1,1), 1); p2_a.poseSucre();
	Place p2_b = Place(Coord(1,1), 1); p2_b.poseNid(1);
	Place p2_c = Place(Coord(1,1), 1); p2_c.posePheroNid(0.5, 1);
	Place p2_d = Place(Coord(1,1), 1); p2_d.posePheroSucre();
	Place p2_e = Place(Coord(1,1), 1); p2_e.posePheroSucre();
	Place p2_f = Place(Coord(1,1), 1);
	
	Fourmi f1 = Fourmi(Coord(0,0), 1, 1); f1.prendSucre();
	Fourmi f2 = Fourmi(Coord(0,0), 2, 1);

	CHECK(condition_n(1, f2, p1, p2_a)); // test regle 1	
	CHECK(condition_n(3, f2, p1, p2_e)); // test regle 5
	CHECK_FALSE(f2.porteSucre());
	CHECK(p2_e.estSurUnePiste());
	CHECK(p2_e.estVide());
	
	CHECK(condition_n(4, f2, p1, p2_f)); // test regle 6
	p1.posePheroSucre();
	CHECK(condition_n(2, f2, p1, p2_d)); // test regle 4
	
	bool test = not false and true and true;
	bool test2 = not false and false;
	CHECK(test);
	CHECK_FALSE(test2);

}

TEST_CASE("test de action_n") {

	Fourmi fSucre1 = Fourmi(Coord(2,2), 3, 2); fSucre1.prendSucre();
	Fourmi fSansSucre1 = Fourmi(Coord(2,2), 3, 2);
	Fourmi fSucre2 = Fourmi(Coord(2,2), 3, 2); fSucre2.prendSucre();

	Place p1_a = Place(Coord(2,2), 2);
	
	Place p2_Sucre = Place(Coord(2,3), 2); p2_Sucre.rempliSucre();
	Place p2 = Place(Coord(3,3), 2);
	Place p3 = Place(Coord(4,4), 2);

	ChargerSucre(fSansSucre1, p1_a, p2_Sucre);
	PoserduSucre(fSucre1, p1_a, p2);
	DeplacerPoser(fSucre2, p1_a, p3);
	CHECK(p1_a.estSurUnePiste());
	CHECK_FALSE(fSucre1.porteSucre());
	CHECK(fSucre2.get_Coord() == p3.get_Coord());
	CHECK(fSucre2.porteSucre());
	CHECK(p3.estSurUnePiste());
	
}
