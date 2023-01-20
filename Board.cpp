#include "Board.h"
#include "MovesHelper.h"
#include "MyMath.h"
#include "Utility.h"
#include "random"
#include "iostream"

const char whitespace = ' ';
const char whitespacesBetweenSquares = 8;
const int linesBetweenSquares = 3;
const char upMoveKey = 'w';
const char leftMoveKey = 'a';
const char rightMoveKey = 'd';
const char downMoveKey = 's';

// player starts playing
void play(int** board, size_t& playerScore, const int boardSize)
{
	while (true)
	{
		char command;
		std::cout << "Enter direction: ";
		std::cin >> command;
		std::cout << std::endl;

		bool isCommandSuccessful = executeCommand(board, playerScore, command, boardSize);

		// checks if there is an empty cell for new number
		if (!isThereValidTurn(board, boardSize))
		{
			// write down score if it is top 5
			// return to main menu

			freeBoard(board, boardSize);
			break;
		}

		if (isCommandSuccessful)
		{
			putNewNumberOnBoard(board, playerScore, boardSize);
			printBoard(board, playerScore, boardSize);
		}

		// checks if a playable turn exists after adding the new generated number 
		if (!isThereValidTurn(board, boardSize))
		{
			// write down score if it is top 5
			// return to main menu

			freeBoard(board, boardSize);
			break;
		}
	}
}

// executes move command
// returns if the command has executed successfully
bool executeCommand(int** board, size_t& playerScore, const char command, const int boardSize)
{
	bool isSuccess = false;

	switch (command)
	{
	case upMoveKey:
		if (isUpCommandPossible(board, boardSize))
		{
			isSuccess = true;
			upMove(board, boardSize);
		}
		break;
	case leftMoveKey:
		if (isLeftCommandPossible(board, boardSize))
		{
			isSuccess = true;
			leftMove(board, boardSize);
		}
		break;
	case downMoveKey:
		if (isDownCommandPossible(board, boardSize))
		{
			isSuccess = true;
			downMove(board, boardSize);
		}
		break;
	case rightMoveKey:
		if (isRigthCommandPossible(board, boardSize))
		{
			isSuccess = true;
			rightMove(board, boardSize);
		}
		break;
	default:
		// wrong command
		break;
	}

	return isSuccess;
}

// moves numbers on the board on the highest row possible
void upMove(int** board, const int boardSize)
{
	int squares = boardSize * boardSize;

	int doubleSquaresCount = { 0 };
	Square* doubledSquares = new Square[squares];

	// row
	for (int row = 1; row < boardSize; row++)
	{
		// col
		for (int col = 0; col < boardSize; col++)
		{
			int* cellP = &board[row][col];

			// gets the index of the doubled square with such position if it exists
			int indexOfDoubledSquare = getIndexOfSquare(Square(row, col), doubledSquares, doubleSquaresCount);

			bool isThereDifferentNumberInBetween = false;
			if (*cellP != 0)
			{
				for (int i = row - 1; i >= 0; i--)
				{
					int* currCellP = &board[i][col];

					if (*currCellP == 0)
					{
						*currCellP = *cellP;
						*cellP = { 0 };
						cellP = currCellP;

						if (indexOfDoubledSquare != -1)
						{
							doubledSquares[indexOfDoubledSquare] = Square(i, col);
						}
					}
					else if (*cellP != *currCellP)
					{
						isThereDifferentNumberInBetween = true;
					}
					else if (*cellP == *currCellP
						&& !isThereDifferentNumberInBetween
						&& !containsSquare(Square(i, col), doubledSquares, doubleSquaresCount))
					{
						*currCellP *= 2;
						*cellP = 0;
						isThereDifferentNumberInBetween = false;
						doubledSquares[doubleSquaresCount++] = Square(i, col);
						break;
					}
				}
			}
			cellP = nullptr;
		}
	}

	delete[] doubledSquares;
}

