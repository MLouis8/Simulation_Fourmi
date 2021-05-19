#include "grille.hpp"

Grille::Grille(int nb_col){
    for(size_t i = 0; i < TAILLEGRILLE; i++)
    {
        vector<Place> v1;
        for (size_t j = 0; j < TAILLEGRILLE; j++)
        {
            Coord c = Coord(i,j);
            Place p = Place(c, nb_col);
            v1.push_back(p);
        }
        grille.push_back(v1);
    }
}
    

Place Grille::chargePlace(Coord c) const {
    for (size_t i = 0; i < TAILLEGRILLE; i++)
    {
        for (size_t j = 0; j < TAILLEGRILLE; j++)
        {
            if (grille[i][j].get_Coord() == c){
                return grille[i][j];
            }
        }
    }
    throw runtime_error("La place recherchee n'existe pas");
}

Place Grille::chargePlaceAleaNonVide(EnsCoord e) const {
    int essais = 0;
    do {
        Coord c = e.choixHasard();
        for (size_t i = 0; i < TAILLEGRILLE; i++)
        {
            for (size_t j = 0; j < TAILLEGRILLE; j++)
            {
                if (grille[i][j].get_Coord() == c and grille[i][j].estVide()){
                    return grille[i][j];
                }
            }
        }
        essais++;
    } while(essais < 100); // tant que la place chargee est vide
    return chargePlace(e.ieme(0));
    //throw runtime_error("La place recherchee n'existe pas");
}

int Grille::get_Colonie(Coord c) const{
    Place p = chargePlace(c);
    return p.get_Nid();
}

void Grille::rangePlace(Place p){
    for (size_t i = 0; i < TAILLEGRILLE; i++)
    {
        for (size_t j = 0; j < TAILLEGRILLE; j++)
        {
            if( p.get_Coord() == grille[i][j].get_Coord() ){
                grille[i][j] = p;
            }   
        }
    }
}

void Grille::diminuePheroSucre(){
    for (size_t i = 0; i < TAILLEGRILLE; i++)
    {
        for (size_t j = 0; j < TAILLEGRILLE; j++)
        {
            Coord c = Coord(i,j);
            Place p = chargePlace(c);

            if (p.estSurUnePiste())
                p.diminuePheroSucre();
            rangePlace(p);
        }
    }
}

void Grille::placeNid( EnsCoord e, int col) {
    for (Coord c : e.getTabCoord() )
    {
        if ( not(chargePlace(c).contientSucre()) and not(chargePlace(c).contientFourmi()) )
        {
            Place p = chargePlace(c);    
            p.poseNid(col);
            p.posePheroNid(1,col);
            rangePlace(p);
        }
    }
}

void Grille::placeSucre( EnsCoord e) {
    for (Coord c : e.getTabCoord() )
    {
        if ( not(chargePlace(c).contientNid()) and not(chargePlace(c).contientFourmi()) )
        {
            Place p = chargePlace(c);    
            p.rempliSucre();
            rangePlace(p);
        }
    }
}

void Grille::placeFourmi( vector<Fourmi> TabF) {
    for( Fourmi f : TabF)
    {
        if (not(chargePlace(f.get_Coord())).contientNid() and not(chargePlace(f.get_Coord())).contientSucre())
        {
            Place p = chargePlace(f.get_Coord());
            p.poseFourmi(f);
            rangePlace(p);
        }
    }
}

void Grille::placeObs(EnsCoord Obs) {
    for (Coord c : Obs.getTabCoord() )
    {
        Place p = chargePlace(c);
        if (p.estVide()) { 
            p.poseObstacle();
            rangePlace(p);
        }
    }
}

void Grille::initialiseGrille(vector<Colonie> TabCol, EnsCoord sucre, EnsCoord Obs){
    placeSucre(sucre);
    placeObs(Obs);
    for (int i = 0; i < TabCol.size(); i++)
    {
        placeFourmi(TabCol[i].get_Colonie());
        placeNid(TabCol[i].coordNid(), i);
        lineariserPheoNid(i);
    }
}

void Grille::lineariserPheoNid(int col){
    bool stable = false;
    while ( not(stable) )
    {
        stable = true;
        for (size_t i = 0; i < TAILLEGRILLE; i++)
        {
            for (size_t j = 0; j < TAILLEGRILLE; j++)
            {
                Coord c = Coord(i,j);
                Place p = chargePlace(c); 
                if( p.pheroNid(col) < 1 )
                {
                    EnsCoord coordVois = voisines(c);
                    float maxPhero = 0;
                    for( Coord v  : coordVois.getTabCoord())
                    {
                        Place voisin = chargePlace(v);
                        maxPhero = max(maxPhero, voisin.pheroNid(col));
                    }
                    maxPhero = maxPhero - (1. / float(TAILLEGRILLE));
                    if( maxPhero > p.pheroNid(col)) 
                    {
                        p.posePheroNid(maxPhero, col);
                        rangePlace(p);   
                        stable = false;
                    }
                }
            }
        }
    }
}

void Grille::ajouteSucre() {
    bool placePrise = true;
    int compteur = 0;
	while (placePrise)
    {
        compteur++;
        size_t x = rand()%TAILLEGRILLE, y = rand()%TAILLEGRILLE;
        Place p = chargePlace(Coord(x, y));
        if (p.estVide()) {
            p.rempliSucre();
            rangePlace(p);
            placePrise = false;
        }
        if (compteur > 1000) throw runtime_error("ajout de sucre impossible !");
    }
}

void Grille::coherence(vector<Fourmi> TabF) const {
    for (size_t i = 0; i < TabF.size(); i++)
    {
        Fourmi f = TabF[i];
        if( i != f.get_Num() ) throw runtime_error(" stocké par erreur une fourmi à un autre indice ");
        if( chargePlace(f.get_Coord()).numeroFourmi() != i or chargePlace(f.get_Coord()).numeroFourmi() == -1 ){
            throw runtime_error("fourmi qui est dans une case qui est vide ou indice fourmi faux.");
        }
    }
    for (size_t i = 0; i < TAILLEGRILLE; i++)
    {
        for (size_t j = 0; j < TAILLEGRILLE; j++)
        {
            Coord c = Coord(i,j);
            Place p = chargePlace(c);
            if( p.get_Coord() != c ) throw runtime_error(" stocké par erreur une place à une autre position");
            if( p.contientFourmi() and  p.numeroFourmi() >= TabF.size()) {
                    throw runtime_error("une case qui contient une fourmi n’existant pas dans le tableau");
            }

        }
            
    }
}
