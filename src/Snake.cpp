#include "Snake.h"

Snake::Snake(Board &board, int x_start, int y_start) : m_board(board) {
    m_cubes.push_back(getIndexFromXY(x_start, y_start));
}

void Snake::nextStep() {
    addOneCube();
    m_cubes.pop_front();
}

void Snake::addOneCube() {
    int nextX, nextY;
    nextX = m_board.getNextX(nextX, m_direction);
    nextY = m_board.getNextY(nextY, m_direction);
    m_cubes.push_back(getIndexFromXY(nextX, nextY));
}