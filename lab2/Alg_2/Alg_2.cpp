#include <iostream>
#include "Labyrinth.h"

#include <fstream>

using namespace std;

const float WALL_CHANCE = 0.5;
const float DEADEND_CHANCE = 0;


bool isUint(const std::string& str)
{
    if (str[0] == '0' and str.length() > 1) return false;
    for (auto i = str.begin(); i != str.end(); ++i)
    {
        if (!std::isdigit(*i)) return false;
    }
    return true;
}

bool isInt(const std::string& str)
{
    if (str[0] != '-' and !std::isdigit(str[0])) return false;
    if (str.length() > 1 and str[0] == '0') return false;

    for (auto i = str.begin() + 1; i != str.end(); ++i)
    {
        if (!std::isdigit(*i)) return false;
    }
    return true;
}

inline bool isFileExists(const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

bool menu() {
    std::string choiceStr;
    while (1) {
        cout << "Enter type of input (0 - file, 1 - generation)\n";
        cin >> choiceStr;
        if (choiceStr == "0" or choiceStr == "1") break;
        else cout << "Wrong input\n";
    }
    bool choice = stoi(choiceStr);
    

    Labyrinth labyrinth;
    
    if (choice)
    {
        std::string sizeXstr, sizeYstr;
        while (1)
        {
            cout << "Enter size (X Y)\n";
            cin >> sizeXstr >> sizeYstr;
            if (isNatural(sizeXstr) and isNatural(sizeYstr)) break;
            else cout << "Wrong input\n";
        }
        
        int sizeX = stoi(sizeXstr), sizeY = stoi(sizeYstr);
        
        labyrinth.createTable(sizeX, sizeY);


        std::string seedStr;
        while (1)
        {
            cout << "Enter seed (0 for random)\n";
            cin >> seedStr;
            if (isInt(seedStr)) break;
            else cout << "Wrong input\n";
        }
        
        time_t seed = stoi(seedStr);
        
        if (seed == 0) seed = time(0);
        srand(seed);
        labyrinth.generate(WALL_CHANCE, DEADEND_CHANCE);
        labyrinth.print();

        while (1)
        {
            cout << "\nExport to file(0/1)?\n";
            cin >> choiceStr;
            if (choiceStr == "0" or choiceStr == "1") break;
            else cout << "Wrong input\n";
        }

        choice = stoi(choiceStr);
        
        if (choice)
        {
            cout << "Enter file name\n";
            std::string filename;
            cin >> filename;
            labyrinth.exportToFile_Text(filename);
        }
    }
    else {
        std::string filename;
        while (1)
        {
            cout << "Enter file name\n";
            cin >> filename;
            if (isFileExists(filename)) break;
            else cout << "File doesn't exist\n";
        }
        
        labyrinth.importFromFile_Text(filename);
        if (labyrinth.countAllNodes() == 0) { cout << "Wrong file format\n"; return -1; }
        labyrinth.print();
    }
    std::string Xstr, Ystr;
    int startX, startY;
    while (1)
    {
        cout << "Enter start node \"X Y\"\n";
        cin >> Xstr >> Ystr;
        if (isUint(Xstr) and isUint(Ystr))
        {
            startX = stoi(Xstr); 
            startY = stoi(Ystr);
            if (startX < labyrinth.getSizeX() and startY < labyrinth.getSizeY()) break;
            else cout << "Wrong input\n";
        }
        else cout << "Wrong input\n";
    }
    
    int endX, endY;
    
    while (1)
    {
        cout << "Enter end node \"X Y\"\n";
        cin >> Xstr >> Ystr;
        if (isUint(Xstr) and isUint(Ystr))
        {
            endX = stoi(Xstr);
            endY = stoi(Ystr);
            if (endX < labyrinth.getSizeX() and endY < labyrinth.getSizeY()) break;
            else cout << "Wrong input\n";
        }
        else cout << "Wrong input\n";
    }
    

    std::string algorithmStr;
    while (1)
    {
        cout << "What algorithm to use? (-1 - IDS, 1 - Astar, 0 - both)\n";
        cin >> algorithmStr;
        if (algorithmStr == "0" or algorithmStr == "1" or algorithmStr == "-1") break;
        else cout << "Wrong input\n";
    }
    
    int algorithm = stoi(algorithmStr);
    
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