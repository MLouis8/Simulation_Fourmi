#include "graphique.hpp"

Vector2f coord2vectorPetitRond(Coord c, size_t t) {
	size_t x = (2*c.getX()+0.25)*(t/TAILLEGRILLE)*0.5;
	size_t y = (2*c.getY()+0.25)*(t/TAILLEGRILLE)*0.5;
	return Vector2f(x,y);
}

Vector2f coord2vectorGrandRond(Coord c, size_t t) {
	size_t x = (2*c.getX())*(t/TAILLEGRILLE)*0.5;
	size_t y = (2*c.getY())*(t/TAILLEGRILLE)*0.5;
	return Vector2f(x,y);
}

Vector2f coord2vectorCarree(Coord c, size_t t) {
	size_t x = (2*c.getX())*(t/TAILLEGRILLE)*0.5;
	size_t y = (2*c.getY())*(t/TAILLEGRILLE)*0.5;
	return Vector2f(x,y);
}

void dessineFourmi(RenderWindow& w, Coord C, Color coul) {
	size_t t = w.getSize().x;
	Vector2f P = coord2vectorPetitRond(C, t);
	size_t rad = (t / TAILLEGRILLE)/2;

	CircleShape fourmi(rad);

	fourmi.setFillColor(coul);
	fourmi.setOutlineColor(coul);
	fourmi.setPosition(P);
	w.draw(fourmi);
}

void dessineGuerriere(RenderWindow& w, Coord C, Color coul) {
	
	size_t t = w.getSize().x;
	Vector2f P = coord2vectorPetitRond(C, t);
	size_t rad = (t / TAILLEGRILLE)/3;

	CircleShape Guerriere(rad, 6);

	Guerriere.setFillColor(coul);
	Guerriere.setOutlineColor(Color::Black);
	Guerriere.setPosition(P);
	w.draw(Guerriere);

}

void dessineNid(RenderWindow& w, Coord C, Color coul) {

	size_t t = w.getSize().x;
	Vector2f P = coord2vectorGrandRond(C, t);
	
	size_t rad = t/ TAILLEGRILLE;
	CircleShape nid(rad);

	nid.setPosition(P);
	nid.setFillColor(coul);
	w.draw(nid);

}

void dessineObstacle(RenderWindow& w, Coord C, Color coul) {

	size_t t = w.getSize().x;
	Vector2f P = coord2vectorCarree(C, t);
	size_t cell = t / TAILLEGRILLE;
	
	sf::RectangleShape obs(Vector2f(cell, cell));
	obs.setPosition(P);
	obs.setFillColor(coul);
	w.draw(obs);

}

void dessinePheroSucre(RenderWindow& w, Coord C, size_t alpha, Color coul) {
	
	size_t t = w.getSize().x;
	Vector2f P = coord2vectorCarree(C, t);
	size_t cell = t / TAILLEGRILLE;
	
	sf::RectangleShape phero(Vector2f(cell, cell));
	
	phero.setPosition(P);
	sf::Color transparence = Color(coul.r, coul.g, coul.b, alpha);
	phero.setFillColor(transparence);
	w.draw(phero);

}

sf::Color dicoCouleur(int col, bool ph) {
	switch(col) {
		case 0:
			if (ph) return Phrouge;
			else return rouge;
		case 1:
			if (ph) return verte;
			else return Phverte;
		case 2:
			if (ph) return bleue;
			else return Phbleue;
		case 3:
			if (ph) return Phjaune;
			else return jaune;
		case 4:
			if (ph) return Phorange;
			else return orange;
		default: //du rouge
			if (ph) return Phrouge;
			else return rouge;
	}
}

void dessine(RenderWindow& w, Grille Grillejeu, bool jour) {
	// Pour chaque place :
	for (size_t i = 0 ; i < TAILLEGRILLE ; i++)
	{
		for (size_t j = 0 ; j < TAILLEGRILLE ; j++)
		{
			Place P = Grillejeu.chargePlace(Coord(i,j));
			
			if (P.contientNid()) {
				dessineObstacle(w, Coord(i,j), dicoCouleur(P.get_Nid(), false));
			} else if (P.contientSucre()) {
				dessinePheroSucre(w, Coord(i,j), (P.qteSucre()*255)/10, Color::White);
			} else if (P.contientFourmi()) {
				if (P.fourmi_en_vie()) {
					dessineFourmi(w, Coord(i,j), dicoCouleur(P.get_colonie_f(), false));
				} else {
					dessineFourmi(w, Coord(i,j), Color::Black);
				}
			} else if (P.estSurUnePiste()) {
				dessinePheroSucre(w, Coord(i,j), P.pheroSucre(), dicoCouleur(5, true));
			} else if (P.contientObstacle()) {
				if (jour) dessineObstacle(w, Coord(i,j), obsjour);
				else dessineObstacle(w, Coord(i,j), obsnuit);
			}
		}
	}
}
