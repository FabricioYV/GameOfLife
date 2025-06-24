#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "GameOfLife.h"

using namespace std;

GameOfLife::GameOfLife(int rows, int cols) : rows(min(50, rows)), cols(min(50, cols)), generations(0) {
    // Initialize with maximum 100x100 grid
    grid = new char*[this->rows];
    nextGrid = new char*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        grid[i] = new char[this->cols];
        nextGrid[i] = new char[this->cols];
        memset(grid[i], ' ', this->cols * sizeof(char));
        memset(nextGrid[i], ' ', this->cols * sizeof(char));
    }
    randomInitialize();
}

GameOfLife::~GameOfLife() {
    for (int i = 0; i < rows; ++i) {
        delete[] grid[i];
        delete[] nextGrid[i];
    }
    delete[] grid;
    delete[] nextGrid;
}

void GameOfLife::randomInitialize() {
    srand(time(0)); // Seed random number generator
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = (rand() % 5 == 0) ? 'O' : ' '; // ~20% chance of being alive
        }
    }
}

void GameOfLife::setCellAlive(int r, int c) {
    if (r >= 0 && r < rows && c >= 0 && c < cols)
        grid[r][c] = 'O';
}

int GameOfLife::wrapCoordinate(int value, int max) const {
    // Bounce behavior - reflect at boundaries
    if (value < 0) return 0;
    if (value >= max) return max - 1;
    return value;
}

int GameOfLife::countNeighbors(int row, int col) const {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            
            // Use wrapCoordinate for bounce behavior
            int newRow = wrapCoordinate(row + i, rows);
            int newCol = wrapCoordinate(col + j, cols);
            
            if (grid[newRow][newCol] == 'O') {
                count++;
            }
        }
    }
    return count;
}

void GameOfLife::update() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int neighbors = countNeighbors(i, j);
            if (grid[i][j] == 'O') {
                nextGrid[i][j] = (neighbors == 2 || neighbors == 3) ? 'O' : ' ';
            } else {
                nextGrid[i][j] = (neighbors == 3) ? 'O' : ' ';
            }
        }
    }
    
    // Swap grids
    char** temp = grid;
    grid = nextGrid;
    nextGrid = temp;
    
    generations++;
}

void GameOfLife::display() const {
    system("clear"); // Use "cls" on Windows
    cout << "Generation: " << generations << endl;
    int aliveCount = 0;
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 'O') {
                cout << "\033[32mO\033[0m "; // Green for alive cells
                aliveCount++;
            } else {
                cout << ". "; // Dot for dead cells
            }
        }
        cout << endl;
    }
    
    cout << string(100, '-') << endl;
    cout << "Alive cells: " << aliveCount << endl;
    double percentage = (static_cast<double>(aliveCount) / (rows * cols)) * 100;
    cout << "Percentage of alive cells: " << fixed << setprecision(2) << percentage << "%" << endl;
}

void GameOfLife::countAliveCells() const {
    int aliveCount = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 'O') {
                aliveCount++;
            }
        }
    }
    cout << "Alive cells: " << aliveCount << endl;
}