#include "condition.hpp"

using namespace std;

// Les conditions

bool condition_n(int r, Fourmi f, Place p1, Place p2) {
    switch(r) {
        case 1: return ConditionPeutChargerSucre(f, p1, p2);
        case 2: return ConditionChercheSucreSuitPiste(f, p1, p2);
        case 3: return ConditionChercheSucrePiste(f, p1, p2);
        case 4: return ConditionChercheSucre(f, p1, p2);
	}
}

bool ConditionCombat(Fourmi f, Place p1, Place p2) {
    return p2.contientFourmi() and (p2.get_colonie_f() != f.get_Colonie()) and p2.fourmi_en_vie();
}

bool ConditionPeutChargerSucre(Fourmi f, Place p1, Place p2) {
    return (not f.porteSucre()) and p2.contientSucre() and not p2.contientNid();
}

bool ConditionPoseSucreNid(Fourmi f, Place p1, Place p2) {
    return f.porteSucre() and p2.get_Nid() == f.get_Colonie();
}

bool ConditionRentreNid(Fourmi f, Place p1, Place p2) {
    return f.porteSucre() and p2.estVide() and estPlusProcheNid(p2, p1, f.get_Colonie());
}

bool ConditionChercheSucreSuitPiste(Fourmi f, Place p1, Place p2) {
    return not f.porteSucre() and p1.estSurUnePiste() and p2.estVide() and not estPlusProcheNid(p2, p1, f.get_Colonie()) and p2.estSurUnePiste();
}

bool ConditionChercheSucrePiste(Fourmi f, Place p1, Place p2) {
    return not f.porteSucre() and p2.estSurUnePiste() and p2.estVide();
}

bool ConditionChercheSucre(Fourmi f, Place p1, Place p2) {
    return not f.porteSucre() and p2.estVide();
}

// Actions qui y correspondent

void action_n(int r, Fourmi& f, Place& p1, Place& p2) {
    switch(r) {
        case 1: ChargerSucre(f, p1, p2); return;
        case 2: case 3: case 4: deplaceFourmi(f, p1, p2); return;
    }
}

void Combat(Fourmi& f1, Place& p1, Fourmi&f2, Place&p2) {
    int gagnant = rand()%2; // renvoie 1 ou 0
    if (gagnant) {
        f1.meurt();
        p1.Fmeurt();
    } else {
        f2.meurt();
        p2.Fmeurt();
    }
}

void ChargerSucre(Fourmi& f, Place& p1, Place& p2) {
    f.prendSucre();
	p2.enleveSucre();
    p1.posePheroSucre();
}

void PoserSucre(Fourmi& f, Place& p1, Place& p2, vector<Colonie>& TabCols) {
    f.poseSucre();
	p2.poseSucre();
    TabCols[p2.get_Nid()].ajouteSucre();
}

void PoserduSucre(Fourmi& f, Place& p1, Place& p2) {
    f.poseSucre();
	p2.poseSucre();
}

void DeplacerPoser(Fourmi& f, Place& p1, Place& p2) {
    deplaceFourmi(f, p1, p2);
    p2.posePheroSucre();
}
