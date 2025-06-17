#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "GameOfLife.h"

using namespace std;

GameOfLife::GameOfLife(int rows, int cols) : rows(rows), cols(cols),generations(0) {
    grid = new char*[rows];
    nextGrid = new char*[rows];
    for (int i = 0; i < rows; ++i) {
        grid[i] = new char[cols];
        nextGrid[i] = new char[cols];
        memset(grid[i], ' ', cols * sizeof(char));
        memset(nextGrid[i], ' ', cols * sizeof(char));
    }
}   
GameOfLife::~GameOfLife() {
    for (int i = 0; i < rows; ++i) {
        delete[] grid[i];
        delete[] nextGrid[i];
    }
    delete[] grid;
    delete[] nextGrid;
}
void GameOfLife::setCellAlive(int r, int c) {
    if (r >= 0 && r < rows && c >= 0 && c < cols)
        grid[r][c] = 'O';  // Set cell to alive

}
void GameOfLife::LoadFromFile(const char* filename) {
    ifstream file(filename);
    int r ,c ;
    while (file >> r >> c) {
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
           setCellAlive(r, c);
        }
    }
    file.close();
}
int GameOfLife::countNeighbors(int row , int col){
    int count = 0;
    for(int i = -1 ; i<= 1 ;i++){
        for(int j = -1 ; j<= 1 ;j++){
            if (i == 0 && j == 0) continue; // Skip the cell itself
            int newRow = row + i;
            int newCol = col + j;
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && grid[newRow][newCol] == 'O') {
                if (grid[newRow][newCol] == 'O') {
                    count++;
                }
            }
        }
    }
    return count;
}
void GameOfLife::update(){
    for(int i = 0; i < rows ;i++){
        for(int j = 0; j < cols ;j++){
            int neighbors = countNeighbors(i, j);
            if (grid[i][j] == 'O') {
                nextGrid[i][j] = (neighbors == 2 || neighbors == 3) ? 'O' : ' ';
            } else {
                nextGrid[i][j] = (neighbors == 3) ? 'O' : ' ';
            }
        }
    }
    char **temp = grid;
    grid = nextGrid;
    nextGrid = temp;
    generations++; // Increment the generation count
}
void GameOfLife::display() const {
    cout << "Generation: " << generations << endl;
    int aliveCount = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
           if(grid[i][j] == 'O') {
                cout << "\033[32mO\033[0m ";
                aliveCount++;
            } else {
                cout << ". ";
            }
            
            
        }
        cout << endl;
    }
    cout << string(50, '-') << endl; // Separator

    //Display alive cells count

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
/*void GameOfLife::moveCells(){
    char **newGrid = new char*[rows];
    for (int i = 0; i < rows; ++i) {
        newGrid[i] = new char[cols];
        memset(newGrid[i], ' ', cols * sizeof(char));
        
    }
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            if (grid[i][j] == 'O') {
                int newRow = i + (rand() % 3 - 1); // Random movement: -1, 0, or 1
                int newCol = j + (rand() % 3 - 1);

                // Handle collisions with the borders of the 100x100 square
                if (newRow < 0 || newRow >= rows || newRow >= 100) {
                    newRow = i - (rand() % 3 - 1); // Reverse direction
                }
                if (newCol < 0 || newCol >= cols || newCol >= 100) {
                    newCol = j - (rand() % 3 - 1); // Reverse direction
                }

                // Move the cell to the new position
                newGrid[newRow][newCol] = 'O';
            }
        }

    }
    // Replace the old grid with the new grid
    for (int i = 0; i < rows; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
    grid = newGrid;
}*/
