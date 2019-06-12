objects=main.o Dialogue.o Room.o utilityFunctions.o Player.o
main: $(objects)
	g++ -std=c++11 $(objects) -o main -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
	./main
main.o: main.cpp constants.hpp 
	g++ -std=c++11 -c main.cpp
Player.o: Player.cpp Player.hpp constants.hpp
	g++ -std=c++11 -c Player.cpp
Dialogue.o: Dialogue.cpp Dialogue.hpp constants.hpp
	g++ -std=c++11 -c Dialogue.cpp
Room.o: Room.cpp Room.hpp
	g++ -std=c++11 -c Room.cpp
utilityFunctions.o: utilityFunctions.hpp utilityFunctions.cpp
	g++ -std=c++11 -c utilityFunctions.cpp
clean:
	rm -f main
	rm -f *.o
