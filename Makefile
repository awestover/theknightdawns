main:
	g++ -c main.cpp
	g++ main.o -o main.out -lsfml-graphics -lsfml-window -lsfml-system
	./main.out
	rm main.out
	rm main.o

