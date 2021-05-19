/**
	Fichier d'entete pour le programme principal
**/

#ifndef PROGRAMMRPRINCIPAL_HPP
#define PROGRAMMEPRINCIPAL_HPP

#include "coord.hpp"
#include "ants.hpp"
#include "grille.hpp"
#include "place.hpp"
#include "condition.hpp"

using namespace std;

/*
 * Fonction qui teste si un vector de coordonnees contient une certaine coordonnee
 */
bool VcontientCoord(vector<Coord> tabC, Coord c1);

/*
 * Fonction qui teste si un nid (dont on passe les coordonnees) respecte les conditions de placement
 */
bool estSeulNid(vector<Coord> tabN, Coord n);

/*
 * Fonction qui teste si un nid est complet
 */
bool nidcomplet(EnsCoord sucres, Coord c);

/*
 * Fonction qui initialise les positions de sucre aleatoirement.
 * Prend en parametre le nombre de sucres a ajouter
 * Prend en parametre l'ensemble de coordonnee de toutes les cases de nid pour les eviter.
 */
EnsCoord aleaSucre(int nbSucres, EnsCoord nids);

/*
 * Fonction qui initialise les positions des nids au depart
 * Prend en parametres le nombre de colonies
 * Fonction a appeler en premier pour l'initialisation de la grille
 * renvoie les coins HG de chaque colonies
 */
EnsCoord aleaNid(int nbColonie);

/*
 * Fonction qui prend en parametre un tableau de EnsCoord
 * Renvoie l'ensemble de Coord de tous les EnsCoord
 */
EnsCoord sommeNids(vector<EnsCoord> tabE);

/*
 * Fonction qui donne un EnsCoord par colonie de leurs nid
 *
 */
vector<EnsCoord> nidsColonies(EnsCoord coins);

/*
 * Fonction qui initialise les positions des fourmis au depart
 * Prend en parametres les coordonnes du coin haut gauche du nid de la colonie
 * Renvoie l'ensemble des coordonnees des fourmies
 *
 */
EnsCoord positionsFourmis(Coord nid);

/* 
 * déplace toutes les fourmis
 * en appliquant les règles de leur comportement
*/
void mettreAJourUneFourmi(Fourmi& f, Grille& g, vector<Colonie>& TabCol);

/*
 * Fonction qui met a jour l'ensemble de la grille
 */
void mettreAJourEnsFourmis(Grille& GrilleJeu, vector<Colonie>& TabCol);

/*
 * Fonction qui affiche un vecteur de fourmis
 */
void afficheTab(vector<Fourmi> tab);

/*
 * Fonction qui renvoie la somme des sucres contenus dans un nid
 */
int sommeSucreNids(EnsCoord nids, Grille GrilleFin);

/*
 * Fonction d'affichage pour le bilan final
 * Affiche les colonies, le nombre de fourmi qui leur reste
 */
void Bilan(vector<Colonie> TabCols);

/*
 * Fonction qui determine si le jeu est fini,
 * Si jamais il ne reste qu'une seule colonie en vie
 */
bool victoire(vector<Colonie> TabCols);

/* fonction pour la victoire */
void intermediaire(Colonie col, int& compteurD);

#endif  // PROGRAMMEPRINCIPAL_HPP
