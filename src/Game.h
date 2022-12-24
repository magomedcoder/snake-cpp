#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Snake.h"
#include "kbhit.h"
#include "Config.h"
#include <vector>

class Game {
    private:
        Board m_board;
        Snake m_snake;
        std::list<int> m_blankIndexes;
        int m_food_index;
        Board &getBoard() {
            return m_board;
        }
        bool m_is_alive;
        bool m_did_quit;
        void createFood();
        bool hasFood(int x, int y);
        bool hasFood(int index);

    public:
        Game(Board &board, Snake &snake);
        void draw();
        void nextStep();
        bool isLive() {
            return (m_is_alive && !m_did_quit);
        }
        void getInput();
        static void play();
};

#endif