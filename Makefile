objects=main.o Dialogue.o Room.o utilityFunctions.o Player.o HUD.o BattleStats.o Entity.o Enemy.o TextDisplay.o Mover.o Projectile.o Animated.o Dijkstra.o
main: $(objects)
	g++ -std=c++11 $(objects) -o main -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
main.o: main.cpp constants.hpp 
	g++ -std=c++11 -c main.cpp

## Animated and children 
AnimatedDeps=Animated.hpp Animated.cpp
Animated.o: $(AnimatedDeps) constants.hpp
	g++ -std=c++11 -c Animated.cpp
MoverDeps=Mover.hpp Mover.cpp $(AnimatedDeps)
Mover.o: $(MoverDeps) 
	g++ -std=c++11 -c Mover.cpp
EntityDeps=Entity.hpp Entity.cpp $(MoverDeps)
Entity.o: $(EntityDeps)
	g++ -std=c++11 -c Entity.cpp
Projectile.o: Projectile.hpp Projectile.cpp $(MoverDeps)
	g++ -std=c++11 -c Projectile.cpp
Player.o: Player.cpp Player.hpp $(EntityDeps)
	g++ -std=c++11 -c Player.cpp
Enemy.o: Enemy.hpp Enemy.cpp $(EntityDeps)	
	g++ -std=c++11 -c Enemy.cpp

## TextDisplay and children
TextDisplayDeps=TextDisplay.hpp TextDisplay.cpp constants.hpp
TextDisplay.o: $(TextDisplayDeps)
	g++ -std=c++11 -c TextDisplay.cpp
HUD.o: HUD.hpp HUD.cpp $(TextDisplayDeps) 
	g++ -std=c++11 -c HUD.cpp
BattleStats.o: BattleStats.hpp BattleStats.cpp $(TextDisplayDeps)
	g++ -std=c++11 -c BattleStats.cpp
Dialogue.o: Dialogue.cpp Dialogue.hpp $(TextDisplayDeps)
	g++ -std=c++11 -c Dialogue.cpp

## misc
Room.o: Room.cpp Room.hpp
	g++ -std=c++11 -c Room.cpp
utilityFunctions.o: utilityFunctions.hpp utilityFunctions.cpp
	g++ -std=c++11 -c utilityFunctions.cpp
Dijkstra.o: Dijkstra.hpp Dijkstra.cpp
	g++ -std=c++11 -c Dijkstra.cpp

clean:
	rm -f main
	rm -f *.o
