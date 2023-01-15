#include "iostream"
#include "fstream"
#include "random"
#include "cmath"

using namespace std;

const int minBoardSize = 4;
const int maxBoardSize = 10;
const int smallRange = 4;
const int middleRange = 16;
const int largeRange = 64;
const int middleRangeScoreRequired = 256;
const int largeRangeScoreRequired = 1024;
const int shortFileNameLength = 8;
const int longFileNameLength = 10;
const char comma = ',';
const char whitespace = ' ';
const char whitespacesBetweenSquares = 8;
const int fileLineMaxLength = 100;
const int playersWithBestScoresCount = 6; // adding one more for the newest one
const int maxScoreLength = 15;
const int nicknameMaxLength = 20;
const int linesBetweenSquares = 3;

struct Square {
	unsigned int rowIndex;
	unsigned int colIndex;

	Square(unsigned int rowIndex, unsigned int colIndex) : rowIndex(rowIndex), colIndex(colIndex) {}

	Square() {}
};

void upMove(int** board, const int boardSize);
void leftMove(int** board, const int boardSize);
void downMove(int** board, const int boardSize);
void rightMove(int** board, const int boardSize);

bool isUpCommandPossible(int** board, const int boardSize);
bool isLeftCommandPossible(int** board, const int boardSize);
bool isDownCommandPossible(int** board, const int boardSize);
bool isRigthCommandPossible(int** board, const int boardSize);

bool executeCommand(int** board, size_t& playerScore, const char command, const int boardSize);
void play(int** board, size_t& playerScore, const int boardSize);
bool isThereValidTurn(int** board, const int boardSize);

int logFunc(double base, double argument);

bool containsSquare(const Square square, const Square* squares, const int length);
int getIndexOfSquare(const Square square, const Square* squares, const int length);

int getRandomPlayableNumber(const size_t playerScore, const int boardScore);
Square getRandomSquareOnBoard(int** board, const int boardSize);
void putNewNumberOnBoard(int** board, size_t& playerScore, const int boardSize);

void createBoard(int** board, const int boardSize);
void printBoard(int** board, const size_t playerScore, const int boardSize);
void freeBoard(int** board, const int boardSize);
void initializeBoard(int** board, size_t& playerScore, const int boardSize);

size_t getCastedNumAsInt(const char* numAsStr, const int numLength);
size_t getScoreOutOfLine(const char* line);
int getNumLength(size_t num);
void writeScoreToLine(char* line, const size_t playerScore, int& lineIndex);
void sortCurrentScoreLine(char** scoreLines, char* currScoreLine, const int scoresCount);
int getStrLen(char* str);

const char* getFileName(const int boardSize);
void writeScore(const char* nickname, const size_t playerScore, const int boardSize);
int getFileLength(const char* fileName);
char** getBestFiveScores(const int boardSize, int& count);

int main()
{
	int commandNumber = { 0 };

	while (true)
	{
		cout << "1. Start game" << endl;
		cout << "2. Leaderboard" << endl;
		cout << "3. Quit" << endl;
		cout << "Choose a command number (f.e. 1): ";
		cin >> commandNumber;

		if (commandNumber == 1)
		{
			// start game
			int boardSize = { 0 };
			size_t playerScore = { 0 };
			char* nickname = new char[nicknameMaxLength + 10];

			bool isFirstTimeReadingNickname = true;

			while (true)
			{
				if (isFirstTimeReadingNickname)
				{
					cout << "Enter your nickname: ";
					cin >> nickname;
					isFirstTimeReadingNickname = false;
				}

				if (getStrLen(nickname) < 3 || getStrLen(nickname) > 20)
				{
					cout << endl;
					cout << "Enter valid nickname ( length between 3 and 20): ";
					cin >> nickname;

					if (getStrLen(nickname) >= 3 && getStrLen(nickname) <= 20)
					{
						break;
					}
				}
				else
				{
					break;
				}
			}

			bool isFirstTimeReadingBoardsize = true;

			while (true)
			{
				if (isFirstTimeReadingBoardsize)
				{
					cout << "Enter board size: ";
					cin >> boardSize;
					isFirstTimeReadingBoardsize = false;
				}

				if (boardSize < 4 || boardSize > 10)
				{
					cout << endl;
					cout << "Enter valid boardsize ( between 4 and 10): ";
					cin >> boardSize;

					if (boardSize >= 4 && boardSize <= 10)
					{
						break;
					}
				}
				else
				{
					break;
				}
			}

			int** board = new int* [boardSize];

			initializeBoard(board, playerScore, boardSize);

			play(board, playerScore, boardSize);

			writeScore(nickname, playerScore, boardSize);
		}
		else if (commandNumber == 2)
		{
			int boardSize = { 0 };
			cout << "Enter board size: ";
			cin >> boardSize;

			int scoresCount = { 0 };
			char** best5Scores = getBestFiveScores(boardSize, scoresCount);

			int index = { 0 };

			for (size_t i = 0; i < scoresCount; i++)
			{
				int index = { 0 };
				char* scoreLine = best5Scores[i];

				char currCh;
				while (true)
				{
					currCh = scoreLine[index++];

					if (currCh == '-')
					{
						cout << " - ";
					}
					else if (currCh == '\0')
					{
						cout << endl;
						break;
					}
					else
					{
						cout << currCh;
					}
				}
			}

			for (size_t i = 0; i < scoresCount; i++)
			{
				delete[] best5Scores[i];
			}

			delete[] best5Scores;
		}
		else if (commandNumber == 3)
		{
			break;
		}
	}
}

