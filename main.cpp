#include <SFML/Graphics.hpp>
#include <iostream>
#include "coord.hpp"
#include "ants.hpp"
#include "place.hpp"
#include "grille.hpp"
#include "condition.hpp"
#include "graphique.hpp"
#include "programmeprincipal.hpp"

using namespace std;
using namespace sf;


int main(int argc, char **argv) {
	srand(time(NULL));

    // Ouverture de la fenetre SFML avec antialiasing
	sf::ContextSettings settings;
	settings.antialiasingLevel = 3;
	size_t t = 800;
	RenderWindow fenetre(VideoMode(t,t), "Simulation", sf::Style::Default, settings);

	// Parametres
	int nbColonies; string Cmode;
	bool journee = true; sf::Color mode;
	cout << "Entrer le nombre de colonies :";
	cin>>nbColonies;
	cout << endl << "Entrer le mode d'affichage (jour/nuit): ";
	cin>>Cmode;
	if (Cmode == "nuit") { mode = nuit; journee = false; }
	else mode = jour;

	// Permet d'eviter une boucle infinie si les nids sont trop rapproches
	if (nbColonies*10 >= TAILLEGRILLE) throw runtime_error("Trop de colonies pour la taille de l'ecran");

	// Initialisation des premieres variables
	EnsCoord CoinsNid  = aleaNid(nbColonies);
    vector<EnsCoord> nids = nidsColonies(CoinsNid);
	EnsCoord sucre = aleaSucre(6, sommeNids(nids));
	EnsCoord tabObs= aleaSucre(TAILLEGRILLE/5, sommeNids(nids));
	vector<Colonie> TabCols;

	for (int i = 0; i < nbColonies; i++)
	{
		EnsCoord posF = positionsFourmis(CoinsNid.ieme(i));
		vector<Fourmi> TabF = creeTabFourmis(posF, i);
		TabCols.push_back(Colonie(nids[i], TabF));
	}
	
	// Creation et initialisation de la grille par rapport aux donnees precedentes
	Grille GrilleJeu = Grille(nbColonies);
	cout << "Debut initialisation" << endl;
	GrilleJeu.initialiseGrille(TabCols, sucre, tabObs); // fonction lineariser pheronid prend bcp de temps
	cout << "Fin initialisation" << endl;

	// Execution du programme
    while(fenetre.isOpen()) {
		// Met la fenetre a 0 avec le bon fond
		fenetre.clear(mode);
		// dessine la premiere grille
		dessine(fenetre, GrilleJeu, journee);
		// affichage
		fenetre.display();
		sleep(seconds(1)); // on attend une seconde

		// Programme principal
		int i = 0;
		while (not victoire(TabCols)) {			
			i++;
			// ajout du sucre tous les 30 tours
			if (i%30 == 0) GrilleJeu.ajouteSucre();
			// Remet la fenetre a 0 avec le bon fond
			fenetre.clear(mode);
			// Met a jour les deplacements des fourmis
			mettreAJourEnsFourmis(GrilleJeu, TabCols);
			// Diminue de 5 tous les pheromones de sucre
			GrilleJeu.diminuePheroSucre();
			// Dessine la fenetre
			dessine(fenetre, GrilleJeu, journee);
			// Actualise la fenêtre
			fenetre.display();
		}

		// Attend quelque secondes
		sleep(seconds(2));
		// fermeture de la fenetre
		fenetre.close();
	}
	
	// On met l'affichage de fin avec le bilan
	Bilan(TabCols);

	// FIN DU PROGRAMME
	
    return 0;
}