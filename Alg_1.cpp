#include <iostream>
#include "Header.h"
#include <random>
#include "ModSort.h"
#include "Sort.h"

using namespace std;

bool menu() {
    cout << "Choose action:\n";
    cout << "0 - generate file\n";
    cout << "1 - sort file\n";
    cout << "2 - check file sorting status\n";
    cout << "3 - transform file\n";

    int basic_choice;
    cin >> basic_choice;

    if (basic_choice == 0) {
        /*cout << "Enter type of file:\n";
        cout << "0 - text file\n";
        cout << "1 - binary file\n";*/

        int type_of_file = 1;
        //cin >> type_of_file;

        cout << "Enter file name:\n";
        string filename;
        cin >> filename;

        cout << "Enter number of elements:\n";
        int num_of_elements;
        cin >> num_of_elements;

        cout << "Enter max number (greater than 0 and less than 64bit number limit):\n";
        unsigned long long max_n;
        cin >> max_n;

        if (type_of_file == 0) {
            cout << "Warning! Text file generation is very slow\n";
            generateFile(num_of_elements, filename, max_n);
        }
        else if (type_of_file == 1) {
            generateBinFile64(num_of_elements, filename, max_n);
        }
        else return 0;
        cout << "File " << filename << " succesfully generated!\n";
    }
    else if (basic_choice == 1) {
        cout << "Enter type of sort:\n";
        cout << "0 - base (very slow)\n";
        cout << "1 - modified\n";
        cout << "2 - alternative (higher memory speed, less algorithm speed)\n";
        int type_of_sort;
        cin >> type_of_sort;

        cout << "Enter file name (file must be binary):\n";
        string filename;
        cin >> filename;

        cout << "Enter output filename\n";
        string output_name;
        cin >> output_name;

        cout << "Delete intermediate products (0/1)?\n";
        bool delete_intermediate;
        cin >> delete_intermediate;

        if (type_of_sort == 0) {
            cout << "Show progress (0/1)?\n";
            bool show_progress;
            cin >> show_progress;
            sortBin64File(filename, output_name, delete_intermediate, show_progress);
        }
        else if (type_of_sort == 1) {
            cout << "Enter max amount of RAM (in bytes):\n";
            int max_RAM_size;
            cin >> max_RAM_size;

            sortBin64FileMod(filename, output_name, max_RAM_size, delete_intermediate);
        }
        else  if (type_of_sort == 2) {
            cout << "Enter max amount of RAM (in bytes):\n";
            int max_RAM_size;
            cin >> max_RAM_size;

            sortBin64FileAlt(filename, output_name, max_RAM_size, delete_intermediate);
        }
        else return 0;

        cout << "File " << filename << " succesfully sorted!\n";
    }
    else if (basic_choice == 2) {
        cout << "Enter file name:\n";
        string filename;
        cin >> filename;

        cout << "Enter file type:\n";
        cout << "0 - text\n";
        cout << "1 - bin64\n";
        int filetype;
        cin >> filetype;

        bool is_sorted;

        if (filetype == 0) {
            is_sorted = checkFileSortingText(filename);
        }
        else if (filetype == 1) {
            is_sorted = checkFileSortingBin64(filename);
        }
        else return 0;

        if(is_sorted) cout << "File " << filename << " is sorted\n";
        else cout << "File " << filename << " is NOT sorted\n";
        
    }
    else if (basic_choice == 3) {
        cout << "For now, only allowed bin64->text transforming\n";

        cout << "Enter file name (file must be binary):\n";
        string filename;
        cin >> filename;

        cout << "Enter output filename\n";
        string output_name;
        cin >> output_name;

        convertBin64toText(filename, output_name);

        cout << "File " << filename << " succesfully converted to text!\n";
    }
    else return 0;
    cout << "\n";
    return 1;
}

int main()
{
    while (menu());

    //string filename = "boss_bin64.bin";
    //generateFile(1073741824, "boss.bin");
    //generateBinFile64(134217728, "boss.bin", 1000000000);
    //sortFile(filename);
    //cout << checkFileSorting("C.txt");

    //sortBin64FileMod("boss_bin64.bin", 100000000);

    
    
    //mergeFilesBin64("S1.bin", "S2.bin", "S12.bin");

   // sortBin64FileMod(filename, 1500000000);
    //cout << checkFileSortingBin64("S1-1.bin");
    //convertBin64toText("S1-1.bin", "S1-1_text.txt");

    //convertBin64toText("S64-1.bin", "S64-1_text.txt");

    /*for (size_t i = 1; i <= 8; i++)
    {
        convertBin64toText("S" + to_string(i) + ".bin", "S" + to_string(i) + "_text.txt");
    }*/
}
