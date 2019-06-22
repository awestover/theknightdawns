objects=main.o Dialogue.o Room.o utilityFunctions.o Player.o HUD.o BattleStats.o Entity.o Enemy.o TextDisplay.o Mover.o Projectile.o
main: $(objects)
	g++ -std=c++11 $(objects) -o main -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
main.o: main.cpp constants.hpp 
	g++ -std=c++11 -c main.cpp
Player.o: Player.cpp Player.hpp constants.hpp Entity.cpp Entity.hpp Mover.cpp Mover.hpp
	g++ -std=c++11 -c Player.cpp
Dialogue.o: Dialogue.cpp Dialogue.hpp constants.hpp
	g++ -std=c++11 -c Dialogue.cpp
Room.o: Room.cpp Room.hpp
	g++ -std=c++11 -c Room.cpp
utilityFunctions.o: utilityFunctions.hpp utilityFunctions.cpp
	g++ -std=c++11 -c utilityFunctions.cpp
HUD.o: HUD.hpp HUD.cpp constants.hpp
	g++ -std=c++11 -c HUD.cpp
BattleStats.o: BattleStats.hpp BattleStats.cpp constants.hpp
	g++ -std=c++11 -c BattleStats.cpp
Entity.o: Entity.hpp Entity.cpp Mover.cpp Mover.hpp
	g++ -std=c++11 -c Entity.cpp
Enemy.o: Enemy.hpp Enemy.cpp Entity.cpp Entity.hpp Mover.cpp Mover.hpp
	g++ -std=c++11 -c Enemy.cpp
TextDisplay.o: TextDisplay.hpp TextDisplay.cpp
	g++ -std=c++11 -c TextDisplay.cpp
Mover.o: Mover.hpp Mover.cpp
	g++ -std=c++11 -c Mover.cpp
Projectile.o: Projectile.hpp Projectile.cpp Mover.hpp Mover.cpp
	g++ -std=c++11 -c Projectile.cpp
clean:
	rm -f main
	rm -f *.o
