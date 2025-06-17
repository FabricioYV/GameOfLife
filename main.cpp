#include <iostream>
#include "GameOfLife.h"
#include <unistd.h> // For usleep
#include <fstream>

#
using namespace std;


int main(){ 
    GameOfLife game(20, 20);
    game.LoadFromFile("cells.txt"); // Load initial live cells from file
    
    for(int i = 0; i < 100; ++i) { // Run for 100 generations
        system("clear");         // o "cls" en Windows
        game.display();
        game.update();
        usleep(200000);
    }
    cout << "Simulation finished." << endl; 
    return 0;
}