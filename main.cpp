#include "iostream"
#include "random"
#include "cmath"

using namespace std;

const int smallRange = 4;
const int middleRange = 16;
const int largeRange = 64;

class Square {
public:
	unsigned int rowIndex;
	unsigned int colIndex;

	Square(unsigned int rowIndex, unsigned int colIndex) {
		this->rowIndex = rowIndex;
		this->colIndex = colIndex;
	}

private:
	Square() {
		this->rowIndex = 0;
		this->colIndex = 0;
	}
};

void upMove(int** board, size_t& playerScore, const int boardSize);
void leftMove(int** board, size_t& playerScore, const int boardSize);
void downMove(int** board, size_t& playerScore, const int boardSize);
void rightMove(int** board, size_t& playerScore, const int boardSize);

bool isUpCommandPossible(int** board, const int boardSize);
bool isLeftCommandPossible(int** board, const int boardSize);
bool isDownCommandPossible(int** board, const int boardSize);
bool isRigthCommandPossible(int** board, const int boardSize);

bool executeCommand(int** board, size_t& playerScore, const char command, const int boardSize);
void play(int** board, size_t& playerScore, const int boardSize);
bool isThereValidTurn(int** board, const int boardSize);

int logFunc(double base, double argument);

int getRandomPlayableNumber(const size_t playerScore);
Square getRandomSquareOnBoard(int** board, const int boardSize);
void putNewNumberOnBoard(int** board, size_t& playerScore, const int boardSize);

void createBoard(int** board, const int boardSize);
void printBoard(int** board, const size_t playerScore, const int boardSize);
void freeBoard(int** board, const int boardSize);
void initializeBoard(int** board, size_t& playerScore, const int boardSize);


int main()
{
	int boardSize = { 0 };
	size_t playerScore = { 0 };

	cout << "Enter board size: ";
	cin >> boardSize;
	cout << endl;

	int** board = new int* [boardSize];

	initializeBoard(board, playerScore, boardSize);

	play(board, playerScore, boardSize);
}

void play(int** board, size_t& playerScore, const int boardSize)
{
	while (true)
	{
		char command;
		cout << "Enter direction: ";
		cin >> command;
		cout << endl;

		bool isCommandSuccessful = executeCommand(board, playerScore, command, boardSize);

		// checks if there is an empty cell for new number
		if (!isThereValidTurn(board, boardSize))
		{
			// write down score if it is top 5
			// return to main menu

			break;
		}

		if (isCommandSuccessful)
		{
			putNewNumberOnBoard(board, playerScore, boardSize);
		}

		// checks if a playable turn exists after adding the new generated number 
		if (!isThereValidTurn(board, boardSize))
		{
			// write down score if it is top 5
			// return to main menu

			break;
		}

		printBoard(board, playerScore, boardSize);
	}
}

/// <-- Moves

// returns if the command has executed successfully
bool executeCommand(int** board, size_t& playerScore, const char command, const int boardSize)
{
	bool isSuccess = false;

	switch (command)
	{
	case 'w':
		if (isUpCommandPossible(board, boardSize))
		{
			isSuccess = true;
			upMove(board, playerScore, boardSize);
		}
		break;
	case 'a':
		if (isLeftCommandPossible(board, boardSize))
		{
			isSuccess = true;
			leftMove(board, playerScore, boardSize);
		}
		break;
	case 's':
		if (isDownCommandPossible(board, boardSize))
		{
			isSuccess = true;
			downMove(board, playerScore, boardSize);
		}
		break;
	case 'd':
		if (isRigthCommandPossible(board, boardSize))
		{
			isSuccess = true;
			rightMove(board, playerScore, boardSize);
		}
		break;
	default:
		// wrong command
		break;
	}

	return isSuccess;
}

void upMove(int** board, size_t& playerScore, const int boardSize)
{
	// row
	for (size_t row = 1; row < boardSize; row++)
	{
		// col
		for (size_t col = 0; col < boardSize; col++)
		{
			int* cellP = &board[row][col];
			bool isThereDifferentNumberInBetween = false;
			if (*cellP != 0)
			{
				for (int i = row - 1; i >= 0; i--)
				{
					int* currCellP = &board[i][col];

					if (*currCellP == 0)
					{
						*currCellP = *cellP;
						*cellP = 0;
						cellP = currCellP;
					}
					else if (*cellP != *currCellP)
					{
						isThereDifferentNumberInBetween = true;
					}
					else if (*cellP == *currCellP && !isThereDifferentNumberInBetween)
					{
						playerScore += *currCellP;
						*currCellP *= 2;
						*cellP = 0;
						isThereDifferentNumberInBetween = false;
					}
				}
			}
		}
	}
}

