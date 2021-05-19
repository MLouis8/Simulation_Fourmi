CXX=g++
CXXFLAGS=-Wall -std=c++11 -g
EXEC_FILES=projet_Main Coordstests Antstests Placestests Grillestests Conditiontests projet_Main

#all: projet_Main
all: Coordstests Antstests Placestests Grillestests Conditiontests projet_Main

# Regle generique
%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

projet_Main: ants.o coord.o grille.o place.o graphique.o main.o condition.o programmeprincipal.o colonie.o
	$(CXX) -o $@ $^ $(LDFLAGS) -lsfml-system -lsfml-window -lsfml-graphics

Coordstests: coord.o testCoord.o
	$(CXX) -o $@ $^ $(LDFLAGS)
Antstests: ants.o coord.o testAnt.o
	$(CXX) -o $@ $^ $(LDFLAGS)
Placestests: ants.o coord.o place.o testPlace.o
	$(CXX) -o $@ $^ $(LDFLAGS)
Grillestests: ants.o coord.o grille.o place.o testGrille.o colonie.o
	$(CXX) -o $@ $^ $(LDFLAGS)
Conditiontests: ants.o coord.o grille.o place.o condition.o testCondition.o
	$(CXX) -o $@ $^ $(LDFLAGS)

Maintest.o: graphique.hpp place.hpp coord.hpp ants.hpp grille.hpp condition.hpp

programmeprincipal.o: place.hpp coord.hpp ants.hpp grille.hpp condition.hpp colonie.hpp

main.o: graphique.hpp place.hpp coord.hpp ants.hpp grille.hpp condition.hpp colonie.hpp

graphique.o: graphique.hpp place.hpp coord.hpp ants.hpp grille.hpp colonie.hpp

coord.o: coord.hpp
testCoord.o: coord.hpp

ants.o: ants.hpp coord.hpp
testAnt.o: ants.hpp coord.hpp

place.o: place.hpp coord.hpp ants.hpp
testPlace.o: place.hpp coord.hpp ants.hpp

grille.o: place.hpp coord.hpp ants.hpp grille.hpp colonie.hpp
testGrille.o: place.hpp coord.hpp ants.hpp grille.hpp colonie.hpp

condition.o: place.hpp coord.hpp ants.hpp grille.hpp condition.hpp
testCondition.o: place.hpp coord.hpp ants.hpp grille.hpp condition.hpp

colonie.o: place.hpp coord.hpp ants.hpp grille.hpp




# Commands:

check1: Coordstests
	./Coordstests

check2: Antstests
	./Antstests

check3: Placestests
	./Placestests

check4: Grillestests
	./Grillestests

check5: Conditiontests
	./Conditiontests

checkAll:
	./Coordstests
	./Antstests
	./Placestests
	./Grillestests
	./Conditiontests

clean:
	rm -f *.o $(EXEC_FILES)
