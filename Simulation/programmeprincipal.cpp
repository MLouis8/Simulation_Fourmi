#include "programmeprincipal.hpp"


bool VcontientCoord(vector<Coord> tabC, Coord c1) {
    for (Coord c2 : tabC) {
        if (c2 == c1) return true;
    }
    return false;
}

bool estSeulNid(vector<Coord> tabN, Coord n) {
    for (Coord c : tabN)
    {
        if (abs(n.getX()-c.getX()) < 10 and abs(n.getY()-c.getY()) < 10) return false;
    }
    return true;
}

bool nidcomplet(EnsCoord sucres, Coord c) {
    bool HG = sucres.contient(c), HD = sucres.contient(Coord(c.getX(), c.getY()+1));
    bool BG = sucres.contient(Coord(c.getX()+1, c.getY())), BD = sucres.contient(Coord(c.getX()+1, c.getY()+1));
    return not HG and not HD and not BG and not BD;
}

EnsCoord aleaSucre(int nbSucres, EnsCoord nids) {
    vector<Coord> tabS;
    int i = 0;
	while (i < nbSucres)
    {
        size_t x = rand()%TAILLEGRILLE, y = rand()%TAILLEGRILLE;
        Coord c = Coord(x, y);
        if (nids.contient(c) or VcontientCoord(tabS, c)) i--;
        else tabS.push_back(c);
        i++;
    }
	return EnsCoord(tabS);
}

/*
 * Fonction qui prend le nombre de colonies et qui renvoie un EnsCoord
 * contenant les coins des nids de chaque colonie
 */
EnsCoord aleaNid(int nbColonie) {
	vector<Coord> tab;
    for (int i = 0; i < nbColonie ; i++)
    {
        bool malPlace = true;
        while (malPlace) {
            // un nid doit etre decolle de 6 cases des enceintes
            // un nid doit etre loin de 12 cases d'un autre nid
            // un nid doit etre loin de 4 cases des sucres et obstacles
            Coord c = Coord(5+rand()%(TAILLEGRILLE-8), 5+rand()%(TAILLEGRILLE-8));
            if (estSeulNid(tab, c)) malPlace = false;
            if (not malPlace) tab.push_back(c);
        }
    }
	return EnsCoord(tab);
}

EnsCoord sommeNids(vector<EnsCoord> tabE) {
	vector<Coord> t;
	for (EnsCoord e : tabE)
	{
		for (Coord c : e.getTabCoord())
		{
			t.push_back(c);
		}
	}
	return EnsCoord(t);
}

vector<EnsCoord> nidsColonies(EnsCoord coins) {
    vector<EnsCoord> tabE;
    for (Coord c : coins.getTabCoord())
    {
        tabE.push_back(EnsCoord({
            c, 
            Coord(c.getX(), c.getY()+1), 
            Coord(c.getX()+1, c.getY()),
            Coord(c.getX()+1, c.getY()+1)
        }));
    }
    return tabE;
}

EnsCoord positionsFourmis(Coord nid) {
	vector<Coord> tabf = {
        Coord(nid.getX()-1, nid.getY()-1),
        Coord(nid.getX()-1, nid.getY()),
        Coord(nid.getX()-1, nid.getY()+1),
        Coord(nid.getX()-1, nid.getY()+2),
        
        Coord(nid.getX(), nid.getY()-1),
        Coord(nid.getX()+1, nid.getY()-1),
        Coord(nid.getX(), nid.getY()+2),
        Coord(nid.getX()+1, nid.getY()+2),
        
        Coord(nid.getX()+2, nid.getY()-1),
        Coord(nid.getX()+2, nid.getY()),
        Coord(nid.getX()+2, nid.getY()+1),
        Coord(nid.getX()+2, nid.getY()+2)
    };
	return EnsCoord(tabf);
}

void Bilan(vector<Colonie> TabCols) {
	cout << endl << "------------------------------------------------------------------------" << endl << endl;
	for (int i = 0; i < TabCols.size(); i++)
	{
		cout << "Colonie " << i+1 << ":" << endl;
		cout << TabCols[i] << endl;
	}
	cout << endl << "------------------------------------------------------------------------" << endl;
}