// moves numbers on the board on the most left row possible
void leftMove(int** board, const int boardSize)
{
	int squares = boardSize * boardSize;

	int doubleSquaresCount = { 0 };
	Square* doubledSquares = new Square[squares];

	// row
	for (int row = 0; row < boardSize; row++)
	{
		// col
		for (int col = 1; col < boardSize; col++)
		{
			int* cellP = &board[row][col];

			// gets the index of the doubled square with such position if it exists
			int indexOfDoubledSquare = getIndexOfSquare(Square(row, col), doubledSquares, doubleSquaresCount);

			bool isThereDifferentNumberInBetween = false;
			if (*cellP != 0)
			{
				for (int i = col - 1; i >= 0; i--)
				{
					int* currCellP = &board[row][i];

					if (*currCellP == 0)
					{
						*currCellP = *cellP;
						*cellP = { 0 };
						cellP = currCellP;

						if (indexOfDoubledSquare != -1)
						{
							doubledSquares[indexOfDoubledSquare] = Square(row, i);
						}
					}
					else if (*currCellP != *cellP)
					{
						isThereDifferentNumberInBetween = true;
					}
					else if (*cellP == *currCellP
						&& !isThereDifferentNumberInBetween
						&& !containsSquare(Square(row, i), doubledSquares, doubleSquaresCount))
					{
						*currCellP *= 2;
						*cellP = 0;
						isThereDifferentNumberInBetween = false;
						doubledSquares[doubleSquaresCount++] = Square(row, i);
						break;
					}
				}
			}
			cellP = nullptr;
		}
	}

	delete[] doubledSquares;
}

// moves numbers on the board on the lowest row possible
void downMove(int** board, const int boardSize)
{
	int squares = boardSize * boardSize;

	int doubleSquaresCount = { 0 };
	Square* doubledSquares = new Square[squares];

	// row
	for (int row = boardSize - 2; row >= 0; row--)
	{
		// col
		for (int col = 0; col < boardSize; col++)
		{
			int* cellP = &board[row][col];

			// gets the index of the doubled square with such position if it exists
			int indexOfDoubledSquare = getIndexOfSquare(Square(row, col), doubledSquares, doubleSquaresCount);

			bool isThereDifferentNumberInBetween = false;
			if (*cellP != 0)
			{
				for (size_t i = row + 1; i < boardSize; i++)
				{
					int* currCellP = &board[i][col];

					if (*currCellP == 0)
					{
						*currCellP = *cellP;
						*cellP = { 0 };
						cellP = currCellP;

						if (indexOfDoubledSquare != -1)
						{
							doubledSquares[indexOfDoubledSquare] = Square(i, col);
						}
					}
					else if (*currCellP != *cellP)
					{
						isThereDifferentNumberInBetween = true;
					}
					else if (*cellP == *currCellP
						&& !isThereDifferentNumberInBetween
						&& !containsSquare(Square(i, col), doubledSquares, doubleSquaresCount))
					{
						*currCellP *= 2;
						*cellP = 0;
						isThereDifferentNumberInBetween = false;
						doubledSquares[doubleSquaresCount++] = Square(i, col);
						break;
					}
				}
			}
			cellP = nullptr;
		}
	}

	delete[] doubledSquares;

}

// moves numbers on the board on the most right row possible
void rightMove(int** board, const int boardSize)
{
	int squares = boardSize * boardSize;

	int doubleSquaresCount = { 0 };
	Square* doubledSquares = new Square[squares];

	// row
	for (int row = 0; row < boardSize; row++)
	{
		// col
		for (int col = boardSize - 2; col >= 0; col--)
		{
			int* cellP = &board[row][col];

			// gets the index of the doubled square with such position if it exists
			int indexOfDoubledSquare = getIndexOfSquare(Square(row, col), doubledSquares, doubleSquaresCount);

			bool isThereDifferentNumberInBetween = false;
			if (*cellP != 0)
			{
				for (size_t i = col + 1; i < boardSize; i++)
				{
					int* currCellP = &board[row][i];

					if (*currCellP == 0)
					{
						*currCellP = *cellP;
						*cellP = { 0 };
						cellP = currCellP;

						if (indexOfDoubledSquare != -1)
						{
							doubledSquares[indexOfDoubledSquare] = Square(row, i);
						}
					}
					else if (*currCellP != *cellP)
					{
						// check the inbetween
						isThereDifferentNumberInBetween = true;
					}
					else if (*cellP == *currCellP
						&& !isThereDifferentNumberInBetween
						&& !containsSquare(Square(row, i), doubledSquares, doubleSquaresCount))
					{
						*currCellP *= 2;
						*cellP = 0;
						isThereDifferentNumberInBetween = false;
						doubledSquares[doubleSquaresCount++] = Square(row, i);
						break;
					}
				}
			}
			cellP = nullptr;
		}
	}

	delete[] doubledSquares;
}

