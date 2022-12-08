#include <iostream>
#include "Labyrinth.h"

using namespace std;

const float WALL_CHANCE = 0.5;
const float DEADEND_CHANCE = 0;

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
        cin >> filename;
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
        cout << "\n";
        int distance = Astar_debug(startX, startY, endX, endY, labyrinth, iterations, visitednodes);
        cout << "A star distance - " << distance << endl;
        cout << "Iterations - " << iterations << endl;
        cout << "Deadends - " << labyrinth.countDeadends() << endl;
        cout << "Visited nodes - " << visitednodes << endl;
        cout << "Nodes - " << labyrinth.countAllNodes() << endl;
    }
    if (algorithm != 1)
    {
        cout << "\n";
        int distance = IDS_debug(startX, startY, endX, endY, labyrinth, iterations, visitednodes);
        cout << "IDS distance - " << distance << endl;
        cout << "Iterations - " << iterations << endl;
        cout << "Deadends - " << labyrinth.countDeadends() << endl;
        cout << "Visited nodes - " << visitednodes << endl;
        cout << "Nodes - " << labyrinth.countAllNodes() << endl;
    }
    cout << endl;
    return 1;
}

int main()
{
    while (menu());
}