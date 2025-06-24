#include <iostream>
#include "GameOfLife.h"
#include <unistd.h> // For usleep
#include <fstream>

#
using namespace std;


int main() {
    GameOfLife game(100, 100); // 100x100 grid
    
    while (true) {
        game.display();
        game.update();
        usleep(200000); // 200ms delay (use Sleep(200) on Windows)
    }
    
    return 0;
}
