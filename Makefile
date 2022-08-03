CC=g++ 

ifeq ($(OS), WINDOWS)
CFLAGS=-Llibwindows/ -Iinclude/ -lraylib -lopengl32 -lgdi32 -lwinmm -g -Wall -fpermissive -O1 -static-libgcc -static-libstdc++
else 
ifeq ($(OS), LINUX)
CFLAGS=-Lliblinux/ -Iinclude/ -lraylib -g -Wall -fpermissive -static-libgcc -static-libstdc++
endif
endif

default: main

title.o: src/title.cpp
	$(CC) -c src/title.cpp -o title.o $(CFLAGS)

main.o: src/main.cpp
	$(CC) -c src/main.cpp -o main.o $(CFLAGS)

game.o: src/game.cpp
	$(CC) -c src/game.cpp -o game.o $(CFLAGS)

main: title.o main.o game.o
	$(CC) main.o title.o game.o -o bin/snakelock $(CFLAGS)

run:
	cd bin; ./snakelock || .\bin\snakelock.exe

clean:
	rm *.o || del -rf *.o *~
