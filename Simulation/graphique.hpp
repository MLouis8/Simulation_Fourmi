/**
	Fichier d'entete pour les fonctions de l'interface graphique
**/

#ifndef GRAPHIQUE_HPP
#define GRAPHIQUE_HPP

#include <stdexcept>
#include <SFML/Graphics.hpp>

#include "place.hpp"
#include "coord.hpp"
#include "ants.hpp"
#include "grille.hpp"

using namespace sf;
using namespace std;

/**
  * Fonctions pour la conversion Coord -> Vector2f (coordonnees graphique)
  **/
Vector2f coord2vectorPetitRond(Coord c, size_t t);
Vector2f coord2vectorGrandRond(Coord c, size_t t);
Vector2f coord2vectorCarree(Coord c, size_t t);

/**
  * Fonctions pour dessiner les objects
  *
  **/
void dessineFourmi(RenderWindow& w, Coord C, Color coul);
void dessineNid(RenderWindow& w, Coord C, Color coul);
void dessineGuerriere(RenderWindow& w, Coord C, Color coul);
void dessinePheroSucre(RenderWindow& w, Coord C, size_t alpha, Color coul);
void dessineObstacle(RenderWindow& w, Coord C, Color coul);

/**
  * Fonction de dessin principale appellee dans le programme principal
  * @param: w fenetre graphique, Grillejeu Grille de la simulation, jour bool pour le jour
  * 
  * Affiche l'etat actuel du jeu
  **/
void dessine(RenderWindow& w, Grille Grillejeu, bool jour);

/**
  * Fonction de test
  **/
void metAJourDessin(Grille GrilleJeu, RenderWindow& w);


/**
    Fonction qui prend en argument une coordonnee de la grille et la taille de la fenetre
    Et qui renvoie un Vector2f, coordonnee de la fentetre graphique equivalente
**/
Vector2f coord2vector2f(Coord c, size_t t);

/* Dico des couleurs:
	 * Pour chaque couleur de fourmi :
	 * 		- une pour les fourmis de base et le nid, 
	 *		- une pour les pheromones pastel-clair,
	 *		- une pour les guerrieres foncee
	 *
	 * Une couleur pour les obstacles :
	 * 		- noir si le fond est jour
	 *		- marron si le fond est nuit
	 *
	 * Une couleur pour le fond :
	 *		- noir-violet-fonce pour la nuit
	 *		- sable pour le jour
	 *	
	 * Et du blanc pour le sucre
	 *
	 */
// Fonction qui donne une couleur en fonction de la colonie
sf::Color dicoCouleur(int col, bool ph);

	static sf::Color rouge   = sf::Color::Red;
	static sf::Color Phrouge = sf::Color(222, 101, 156); //sf::Color(255,102,102);
	static sf::Color Grouge  = sf::Color(102,0,17);

	static sf::Color verte    = sf::Color::Green;
	static sf::Color Phverte  = sf::Color(102,255,102);
	static sf::Color Gverte   = sf::Color(0,51,8);

	static sf::Color bleue	 = sf::Color::Blue;
	static sf::Color Phbleue = sf::Color(102,102,255);
	static sf::Color Gbleue  = sf::Color(17,0,102);

	static sf::Color jaune 	 = sf::Color::Yellow;
	static sf::Color Phjaune = sf::Color::Yellow;
	static sf::Color Gjaune  = sf::Color::Yellow;

	static sf::Color orange  = sf::Color::Yellow;
	static sf::Color Phorange= sf::Color::Yellow;
	static sf::Color Gorange = sf::Color::Yellow;

	static sf::Color nuit 	 = sf::Color(5,0,12);
	static sf::Color jour	 = sf::Color(197,183,131);
	static sf::Color obsjour = sf::Color::Black;
	static sf::Color obsnuit = sf::Color(153,102,0);

	static sf::Color blanc	 = sf::Color::White;

#endif // GRAAPHIQUE_HPP
