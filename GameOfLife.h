#ifndef __GAME_OF_LIFE_H__
#define __GAME_OF_LIFE_H__


struct Cord {
    int x;
    int y;

};
class GameOfLife
{
private:
    int rows,cols;
    char **grid;
    char **nextGrid;
    int generations ; //Track Current generation
    int countNeighbors(int row, int col);

public:
    GameOfLife(int rows, int cols);
    ~GameOfLife();

    void setCellAlive(int row, int col);
    void LoadFromFile(const char* filename);
    void countAliveCells() const;
    void update();
    void display() const;
    void moveCells();
};



#endif // __GAME_OF_LIFE_H__
