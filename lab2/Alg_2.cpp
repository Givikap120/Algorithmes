#include <iostream>
#include "Labyrinth.h"

using namespace std;

const float WALL_CHANCE = 0.5;
const float DEADEND_CHANCE = 0.2;

bool menu() {
    cout << "Enter type of input (0 - file, 1 - generation)\n";
    bool choice;
    cin >> choice;

    Labyrinth labyrinth;

    if (choice)
    {
        cout << "Enter size (X Y)\n";
        int sizeX, sizeY;
        cin >> sizeX >> sizeY;
        labyrinth.createTable(sizeX, sizeY);

        cout << "Enter seed (0 for random)\n";
        time_t seed;
        cin >> seed;
        if (seed == 0) seed = time(0);
        srand(seed);
        labyrinth.generate(WALL_CHANCE, DEADEND_CHANCE);
        labyrinth.print();

        cout << "\nExport to file(0/1)?\n";
        cin >> choice;
        if (choice)
        {
            cout << "Enter file name\n";
            std::string filename;
            cin >> filename;
            labyrinth.exportToFile_Text(filename);
        }
    }
    else {
        cout << "Enter file name\n";
        std::string filename;
        labyrinth.importFromFile_Text(filename);
        labyrinth.print();
    }
    cout << "Enter start node \"X Y\"\n";
    int startX, startY;
    cin >> startX >> startY;
    cout << "Enter end node \"X Y\"\n";
    int endX, endY;
    cin >> endX >> endY;

    cout << "What algorithm to use? (-1 - IDS, 1 - Astar, 0 - both)\n";
    int algorithm;
    cin >> algorithm;
    int iterations, visitednodes;
    if (algorithm != -1)
    {
        cout << "\nA star distance - " << Astar_debug(startX, startY, endX, endY, labyrinth, iterations, visitednodes) << endl;
        cout << "Iterations - " << iterations << endl;
        cout << "Deadends - " << labyrinth.countDeadends() << endl;
        cout << "Visited nodes - " << visitednodes << endl;
        cout << "Iterations - " << labyrinth.countAllNodes() << endl;
    }
    cout << "\n";
    if (algorithm != 1)
    {
        int distance = IDS_debug(startX, startY, endX, endY, labyrinth, iterations, visitednodes);
        cout << "\nIDS distance - " << distance << endl;
        cout << "Iterations - " << iterations << endl;
        cout << "Deadends - " << labyrinth.countDeadends() << endl;
        cout << "Visited nodes - " << visitednodes << endl;
        cout << "Iterations - " << labyrinth.countAllNodes() << endl;
    }

    return 1;
}

int main()
{
    //while (menu());
    for (time_t i = 2; i < 3; i++)
    {
        srand(i);
        Labyrinth labyrinth(10,10);
        labyrinth.generate(WALL_CHANCE, DEADEND_CHANCE);
        labyrinth.print();
        cout << endl;
        int iterations, visitednodes;
        int distance = IDS_debug(0, 0, 9, 9, labyrinth, iterations, visitednodes);
        cout << "\nDistance - " << distance << endl;
        cout << "Iterations - " << iterations << endl;
        cout << "Deadends - " << labyrinth.countDeadends() << endl;
        cout << "Visited nodes - " << visitednodes << endl;
        cout << "Iterations - " << labyrinth.countAllNodes() << endl;
    }
}