/// <-- Work with files
const char* getFileName(const int boardSize)
{
	//should not be right here
	if (boardSize < maxBoardSize)
	{
		char* fileName = new char[shortFileNameLength];

		fileName[0] = (boardSize + '0');
		fileName[1] = 'x';
		fileName[2] = (boardSize + '0');
		fileName[3] = '.';
		fileName[4] = 't';
		fileName[5] = 'x';
		fileName[6] = 't';
		fileName[7] = '\0';

		return fileName;
	}
	else if (boardSize == maxBoardSize)
	{
		char* fileName = new char[longFileNameLength];

		fileName[0] = '1';
		fileName[1] = '0';
		fileName[2] = 'x';
		fileName[3] = '1';
		fileName[4] = '0';
		fileName[5] = '.';
		fileName[6] = 't';
		fileName[7] = 'x';
		fileName[8] = 't';
		fileName[9] = '\0';

		return fileName;
	}
}

size_t getCastedNumAsInt(const char* numAsStr, const int numLength)
{
	size_t num = { 0 };
	size_t helpingNum = 1;

	for (size_t i = 0; i < numLength - 1; i++)
	{
		helpingNum *= 10;
	}

	for (size_t i = 0; i < numLength; i++)
	{
		char test = numAsStr[i];
		int digit = numAsStr[i] - '0';
		int numToAdd = digit * helpingNum;
		num += numToAdd;
		helpingNum /= 10;
	}

	return num;
}

// gets length of string
int getStrLen(char* str)
{
	int count = { 0 };

	while (true)
	{
		if (str[count] == '\0')
		{
			break;
		}

		count++;
	}

	return count;
}

// gets score out of line of type nickname-score and returns it 
size_t getScoreOutOfLine(const char* line)
{
	char* score = new char[maxScoreLength];

	int lineIndex = { 0 };
	int scoreIndex = { 0 };

	while (true)
	{
		if (line[lineIndex] == '-')
		{
			lineIndex++;
			break;
		}

		lineIndex++;
	}

	while (true)
	{
		if (line[lineIndex] == '\0' || line[lineIndex] == comma)
		{
			break;
		}

		score[scoreIndex++] = line[lineIndex++];
	}

	return getCastedNumAsInt(score, scoreIndex);
}

// gets num digits
int getNumLength(size_t num)
{
	int length = { 1 };

	while (true)
	{
		if (num / 10 == 0)
		{
			break;
		}

		num /= 10;
		length++;
	}

	return length;
}

// appends score to nickname
void writeScoreToLine(char* line, const size_t playerScore, int& lineIndex)
{
	int numLength = getNumLength(playerScore);
	int helpingNum = { 1 };

	for (size_t i = 0; i < numLength - 1; i++)
	{
		helpingNum *= 10;
	}

	for (size_t i = 0; i < numLength; i++)
	{
		int digit = (playerScore / helpingNum) % 10;

		// digit + '0' gets the digit as a char
		line[lineIndex++] = digit + '0';
		helpingNum /= 10;
	}
}

// sorts best 5 scores compared to the new one
void sortCurrentScoreLine(char** scoreLines, char* currScoreLine, const int scoresCount)
{
	int lastIndex = scoresCount;

	scoreLines[lastIndex++] = currScoreLine;

	int newCount = lastIndex;

	for (int i = 0; i < newCount - 1; ++i)
	{
		for (int j = 0; j < newCount - i - 1; ++j)
		{
			if (getScoreOutOfLine(scoreLines[j]) < getScoreOutOfLine(scoreLines[j + 1]))
			{
				swap(scoreLines[j], scoreLines[j + 1]);
			}
		}
	}
}

// writes new score to file
void writeScore(const char* nickname, const size_t playerScore, const int boardSize)
{
	const char* fileName = getFileName(boardSize);

	char* newLine = new char[fileLineMaxLength];
	int index = { 0 };

	while (nickname[index] != '\0')
	{
		newLine[index] = nickname[index];
		index++;
	}

	newLine[index++] = '-';

	writeScoreToLine(newLine, playerScore, index);

	newLine[index] = '\0';

	int count = { 0 };

	char** previousBest5Scores = getBestFiveScores(boardSize, count);

	if (count != 0)
	{
		sortCurrentScoreLine(previousBest5Scores, newLine, count);

		// delete current content on the file
		ofstream myFileToDelete(fileName);
		myFileToDelete << "";
		myFileToDelete.close();

		ofstream myFileToWrite;
		myFileToWrite.open(fileName, ios::app);

		int iterations = count < 5 ? count + 1 : count;

		for (size_t i = 0; i < iterations; i++)
		{
			const char* currLine = previousBest5Scores[i];

			if (currLine[0] != '\0')
			{
				if (i != iterations - 1)
				{
					myFileToWrite << currLine << comma;
				}
				else
				{
					myFileToWrite << currLine;
				}
			}

			if (!myFileToWrite)
			{
				cout << "Data was not saves successfully";
			}
		}

		myFileToWrite.close();

		for (size_t i = 0; i < count + 1; i++)
		{
			delete[] previousBest5Scores[i];
		}

		delete[] previousBest5Scores;
	}
	else
	{
		ofstream myFileToWrite;
		myFileToWrite.open(fileName);

		const char* newLineAsStr = newLine;
		myFileToWrite << newLineAsStr;

		if (!myFileToWrite)
		{
			cout << "Data was not saves successfully";
		}

		myFileToWrite.close();
	}

	delete[] fileName;
}

