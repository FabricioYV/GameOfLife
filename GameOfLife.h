#ifndef __GAME_OF_LIFE_H__
#define __GAME_OF_LIFE_H__


class GameOfLife {
public:
    GameOfLife(int rows = 100, int cols = 100); // Default to 100x100
    ~GameOfLife();
    
    void randomInitialize();
    void update();
    void display() const;
    void countAliveCells() const;

private:
    int rows;
    int cols;
    int generations;
    char** grid;
    char** nextGrid;
    
    void setCellAlive(int r, int c);
    int countNeighbors(int row, int col) const;
    int wrapCoordinate(int value, int max) const;
};

#endif