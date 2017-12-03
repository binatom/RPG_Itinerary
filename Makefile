all: compile doc

compile: RPG_Itinerary

RPG_Itinerary: main.o Equipments.o CMenu.o Weapons.o Spells.o sqlite3.o
	g++ -std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb main.o Equipments.o CMenu.o Weapons.o Spells.o sqlite3.o -o RPG_Itinerary -lpthread -ldl


Equipments.o: ./src/Equipments.cpp ./src/Equipments.h
	g++ -std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb ./src/Equipments.cpp -c -o Equipments.o

main.o: ./src/main.cpp ./src/Equipments.h ./src/Weapons.h ./src/sqlite/sqlite3.h
	g++ -std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb ./src/main.cpp -c -o main.o

CMenu.o: ./src/CMenu.cpp ./src/CMenu.h ./src/Equipments.h ./src/Weapons.h ./src/Spells.h
	g++ -std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb ./src/CMenu.cpp -c -o CMenu.o

Weapons.o: ./src/Weapons.cpp ./src/Weapons.h ./src/Equipments.h
	g++ -std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb ./src/Weapons.cpp -c -o Weapons.o

Spells.o: ./src/Spells.cpp ./src/Spells.h ./src/Equipments.h
	g++ -std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb ./src/Spells.cpp -c -o Spells.o

sqlite3.o: ./src/sqlite/sqlite3.c ./src/sqlite/sqlite3.h
	gcc ./src/sqlite/sqlite3.c -c -o sqlite3.o

run: compile
	./RPG_Itinerary

doc:
	doxygen Doxyfile

clean:
	rm -rf RPG_Itinerary ./*o doc/ 2>/dev/null




