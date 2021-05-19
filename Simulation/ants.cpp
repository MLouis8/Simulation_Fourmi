#include "ants.hpp"

vector<Fourmi> creeTabFourmis( EnsCoord e, int col){
    vector<Fourmi> TabFourmis;
    for (int i = 0; i < e.taille(); i++)
    {
        TabFourmis.push_back( Fourmi(e.getTabCoord()[i],i,col) );
    }
    return TabFourmis;
}
