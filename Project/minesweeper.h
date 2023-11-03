#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

const int SIZE = 8;

void initializeBoard(const string& boardFileName, char**& board, char**& displayBoard);
bool touch(int row, int col, char**& displayBoard, char**& board);
void minesweeper(const string& commandFileName, const string& outputFileName);