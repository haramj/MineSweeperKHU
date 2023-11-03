#include "minesweeper.h"

void initializeBoard(const string& boardFileName, char** &board, char** &displayBoard) {
	std::ifstream file(boardFileName);
	std::string line;
	int i = 0;
	while (std::getline(file, line)) {
		for (int j = 0; j < line.length(); j++) {
			char c = line[j];
			board[i][j] = c;
			if (c == '*') {
				displayBoard[i][j] = '@';
			}
			else {
				displayBoard[i][j] = '.';
			}
		}
		++i;
	}
	file.close();
}

bool touch(int row, int col, char**& board, char** &displayBoard) {
	if (board[row][col] == '*') {
		displayBoard[row][col] = '*';
		return true;
	}
	else {
		int count = 0;
		for (int x = row - 1; x <= row + 1; x++) {
			for (int y = col - 1; y <= col + 1; y++) {
				if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && (x != row || y != col) && board[x][y] == '*') ++count;
			}
		}
		displayBoard[row][col] = (char)('0' + count);
		return false;
	}
}

void minesweeper(const string& commandFileName, const string& outputFileName) {
	std::ifstream file(commandFileName);
	std::ofstream outFile(outputFileName);
	
	char** board = new char* [SIZE];
	char** displayBoard = new char* [SIZE];
	for (int i = 0; i < SIZE; i++) {
		board[i] = new char[SIZE];
		displayBoard[i] = new char[SIZE];
		for (int j = 0; j < SIZE; j++) {
			board[i][j] = ' ';
			displayBoard[i][j] = ' ';
		}
	}

	std::string line;
	int touchCount = 0;
	while (std::getline(file, line)) {
		if (line.substr(0, 4) == "load") {
			const std::string boardFileName = line.substr(5);
			outFile << "Command: " << "load " << boardFileName << '\n';
			initializeBoard(boardFileName,board,displayBoard);
		}
		else if (line.substr(0, 5) == "touch") {
			++touchCount;
			outFile << "Command: " << "touch " << line[6] << ' ' << line[8] << '\n';
			if (touch((int)(line[6]-'0') - 1, (int)(line[8]-'0') - 1, displayBoard, board)) {
				break;
			}
		}
		else if (line.substr(0, 7) == "display") {
			outFile << "Command: " << "display" << '\n';
			for (int i = 0; i < SIZE; ++i) {
				for (int j = 0; j < SIZE; ++j) {
					if (displayBoard[i][j] == '@') {
						outFile << '.';
					}
					else outFile << displayBoard[i][j];
				}
				outFile << '\n';
			}
			outFile << '\n';
		}
	}
	
	outFile << "Game Over" << '\n';
	outFile << "~~~~~~~~~" << '\n';
	outFile << "Final Board" << '\n';
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			outFile << displayBoard[i][j];
 		}
		outFile << '\n';
	}
	outFile << '\n' << "Spaces touched: " << touchCount << "\n";
	file.close();
	for (int i = 0; i < SIZE; i++) {
		delete[] board[i];
		delete[] displayBoard[i];
	}
	delete[] board;
	delete[] displayBoard;
}

int main() {
	minesweeper("./test1commands.txt", "test1_output_mine.txt");
	minesweeper("./test2commands.txt", "test2_output_mine.txt");
	minesweeper("./test3commands.txt", "test3_output_mine.txt");
	minesweeper("./test4commands.txt", "test4_output_mine.txt");
	minesweeper("./test5commands.txt", "test5_output_mine.txt");
	minesweeper("./test6commands.txt", "test6_output_mine.txt");
	minesweeper("./test7commands.txt", "test7_output_mine.txt");
	minesweeper("./test8commands.txt", "test8_output_mine.txt");
	minesweeper("./test9commands.txt", "test9_output_mine.txt");
	minesweeper("./test10commands.txt", "test10_output_mine.txt");

	return 0;
}