// checks if up command is possible to be executed
bool isUpCommandPossible(int** board, const int boardSize)
{
	// row
	for (int row = 1; row < boardSize; row++)
	{
		// col
		for (int col = 0; col < boardSize; col++)
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

// checks if left command is possible to be executed
bool isLeftCommandPossible(int** board, const int boardSize)
{
	// row
	for (int row = 0; row < boardSize; row++)
	{
		// col
		for (int col = 1; col < boardSize; col++)
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

// checks if down command is possible to be executed
bool isDownCommandPossible(int** board, const int boardSize)
{
	// row
	for (int row = boardSize - 2; row >= 0; row--)
	{
		// col
		for (int col = 0; col < boardSize; col++)
		{
			int cell = board[row][col];
			bool isThereDifferentNumberInBetween = false;
			if (cell != 0)
			{
				for (int i = row + 1; i < boardSize; i++)
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

// checks if right command is possible to be executed
bool isRigthCommandPossible(int** board, const int boardSize)
{
	// row
	for (int row = 0; row < boardSize; row++)
	{
		// col
		for (int col = boardSize - 2; col >= 0; col--)
		{
			int cell = board[row][col];
			bool isThereDifferentNumberInBetween = false;
			if (cell != 0)
			{
				for (int i = col + 1; i < boardSize; i++)
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

// checks if there is a valid turn to be played
bool isThereValidTurn(int** board, const int boardSize)
{
	bool validTurnExists = isLeftCommandPossible(board, boardSize)
		|| isUpCommandPossible(board, boardSize)
		|| isRigthCommandPossible(board, boardSize)
		|| isDownCommandPossible(board, boardSize);

	return validTurnExists;
}

// gets random square on the board with coordinates row and col indexes
Square getRandomSquareOnBoard(int** board, const int boardSize)
{
	// seeding the random function so it does not return the same result every time
	srand((unsigned int)time(NULL));

	int rowRandomIndex = rand() % boardSize;
	int colRandomIndex = rand() % boardSize;

	if (board[rowRandomIndex][colRandomIndex] != 0)
	{
		int test = board[rowRandomIndex][colRandomIndex];
		// checks for free square after the given random square
		for (int i = 0; i < boardSize; i++)
		{
			for (int j = 0; j < boardSize; j++)
			{
				if (board[i][j] == 0)
				{
					rowRandomIndex = i;
					colRandomIndex = j;
					break;
				}
			}
		}
	}

	return Square(rowRandomIndex, colRandomIndex);
}

// gets random square on the board and puts a playable number there
void putNewNumberOnBoard(int** board, size_t& playerScore, const int boardSize)
{
	int randomplayableNumber = getRandomPlayableNumber(playerScore, boardSize);

	Square randomSquare = getRandomSquareOnBoard(board, boardSize);

	board[randomSquare.rowIndex][randomSquare.colIndex] = randomplayableNumber;
	playerScore += randomplayableNumber;
}

// initializes a 2D array
void createBoard(int** board, const int boardSize)
{
	for (int i = 0; i < boardSize; i++) {
		board[i] = new int[boardSize];
	}

	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			board[i][j] = 0;
		}
	}
}

// prints digits on every square on the board
void printBoard(int** board, const size_t playerScore, const int boardSize)
{
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {

			int currSquareNumberLen = getNumLength(board[i][j]);

			std::cout << board[i][j];

			for (int i = 0; i < whitespacesBetweenSquares - currSquareNumberLen + 1; i++)
			{
				std::cout << whitespace;
			}
		}

		for (int i = 0; i < linesBetweenSquares; i++)
		{
			std::cout << std::endl;
		}
	}

	std::cout << "Score: " << playerScore << std::endl;
}

// frees the memory that the board uses
void freeBoard(int** board, const int boardSize)
{
	for (int i = 0; i < boardSize; i++) {
		delete[] board[i];
	}

	delete[] board;
}

// creates board, puts number on the it and prints it
void initializeBoard(int** board, size_t& playerScore, const int boardSize)
{
	createBoard(board, boardSize);
	putNewNumberOnBoard(board, playerScore, boardSize);
	printBoard(board, playerScore, boardSize);
}