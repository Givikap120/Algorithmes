#include "pch.h"
#include "CppUnitTest.h"
#include <string>

#include "../Alg_2/Labyrinth.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Labyrinth>(const Labyrinth& t) { return L"Labyrinth"; }

namespace Alg2tests
{
    
	TEST_CLASS(Alg2tests)
	{
	public:
		
		TEST_METHOD(short_path_labyrinth_test_IDS)
		{
            //start variables
            const time_t seed = 1;
            const int sizeX = 10, sizeY = 10;
            const int startX = 0, startY = 0;
            const int endX = 9, endY = 9;
            const float wallChance = 0.5, deadendChance = 0;

            //testing algorithm
            srand(seed);
            Labyrinth labyrinth(sizeX, sizeY);
            labyrinth.generate(wallChance, deadendChance);

            int IDS_distance = IDS(startX, startY, endX, endY, labyrinth);

            //checking corectness
            const int answer = 18;

            Assert::AreEqual(IDS_distance, answer);
		}

        TEST_METHOD(short_path_labyrinth_test_Astar)
        {
            //start variables
            const time_t seed = 1;
            const int sizeX = 10, sizeY = 10;
            const int startX = 0, startY = 0;
            const int endX = 9, endY = 9;
            const float wallChance = 0.5, deadendChance = 0;

            //testing algorithm
            srand(seed);
            Labyrinth labyrinth(sizeX, sizeY);
            labyrinth.generate(wallChance, deadendChance);

            int Astar_distance = Astar(startX, startY, endX, endY, labyrinth);

            //checking corectness
            const int answer = 18;

            Assert::AreEqual(Astar_distance, answer);
        }

        TEST_METHOD(long_path_labyrinth_test_IDS)
        {
            //start variables
            const time_t seed = 4;
            const int sizeX = 10, sizeY = 10;
            const int startX = 0, startY = 0;
            const int endX = 9, endY = 9;
            const float wallChance = 0.5, deadendChance = 0;

            //testing algorithm
            srand(seed);
            Labyrinth labyrinth(sizeX, sizeY);
            labyrinth.generate(wallChance, deadendChance);

            int IDS_distance = IDS(startX, startY, endX, endY, labyrinth);

            //checking corectness
            const int answer = 22;

            Assert::AreEqual(IDS_distance, answer);
        }

        TEST_METHOD(long_path_labyrinth_test_Astar)
        {
            //start variables
            const time_t seed = 4;
            const int sizeX = 10, sizeY = 10;
            const int startX = 0, startY = 0;
            const int endX = 9, endY = 9;
            const float wallChance = 0.5, deadendChance = 0;

            //testing algorithm
            srand(seed);
            Labyrinth labyrinth(sizeX, sizeY);
            labyrinth.generate(wallChance, deadendChance);

            int Astar_distance = Astar(startX, startY, endX, endY, labyrinth);

            //checking corectness
            const int answer = 22;

            Assert::AreEqual(Astar_distance, answer);
        }

        TEST_METHOD(custom_start_end_position_test_IDS)
        {
            //start variables
            const time_t seed = 12;
            const int sizeX = 10, sizeY = 10;
            const int startX = 8, startY = 5;
            const int endX = 3, endY = 4;
            const float wallChance = 0.5, deadendChance = 0;

            //testing algorithm
            srand(seed);
            Labyrinth labyrinth(sizeX, sizeY);
            labyrinth.generate(wallChance, deadendChance);

            int IDS_distance = IDS(startX, startY, endX, endY, labyrinth);

            //checking corectness
            const int answer = 14;

            Assert::AreEqual(IDS_distance, answer);
        }
        TEST_METHOD(custom_start_end_position_test_Astar)
        {
            //start variables
            const time_t seed = 12;
            const int sizeX = 10, sizeY = 10;
            const int startX = 8, startY = 5;
            const int endX = 3, endY = 4;
            const float wallChance = 0.5, deadendChance = 0;

            //testing algorithm
            srand(seed);
            Labyrinth labyrinth(sizeX, sizeY);
            labyrinth.generate(wallChance, deadendChance);

            int Astar_distance = Astar(startX, startY, endX, endY, labyrinth);

            //checking corectness
            const int answer = 14;

            Assert::AreEqual(Astar_distance, answer);
        }

        TEST_METHOD(insanely_large_labyrinth_test_Astar)
        {
            //start variables
            const time_t seed = 1;
            const int sizeX = 50, sizeY = 50;
            const int startX = 0, startY = 0;
            const int endX = 49, endY = 49;
            const float wallChance = 0.5, deadendChance = 0;

            //testing algorithm
            srand(seed);
            Labyrinth labyrinth(sizeX, sizeY);
            labyrinth.generate(wallChance, deadendChance);

            int Astar_distance = Astar(startX, startY, endX, endY, labyrinth);

            //checking corectness
            const int answer = 100;

            Assert::AreEqual(Astar_distance, answer);
        }

        TEST_METHOD(vertical_labyrinth_test_IDS)
        {
            //start variables
            const time_t seed = 1;
            const int sizeX = 1, sizeY = 10;
            const int startX = 0, startY = 0;
            const int endX = 0, endY = 9;
            const float wallChance = 0.5, deadendChance = 0;

            //testing algorithm
            srand(seed);
            Labyrinth labyrinth(sizeX, sizeY);
            labyrinth.generate(wallChance, deadendChance);

            int IDS_distance = IDS(startX, startY, endX, endY, labyrinth);

            //checking corectness
            const int answer = 9;

            Assert::AreEqual(IDS_distance, answer);
        }

        TEST_METHOD(vertical_labyrinth_test_Astar)
        {
            //start variables
            const time_t seed = 1;
            const int sizeX = 1, sizeY = 10;
            const int startX = 0, startY = 0;
            const int endX = 0, endY = 9;
            const float wallChance = 0.5, deadendChance = 0;

            //testing algorithm
            srand(seed);
            Labyrinth labyrinth(sizeX, sizeY);
            labyrinth.generate(wallChance, deadendChance);

            int Astar_distance = Astar(startX, startY, endX, endY, labyrinth);

            //checking corectness
            const int answer = 9;

            Assert::AreEqual(Astar_distance, answer);
        }
        TEST_METHOD(horizontal_labyrinth_test_IDS)
        {
            //start variables
            const time_t seed = 1;
            const int sizeX = 10, sizeY = 1;
            const int startX = 0, startY = 0;
            const int endX = 9, endY = 0;
            const float wallChance = 0.5, deadendChance = 0;

            //testing algorithm
            srand(seed);
            Labyrinth labyrinth(sizeX, sizeY);
            labyrinth.generate(wallChance, deadendChance);

            int IDS_distance = IDS(startX, startY, endX, endY, labyrinth);

            //checking corectness
            const int answer = 9;

            Assert::AreEqual(IDS_distance, answer);
        }

        TEST_METHOD(horizontal_labyrinth_test_Astar)
        {
            //start variables
            const time_t seed = 1;
            const int sizeX = 10, sizeY = 1;
            const int startX = 0, startY = 0;
            const int endX = 9, endY = 0;
            const float wallChance = 0.5, deadendChance = 0;

            //testing algorithm
            srand(seed);
            Labyrinth labyrinth(sizeX, sizeY);
            labyrinth.generate(wallChance, deadendChance);

            int Astar_distance = Astar(startX, startY, endX, endY, labyrinth);

            //checking corectness
            const int answer = 9;

            Assert::AreEqual(Astar_distance, answer);
        }

        TEST_METHOD(one_cell_labyrinth_test_IDS)
        {
            //start variables
            const time_t seed = 1;
            const int sizeX = 1, sizeY = 1;
            const int startX = 0, startY = 0;
            const int endX = 0, endY = 0;
            const float wallChance = 0.5, deadendChance = 0;

            //testing algorithm
            srand(seed);
            Labyrinth labyrinth(sizeX, sizeY);
            labyrinth.generate(wallChance, deadendChance);

            int IDS_distance = IDS(startX, startY, endX, endY, labyrinth);

            //checking corectness
            const int answer = 0;

            Assert::AreEqual(IDS_distance, answer);
        }

        TEST_METHOD(one_cell_labyrinth_test_Astar)
        {
            //start variables
            const time_t seed = 1;
            const int sizeX = 1, sizeY = 1;
            const int startX = 0, startY = 0;
            const int endX = 0, endY = 0;
            const float wallChance = 0.5, deadendChance = 0;

            //testing algorithm
            srand(seed);
            Labyrinth labyrinth(sizeX, sizeY);
            labyrinth.generate(wallChance, deadendChance);

            int Astar_distance = Astar(startX, startY, endX, endY, labyrinth);

            //checking corectness
            const int answer = 0;

            Assert::AreEqual(Astar_distance, answer);
        }

        TEST_METHOD(file_import_test)
        {
            //start variables
            const time_t seed = 1;
            const int sizeX = 10, sizeY = 10;
            const int startX = 0, startY = 0;
            const int endX = 9, endY = 9;
            const float wallChance = 0.5, deadendChance = 0;

            //testing algorithm
            srand(seed);
            Labyrinth labyrinth(sizeX, sizeY);
            labyrinth.generate(wallChance, deadendChance);

            labyrinth.exportToFile_Text("test.txt");
            Labyrinth labyrinthFromFile;

            labyrinthFromFile.importFromFile_Text("test.txt");

            //checking corectness

            Assert::AreEqual(labyrinth, labyrinthFromFile);
        }
        
	};
}
