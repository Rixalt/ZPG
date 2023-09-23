#include <iostream>
#include <vector>
#include <unistd.h>

const int ROWS = 20;
const int COLS = 40;
const char ALIVE_CELL = '*';
const char DEAD_CELL = ' ';

std::vector<std::vector<bool>> currentGeneration(ROWS, std::vector<bool>(COLS, false));
std::vector<std::vector<bool>> nextGeneration(ROWS, std::vector<bool>(COLS, false));

void initializeGame() {

    int middleRow = ROWS / 2;
    for (int i = 0; i < COLS; ++i) {
        currentGeneration[middleRow][i] = true;
    }
}

void printGeneration() {

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (currentGeneration[i][j]) {
                std::cout << ALIVE_CELL;
            } else {
                std::cout << DEAD_CELL;
            }
        }
        std::cout << std::endl;
    }
}

bool isValid(int row, int col) {

    return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

int countNeighbors(int row, int col) {

    int neighbors = 0;
    int dx[] = {1, 1, 1, 0, 0, -1, -1, -1};
    int dy[] = {1, 0, -1, 1, -1, 1, 0, -1};

    for (int i = 0; i < 8; ++i) {
        int newRow = row + dx[i];
        int newCol = col + dy[i];
        if (isValid(newRow, newCol) && currentGeneration[newRow][newCol]) {
            neighbors++;
        }
    }

    return neighbors;
}

void evolveGeneration() {

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int neighbors = countNeighbors(i, j);

            if (currentGeneration[i][j]) {

                nextGeneration[i][j] = (neighbors == 2 || neighbors == 3);
            } else {

                nextGeneration[i][j] = (neighbors == 3);
            }
        }
    }

    // Оновлюємо поточне покоління
    currentGeneration = nextGeneration;
}

int main() {
    initializeGame();

    while (true) {
        system("clear");
        printGeneration();
        evolveGeneration();
        usleep(100000);
    }

    return 0;
}
