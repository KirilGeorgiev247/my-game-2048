#include "main.h"
#include "iostream"
#include "random"
#include "cmath"

using namespace std;

const int smallRange = 4;
const int middleRange = 16;
const int largeRange = 64;

int main()
{
	int boardSize = { 0 };
	size_t playerScore = { 0 };

	cout << "Enter board size: ";
	cin >> boardSize;
	cout << endl;

	int** board = new int* [boardSize];

	initializeBoard(board, playerScore, boardSize);
}

// int casting makes it works differently from real log function (f.e. 2.6 will return 2)
int logFunc(double base, double argument)
{
	return (int)(log(argument) / log(base));
}

int getRandomSquareOnBoard(const int boardSize)
{
	srand((unsigned int)time(NULL));

	int randomIndex = rand() % boardSize;

	return randomIndex;
}

// gets random playable number by first getting random number than seeing which closest lower number is power of two and returns it
int getRandomPlayableNumber(const size_t playerScore)
{
	// seed the random generator so it does not return the same result
	srand((unsigned int)time(NULL));

	int randomNumInRange = rand() % smallRange + 1;

	int base = 2;
	int timesTheWholePartOfNumberIsPowerOfTwo = logFunc(base, randomNumInRange);

	int result = pow(base, timesTheWholePartOfNumberIsPowerOfTwo);

	if (result == 0)
	{
		result++;
	}

	return result;

}

// <-- board initilization 

// initializes a 2D array
void createBoard(int** board, const int boardSize)
{
	for (size_t i = 0; i < boardSize; i++) {
		board[i] = new int[boardSize];
	}

	for (size_t i = 0; i < boardSize; i++) {
		for (size_t j = 0; j < boardSize; j++) {
			board[i][j] = 0;
		}
	}
}

// gets random square on the board and puts a playable number there
void putFirstNumberOnBoard(int** board, size_t& playerScore, const int boardSize)
{
	int randomplayableNumber = getRandomPlayableNumber(playerScore);

	int randomIndex = getRandomSquareOnBoard(boardSize);

	board[randomIndex][randomIndex] = randomplayableNumber;
	playerScore += randomplayableNumber;
}

void printBoard(int** board, const size_t playerScore, const int boardSize)
{
	for (size_t i = 0; i < boardSize; i++) {
		for (size_t j = 0; j < boardSize; j++) {
			cout << board[i][j] << "      ";
		}

		cout << endl;
		cout << endl;
	}

	cout << "Score: " << playerScore;
}

// frees the memory that the board uses
void freeBoard(int** board, const int boardSize)
{
	for (size_t i = 0; i < boardSize; i++) {
		delete[] board[i];
	}

	delete[] board;
}

void initializeBoard(int** board, size_t& playerScore, const int boardSize)
{
	createBoard(board, boardSize);
	putFirstNumberOnBoard(board, playerScore, boardSize);
	printBoard(board, playerScore, boardSize);
}
// board initilization -->