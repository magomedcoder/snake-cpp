#include "Game.h"

void Game::draw() {
    system("clear");
    if (!m_is_alive) {
        std::cout << "Игра закончена!" << std::endl;
        return;
    }
    if (m_did_quit) {
        std::cout << "Выход" << std::endl;
        return;
    }
    std::cout << "W - вверх,  A - влево, D - вправо, S - вниз, Z - Выйти" << std::endl;
    int i, j;
    for (i = 0; i < getBoard().getWidth() + 2; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;
    for (i = 0; i < getBoard().getHeight(); i++) {
        std::cout << "|";
        for (j = 0; j < getBoard().getWidth(); j++) {
            std::cout << (m_snake.has(j, i) ? SNAKE_BODY_SYM : (hasFood(j, i) ? FOOD_SYM : " "));
        }
        std::cout << "|" << std::endl;
    }
    for (i = 0; i < getBoard().getWidth() + 2; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;
}

void Game::play() {
    char playing = 1;
    srand((unsigned int)time(0));
    Board board(20, 10);
    int start_x = board.getWidth() / 2;
    int start_y = board.getHeight() / 2;
    Snake snake(board, start_x, start_y);
    snake.setDirection(DOWN);
    Game game(board, snake);
    while (game.isLive()) {
        game.getInput();
        game.nextStep();
        game.draw();
        playing++;
        sleepcp(100);
    }
}

int main() {
    Game::play();
}