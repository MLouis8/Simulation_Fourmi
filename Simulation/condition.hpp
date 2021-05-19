/**
    Fichier pour les six conditions (sept ds futur) pour le deplacement des fourmis
    Avec les actions qui vont avec.
**/

#ifndef CONDITION_HPP
#define CONDITION_HPP
#pragma GCC diagnostic ignored "-Wreturn-type"

#include "coord.hpp"
#include "place.hpp"
#include "grille.hpp"
#include "ants.hpp"

using namespace std;

// Conditions : (voir sujet principal)

bool condition_n(int r, Fourmi f, Place p1, Place p2);

bool ConditionPeutChargerSucre(Fourmi f, Place p1, Place p2);

bool ConditionPoseSucreNid(Fourmi f, Place p1, Place p2);

bool ConditionRentreNid(Fourmi f, Place p1, Place p2);

bool ConditionChercheSucreSuitPiste(Fourmi f, Place p1, Place p2);

bool ConditionChercheSucrePiste(Fourmi f, Place p1, Place p2);

bool ConditionChercheSucre(Fourmi f, Place p1, Place p2);

bool ConditionCombat(Fourmi f, Place p1, Place p2);

// Actions qui y correspondent

void action_n(int r, Fourmi& f, Place& p1, Place& p2);

void ChargerSucre(Fourmi& f, Place& p1, Place& p2);

void PoserSucre(Fourmi& f, Place& p1, Place& p2, vector<Colonie>& TabCols);

void PoserduSucre(Fourmi& f, Place& p1, Place& p2);

void DeplacerPoser(Fourmi& f, Place& p1, Place& p2);

void Combat(Fourmi& f1, Place& p1, Fourmi&f2, Place&p2);

#endif // CONDITION_HPP
