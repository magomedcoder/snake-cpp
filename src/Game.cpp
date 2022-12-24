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
            std::cout << (m_snake.has(j, i) ? SNAKE_BODY_SYM : (hasFood(j, i) ? FOOD_SYM : EMPTY_SYM));
        }
        std::cout << "|" << std::endl;
    }
    for (i = 0; i < getBoard().getWidth() + 2; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;
}

bool Game::hasFood(int x, int y) {
    return m_food_index == (y * m_board.getWidth() + x);
}

bool Game::hasFood(int index) {
    return m_food_index == index;
}

void Game::nextStep() {
    m_snake.nextStep();
    if (m_snake.isDead()) {
        m_is_alive = false;
    } else if (hasFood(m_snake.getHeadIndex())) {
        m_snake.addOneCube();
        createFood();
    }
}

void sleepcp(int mil) {
    clock_t end_time;
    end_time = clock() + mil * CLOCKS_PER_SEC / 1000;
    while (clock() < end_time){
    }
}

Game::Game(Board &board, Snake &snake) : m_board(board), m_snake(snake), m_is_alive(true), m_did_quit(false) {
    createFood();
}

void Game::createFood() {
    m_blankIndexes.clear();
    int i = 0;
    int lim = m_board.getHeight() * m_board.getWidth();
    while (i < lim) {
        m_blankIndexes.push_back(i++);
    }
    std::list<int>::iterator it = m_blankIndexes.begin();
    std::advance(it, rand() % m_blankIndexes.size());
    m_food_index = *it;
}

void Game::getInput() {
    keyboard keyb;
    unsigned int in_wait = 20, waited = 0;
    DIRECTION dir = -1;
    while (waited < 50) {
        if (keyb.kbhit()) {
            switch ((char)keyb.getch()) {
                case 'w':
                case 'W':
                    if (m_snake.getDirection() != DOWN)
                        dir = UP;
                    break;
                case 'a':
                case 'A':
                    if (m_snake.getDirection() != RIGHT)
                        dir = LEFT;
                    break;
                case 's':
                case 'S':
                    if (m_snake.getDirection() != UP)
                        dir = DOWN;
                    break;
                case 'd':
                case 'D':
                    if (m_snake.getDirection() != LEFT)
                        dir = RIGHT;
                    break;
                case 'z':
                case 'Z':
                    m_did_quit = true;
                    break;
                default:
                    break;
            }
            if (m_did_quit)
                break;
            if (dir != -1) {
                m_snake.setDirection(dir);
                break;
            }
        }
        waited += in_wait;
        sleepcp(in_wait);
    }
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