void leftMove(int** board, size_t& playerScore, const int boardSize)
{
	// row
	for (size_t row = 0; row < boardSize; row++)
	{
		// col
		for (size_t col = 1; col < boardSize; col++)
		{
			int* cellP = &board[row][col];
			bool isThereDifferentNumberInBetween = false;
			if (*cellP != 0)
			{
				for (int i = col - 1; i >= 0; i--)
				{
					int* currCellP = &board[row][i];

					if (*currCellP == 0)
					{
						*currCellP = *cellP;
						*cellP = 0;
						cellP = currCellP;
					}
					else if (*currCellP != *cellP)
					{
						isThereDifferentNumberInBetween = true;
					}
					else if (*currCellP == *cellP && !isThereDifferentNumberInBetween)
					{
						playerScore += *currCellP;
						*currCellP *= 2;
						*cellP = 0;
						isThereDifferentNumberInBetween = false;
					}
				}
			}
		}
	}
}

void downMove(int** board, size_t& playerScore, const int boardSize)
{
	// row
	for (int row = boardSize - 2; row >= 0; row--)
	{
		// col
		for (size_t col = 0; col < boardSize; col++)
		{
			int* cellP = &board[row][col];
			bool isThereDifferentNumberInBetween = false;
			if (*cellP != 0)
			{
				for (size_t i = row + 1; i < boardSize; i++)
				{
					int* currCellP = &board[i][col];

					if (*currCellP == 0)
					{
						*currCellP = *cellP;
						*cellP = 0;
						cellP = currCellP;
					}
					else if (*currCellP != *cellP)
					{
						isThereDifferentNumberInBetween = true;
					}
					else if (*currCellP == *cellP && !isThereDifferentNumberInBetween)
					{
						playerScore += *currCellP;
						*currCellP *= 2;
						*cellP = 0;
					}
				}
			}
		}
	}
}

void rightMove(int** board, size_t& playerScore, const int boardSize)
{
	// row
	for (size_t row = 0; row < boardSize; row++)
	{
		// col
		for (int col = boardSize - 2; col >= 0; col--)
		{
			int* cellP = &board[row][col];
			bool isThereDifferentNumberInBetween = false;
			if (*cellP != 0)
			{
				for (size_t i = col + 1; i < boardSize; i++)
				{
					int* currCellP = &board[row][i];

					if (*currCellP == 0)
					{
						*currCellP = *cellP;
						*cellP = 0;
						cellP = currCellP;
					}
					else if (*currCellP != *cellP)
					{
						// check the inbetween
						isThereDifferentNumberInBetween = true;
					}
					else if (*currCellP == *cellP && !isThereDifferentNumberInBetween)
					{
						playerScore += *currCellP;
						*currCellP *= 2;
						*cellP = 0;
						isThereDifferentNumberInBetween = false;
					}
				}
			}
		}
	}
}

/// Moves -->

/// <-- Validating for turn possibility

