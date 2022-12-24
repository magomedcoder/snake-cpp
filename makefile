snake: src/Game.cpp src/Game.h src/Board.cpp src/Board.h src/Snake.cpp src/Snake.h src/Config.h
	g++ -Wall -g src/Game.cpp src/Board.cpp src/Snake.cpp src/kbhit.cpp -o snake

clean:
	rm -f snake