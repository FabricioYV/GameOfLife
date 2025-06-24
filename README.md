📌 Overview
This project implements Conway's Game of Life, a cellular automaton that simulates the evolution of a population of cells following simple rules. The simulation runs on a 100x100 grid with boundary reflection behavior and random initialization.

✨ Features
Bounded 100x100 grid with reflection at boundaries

Random initialization of cells (~20% alive at start)

Color display (green for alive cells)

Real-time statistics including:

Generation count

Number of alive cells

Percentage of alive cells

Adjustable speed of simulation

🛠️ Requirements
C++ compiler (g++ or similar)

Unix-like system (for usleep) or Windows (with modifications)

🚀 Installation & Usage
Compile the program:

bash
g++ -o life GameOfLife.cpp main.cpp
Run the simulation:

bash
./life
Controls:

The simulation runs automatically

Press Ctrl+C to exit