// gets file content length
int getFileLength(const char* fileName)
{
	fstream myFile;

	myFile.open(fileName, ios::in);

	char ch;
	int counter = { 0 };

	while (true)
	{
		myFile >> ch;

		if (myFile.eof())
		{
			break;
		}

		counter++;
	}

	myFile.close();

	return counter;
}

char** getBestFiveScores(const int boardSize, int& count)
{
	const char* fileName = getFileName(boardSize);

	ifstream myFile;

	myFile.open(fileName);

	delete[] fileName;

	char** result = new char* [playersWithBestScoresCount];

	for (size_t i = 0; i < playersWithBestScoresCount; i++)
	{
		result[i] = new char[fileLineMaxLength];
	}

	int resultIndex = { 0 };

	while (true)
	{
		if (myFile.eof())
		{
			break;
		}

		char* currLine = new char[fileLineMaxLength];
		myFile.getline(currLine, fileLineMaxLength, ',');

		if (currLine[0] == '\0')
		{
			break;
		}

		result[resultIndex++] = currLine;
		count++;
	}

	myFile.close();

	return result;
}
/// Work with files -->

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
			upMove(board, boardSize);
		}
		break;
	case 'a':
		if (isLeftCommandPossible(board, boardSize))
		{
			isSuccess = true;
			leftMove(board, boardSize);
		}
		break;
	case 's':
		if (isDownCommandPossible(board, boardSize))
		{
			isSuccess = true;
			downMove(board, boardSize);
		}
		break;
	case 'd':
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

void upMove(int** board, const int boardSize)
{
	int squares = boardSize * boardSize;

	int doubleSquaresCount = { 0 };
	Square* doubledSquares = new Square[squares];

	// row
	for (size_t row = 1; row < boardSize; row++)
	{
		// col
		for (size_t col = 0; col < boardSize; col++)
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

void leftMove(int** board, const int boardSize)
{
	int squares = boardSize * boardSize;

	int doubleSquaresCount = { 0 };
	Square* doubledSquares = new Square[squares];

	// row
	for (size_t row = 0; row < boardSize; row++)
	{
		// col
		for (size_t col = 1; col < boardSize; col++)
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

void downMove(int** board, const int boardSize)
{
	int squares = boardSize * boardSize;

	int doubleSquaresCount = { 0 };
	Square* doubledSquares = new Square[squares];

	// row
	for (int row = boardSize - 2; row >= 0; row--)
	{
		// col
		for (size_t col = 0; col < boardSize; col++)
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

void rightMove(int** board, const int boardSize)
{
	int squares = boardSize * boardSize;

	int doubleSquaresCount = { 0 };
	Square* doubledSquares = new Square[squares];

	// row
	for (size_t row = 0; row < boardSize; row++)
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

bool containsSquare(const Square square, const Square* squares, const int length)
{
	for (size_t i = 0; i < length; i++)
	{
		if (squares[i].rowIndex == square.rowIndex
			&& squares[i].colIndex == square.colIndex)
		{
			return true;
		}
	}
	return false;
}

// returns -1 if it does not contain this square
int getIndexOfSquare(const Square square, const Square* squares, const int length)
{
	for (size_t i = 0; i < length; i++)
	{
		if (squares[i].rowIndex == square.rowIndex
			&& squares[i].colIndex == square.colIndex)
		{
			return (int)i;
		}
	}

	return -1;
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

// gets random playable number by first getting random number than seeing which closest lower number is power of two and returns it
int getRandomPlayableNumber(const size_t playerScore, const int boardSize)
{
	// seed the random generator so it does not return the same result
	srand((unsigned int)time(NULL));

	int randomNumInRange = { 0 };

	if (playerScore < middleRangeScoreRequired)
	{
		randomNumInRange = rand() % smallRange + 1;
	}
	else if (playerScore > largeRangeScoreRequired)
	{
		randomNumInRange = rand() % largeRange + 1;
	}
	else
	{
		randomNumInRange = rand() % middleRange + 1;
	}

	int base = { 2 };
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

			int currSquareNumberLen = getNumLength(board[i][j]);

			cout << board[i][j];

			for (size_t i = 0; i < whitespacesBetweenSquares - currSquareNumberLen + 1; i++)
			{
				cout << whitespace;
			}
		}

		for (size_t i = 0; i < linesBetweenSquares; i++)
		{
			cout << endl;
		}
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