bool victoire(vector<Colonie> TabCols) {
	int compteurD = 0;
	for (int i = 0; i < TabCols.size(); i++)
	{
		intermediaire(TabCols[i], compteurD);
	}
	if (compteurD == TabCols.size()-1) return true;
	else return false;
}

void intermediaire(Colonie col, int& compteurD) {
	for (Fourmi f : col.get_Colonie())
	{
		if (f.enVie()) return;
	}
	compteurD++;
}

void mettreAJourUneFourmi(Fourmi& f, Grille& g, vector<Colonie>& TabCol) {
    
	Coord cf = f.get_Coord();
    Place pf = g.chargePlace(cf);
    EnsCoord voiscoord = voisines(cf);
    int col = f.get_Colonie();

	// Si la fourmie est morte on essaie de la remettre sur son nid 
	// et on la ressussite si il y a assez de sucre sinon on la touche pas
	if (not f.enVie()) {
		if (TabCol[f.get_Colonie()].get_nbSucres() > 3) {
			// on ressussite la fourmie au bord du nid
			f.ressucite();
			// on enleve trois sucres
			TabCol[f.get_Colonie()].enleveSucre();
		}
		return;
	}

	if (f.porteSucre()) {
		Place procheNid = pf;
		// on itere sur les coordonnees de voisines
		for (Coord c : voiscoord.getTabCoord())
		{
			Place voisin = g.chargePlace(c);
			// si la coordonnee correspond a un nid on fait comme tel
			if (voisin.contientNid() and col == voisin.get_Nid()) {
				PoserSucre(f, pf, voisin, TabCol);
				g.rangePlace(pf);
				g.rangePlace(voisin);
				return;
			}
			// sinon on cherche le voisin le plus proche du nid
			if (voisin.estVide() and estPlusProcheNid(voisin, procheNid, col))
				procheNid = voisin;
		}
		// On execute l'action de rapprocher du nid et deposer un pheromone
		DeplacerPoser(f, pf, procheNid);

		// Et on range les places modifiees
		g.rangePlace(pf);
		g.rangePlace(procheNid);
	
	} else {
		for (Coord cv : voiscoord.getTabCoord())
		{
			Place pv = g.chargePlace(cv);
			if (ConditionCombat(f, pf, pv)) {
				int colo = pv.get_colonie_f();
				Fourmi& fv = TabCol[colo].donneFourmi(pv.numeroFourmi());
				Combat(f, pf, fv, pv);
				g.rangePlace(pf);
				g.rangePlace(pv);
				return;
			}
		}
		for (int regle = 1 ; regle < 5 ; regle++)
		{
			if (regle == 4) { // Si la fourmi est en recherche de base
				// on charge trois place au hasard
				Place loinNid = g.chargePlaceAleaNonVide(voiscoord);
				for (int i = 0 ; i < 0 ; i++) {
					Coord cv = voiscoord.choixHasard();
					Place Pcv = g.chargePlace(cv);
					if (not estPlusProcheNid(Pcv, loinNid, col))
						loinNid = Pcv;
				}
				// on garde seulement la place la plus loin du nid
				Place vois = loinNid;

				if (condition_n(regle, f, pf, vois)) {
					action_n(regle, f, pf, vois);
					g.rangePlace(pf);
					g.rangePlace(vois);
					return;
				}

			} else {

				for (Coord cv : voiscoord.getTabCoord())
				{
					Place vois = g.chargePlace(cv);
					if (condition_n(regle, f, pf, vois)) {
						action_n(regle, f, pf, vois);
						g.rangePlace(pf);
						g.rangePlace(vois);
						return;
					}
				}
			}
		}
	}
}

void mettreAJourEnsFourmis(Grille& GrilleJeu, vector<Colonie>& TabCol) {
	for (Colonie& col : TabCol)
	{
    	for (Fourmi& f : col.get_Colonie())
			mettreAJourUneFourmi(f, GrilleJeu, TabCol);
	}
}

void afficheTab(vector<Fourmi> tab) {
	cout << endl;
	for (Fourmi f : tab) {
		cout << f.get_Coord();
	}
	cout << endl;
}

int sommeSucreNids(EnsCoord nids, Grille GrilleFin) {
	int somme = 0;
	for (Coord c : nids.getTabCoord())
	{
		Place p = GrilleFin.chargePlace(c);
		somme += p.qteSucre();
	}
	return somme;
}