bool isUpCommandPossible(int** board, const int boardSize)
{
	// row
	for (size_t row = 1; row < boardSize; row++)
	{
		// col
		for (size_t col = 0; col < boardSize; col++)
		{
			int cell = board[row][col];
			bool isThereDifferentNumberInBetween = false;
			if (cell != 0)
			{
				for (int i = row - 1; i >= 0; i--)
				{
					int currCell = board[i][col];

					if (currCell == 0)
					{
						return true;
					}
					else if (currCell != cell)
					{
						isThereDifferentNumberInBetween = true;
					}
					else if (currCell == cell && !isThereDifferentNumberInBetween)
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool isLeftCommandPossible(int** board, const int boardSize)
{
	// row
	for (size_t row = 0; row < boardSize; row++)
	{
		// col
		for (size_t col = 1; col < boardSize; col++)
		{
			int cell = board[row][col];
			bool isThereDifferentNumberInBetween = false;
			if (cell != 0)
			{
				for (int i = col - 1; i >= 0; i--)
				{
					int currCell = board[row][i];

					if (currCell == 0)
					{
						return true;
					}
					else if (currCell != cell)
					{
						// check the inbetween
						isThereDifferentNumberInBetween = true;
					}
					else if (currCell == cell && !isThereDifferentNumberInBetween)
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool isDownCommandPossible(int** board, const int boardSize)
{
	// row
	for (int row = boardSize - 2; row >= 0; row--)
	{
		// col
		for (size_t col = 0; col < boardSize; col++)
		{
			int cell = board[row][col];
			bool isThereDifferentNumberInBetween = false;
			if (cell != 0)
			{
				for (size_t i = row + 1; i < boardSize; i++)
				{
					int currCell = board[i][col];

					if (currCell == 0)
					{
						return true;
					}
					else if (currCell != cell)
					{
						isThereDifferentNumberInBetween = true;
					}
					else if (currCell == cell && !isThereDifferentNumberInBetween)
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool isRigthCommandPossible(int** board, const int boardSize)
{
	// row
	for (size_t row = 0; row < boardSize; row++)
	{
		// col
		for (int col = boardSize - 2; col >= 0; col--)
		{
			int cell = board[row][col];
			bool isThereDifferentNumberInBetween = false;
			if (cell != 0)
			{
				for (size_t i = col + 1; i < boardSize; i++)
				{
					int currCell = board[row][i];

					if (currCell == 0)
					{
						return true;
					}
					else if (currCell != cell)
					{
						// check the inbetween
						isThereDifferentNumberInBetween = true;
					}
					else if (currCell == cell && !isThereDifferentNumberInBetween)
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool isThereValidTurn(int** board, const int boardSize)
{
	bool validTurnExists = isLeftCommandPossible(board, boardSize)
		|| isUpCommandPossible(board, boardSize)
		|| isRigthCommandPossible(board, boardSize)
		|| isDownCommandPossible(board, boardSize);

	return validTurnExists;
}
/// Validating for turn possibility -->

/// <-- Generating number on board

// int casting makes it works differently from real log function (f.e. 2.6 will return 2)
int logFunc(double base, double argument)
{
	return (int)(log(argument) / log(base));
}

Square getRandomSquareOnBoard(int** board, const int boardSize)
{
	bool shouldCheckOtherWay = false;

	srand((unsigned int)time(NULL));

	int rowRandomIndex = rand() % boardSize;
	int colRandomIndex = rand() % boardSize;

	if (board[rowRandomIndex][colRandomIndex] != 0)
	{
		// checks for free square after the given random square
		for (int i = rowRandomIndex; i < boardSize; i++)
		{
			for (int j = colRandomIndex; j < boardSize; j++)
			{
				if (board[i][j] != 0)
				{
					rowRandomIndex = i;
					colRandomIndex = j;
					shouldCheckOtherWay = true;
					break;
				}
			}
		}

		// checks for free square before the given random square if all that are after are taken
		if (shouldCheckOtherWay)
		{
			for (int i = 0; i < rowRandomIndex; i++)
			{
				for (int j = 0; j < colRandomIndex; j++)
				{
					if (board[i][j] != 0)
					{
						rowRandomIndex = i;
						colRandomIndex = j;
						break;
					}
				}
			}
		}
	}

	return Square(rowRandomIndex, colRandomIndex);
}

// gets random square on the board and puts a playable number there
void putNewNumberOnBoard(int** board, size_t& playerScore, const int boardSize)
{
	int randomplayableNumber = getRandomPlayableNumber(playerScore);

	Square randomSquare = getRandomSquareOnBoard(board, boardSize);

	board[randomSquare.rowIndex][randomSquare.colIndex] = randomplayableNumber;
	playerScore += randomplayableNumber;
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

	if (result == 0 || result == 1)
	{
		result = 2;
	}

	return result;

}

/// Generating number on board -->

/// <-- Board initilization 

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

void printBoard(int** board, const size_t playerScore, const int boardSize)
{
	for (size_t i = 0; i < boardSize; i++) {
		for (size_t j = 0; j < boardSize; j++) {
			cout << board[i][j] << "      ";
		}

		cout << endl;
		cout << endl;
		cout << endl;
	}

	cout << "Score: " << playerScore << endl;
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
	putNewNumberOnBoard(board, playerScore, boardSize);
	printBoard(board, playerScore, boardSize);
}
/// Board initilization -->