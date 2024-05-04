all: ecosystem.bin

sample: ecosystem.bin
	./ecosystem.bin ../input/map.txt ../input/species.txt

ecosystem.bin: main.o Organism.o Plant.o Animal.o Helper.o Ecosystem.o
	g++ -o ecosystem.bin main.o Organism.o Plant.o Animal.o Helper.o Ecosystem.o

main.o: main.cpp Organism.o Plant.o Animal.o Helper.o Ecosystem.o
	g++ -c main.cpp

Plant.o: Plant.h Plant.cpp Organism.o
	g++ -c Plant.h Plant.cpp

Animal.o: Animal.h Animal.cpp
	g++ -c Animal.h Animal.cpp

Organism.o: Organism.h Organism.cpp Helper.o
	g++ -c Organism.h Organism.cpp

Helper.o: Helper.h Helper.cpp
	g++ -c Helper.h Helper.cpp

Ecosystem.o: Ecosystem.h Ecosystem.cpp
	g++ -c Ecosystem.h Ecosystem.cpp

clean:
	rm -rf *.bin *.o *.exe *.gch

clean2:
	del -rf *.bin *.o *.exe *.gch