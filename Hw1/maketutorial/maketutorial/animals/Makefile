dog_program : dog.o main.o
		g++ dog.o main.o -o dog_program

dog.o :
		g++ -c dog.cpp

main.o : main.cpp
		g++ -c main.cpp

clean :
		rm dog_program *.o