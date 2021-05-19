#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <array>

#include "coord.hpp"

// Test de la classe Coord

TEST_CASE("Test du constructeur"){
        Coord c1 = Coord(0, 0);
        Coord c2 = Coord(TAILLEGRILLE-1, 0);
        CHECK(c1.getY() == 0);
        CHECK(c1.getX() == 0);
        CHECK(c2.getX() == TAILLEGRILLE-1);
        CHECK(c2.getY() == 0);
        CHECK_THROWS_AS(Coord(-1, 0), std::exception);
        CHECK_THROWS_AS(Coord(0, TAILLEGRILLE), std::exception);
}

TEST_CASE("Test des getters"){
        Coord c1 = Coord(0, 3);
        CHECK(c1.getX() == 0);
        CHECK_FALSE(c1.getY() != 3);
}

TEST_CASE("Test de =="){
        Coord c1 = Coord(0,6), c2 = Coord(0,6), c3 = Coord(1,6);
        CHECK(c1 == c2);
	CHECK_FALSE(c1 == c3);
}

TEST_CASE("Test de !="){
        Coord c1 = Coord(0,0);
        CHECK(c1 != Coord(1,0));
        CHECK(c1 != Coord(0,7)); 
        CHECK(c1 != Coord(2,2));
}

// Test de la classe EnsCoord

EnsCoord ensembledetest() {
	vector<Coord> v = {Coord(0,0), Coord(5,1), Coord(2,3), Coord(7,0)};
	EnsCoord E = EnsCoord(v);
	return E;
}

TEST_CASE("test de la methode contient (Ens)"){
	EnsCoord E2 = ensembledetest();
	CHECK(E2.contient(Coord(5,1)));
	CHECK_FALSE(E2.contient(Coord(2,4)));
}

TEST_CASE("test de la methode ajoute (Ens)"){
	EnsCoord E3 = ensembledetest();
	E3.ajoute(Coord(0,0));
	CHECK(E3.taille() == 4);
	E3.ajoute(Coord(1,1));
	CHECK(E3.taille() == 5);
	CHECK(E3.ieme(4) == Coord(1,1));
}

TEST_CASE("test de la methode supprime (Ens)"){
	EnsCoord E4 = ensembledetest();
	E4.supprime(Coord(0,0));
	CHECK(E4.taille() == 3);
	CHECK_THROWS_AS(E4.supprime(Coord(0,0)), std::exception);
}

TEST_CASE("test de la methode estVide (Ens)"){
	EnsCoord E5 = ensembledetest();
	EnsCoord E5B= EnsCoord();
	CHECK_FALSE(E5.estVide());
	CHECK(E5B.estVide());
}

TEST_CASE("test de la methode taille (Ens)"){
	EnsCoord E6 = ensembledetest();
	EnsCoord E6B= EnsCoord();
	CHECK(E6.taille() == 4);
	CHECK(E6B.taille()== 0);
}

TEST_CASE("test de la methode ieme (Ens)"){
	EnsCoord E7 = ensembledetest();
	CHECK(E7.ieme(1) == Coord(5,1));
	CHECK(E7.ieme(3) == Coord(7,0));
}

TEST_CASE("test de la fonction voisines") {
	
	EnsCoord v1 = voisines(Coord(0,0)), v2 = voisines(Coord(2,1)); 
	EnsCoord v3 = voisines(Coord(3,4)), v4 = voisines(Coord(4,2));

	CHECK(v1.contient(Coord(0,1)));
	CHECK(v1.contient(Coord(1,0)));
	CHECK(v1.contient(Coord(1,1)));
	
	CHECK(v2.contient(Coord(1,0)));
	CHECK(v2.contient(Coord(1,1)));
	CHECK(v2.contient(Coord(1,2)));
	CHECK(v2.contient(Coord(2,2)));
	CHECK(v2.contient(Coord(3,2)));
	CHECK(v2.contient(Coord(3,1)));
	CHECK(v2.contient(Coord(3,0)));
	CHECK(v2.contient(Coord(2,0)));

	CHECK(v3.contient(Coord(2,3)));
	CHECK(v3.contient(Coord(2,4)));
	CHECK(v3.contient(Coord(3,3)));
	CHECK(v3.contient(Coord(4,3)));
	CHECK(v3.contient(Coord(4,4)));
	
	CHECK(v4.contient(Coord(4,1)));
	CHECK(v4.contient(Coord(3,1)));
	CHECK(v4.contient(Coord(3,2)));
	CHECK(v4.contient(Coord(3,3)));
	CHECK(v4.contient(Coord(4,3)));
}

TEST_CASE("test de la fonction choixHasard") {
	EnsCoord e = ensembledetest();
	Coord c1 = e.choixHasard(), c2 = e.choixHasard(), c3 = e.choixHasard();
	CHECK(e.contient(c1));
	CHECK(e.contient(c2));
	CHECK(e.contient(c3));
	WARN(c2 != c3);
	WARN(c1 != c3);
	WARN(c1 != c2);
}

int main(int argc, const char **argv) {
	doctest::Context context(argc, argv);
	int test_result = context.run();
	if (context.shouldExit()) return test_result;

	srand(time(NULL)); // Permet de creer des nombres pseudos aleatoires

	// Test de la surcharge d'affichage pour Coord
	Coord c1 = Coord(0,0), c2 = Coord(2,7);
	// Resultat attendu: (0,0)
	cout << c1 << endl;
	// Resultat attendu: (2,7)
	cout << c2 << endl;
	
	// Test de la surchage d'affichage pour EnsCoord
	vector<Coord> tab = {c1, c2};
	EnsCoord E = EnsCoord(tab);
	cout << E << endl;
    
	EnsCoord v1 = voisines(Coord(0,0)), v2 = voisines(Coord(2,1)); 
	EnsCoord v3 = voisines(Coord(3,4)), v4 = voisines(Coord(4,2));

	return 0;
}

