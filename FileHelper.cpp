#include "FileHelper.h"
#include "Utility.h"
#include "fstream"
#include <iostream>

const int maxBoardSize = 10;
const int shortFileNameLength = 8;
const int longFileNameLength = 10;

const char comma = ',';
const char dash = '-';
const int fileLineMaxLength = 100;
const int playersWithBestScoresCount = 6; // adding one more for the newest one

// gets the name of a file depending on the board size
const char* getFileName(const int boardSize)
{
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

// writes new player score in format player - score
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

	newLine[index++] = dash;

	appendScoreToLine(newLine, playerScore, index);

	newLine[index] = '\0';

	int count = { 0 };

	char** previousBest5Scores = getBestFiveScores(boardSize, count);

	if (count != 0)
	{
		sortCurrentScoreLine(previousBest5Scores, newLine, count);

		// delete current content on the file
		std::ofstream myFileToDelete(fileName);
		myFileToDelete << "";
		myFileToDelete.close();

		std::ofstream myFileToWrite;
		myFileToWrite.open(fileName, std::ios::app);

		int iterations = count < 5 ? count + 1 : count;

		for (int i = 0; i < iterations; i++)
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
				std::cout << "Data was not saves successfully";
			}
		}

		myFileToWrite.close();

		for (int i = 0; i < count + 1; i++)
		{
			delete[] previousBest5Scores[i];
		}

		delete[] previousBest5Scores;
	}
	else
	{
		std::ofstream myFileToWrite;
		myFileToWrite.open(fileName);

		const char* newLineAsStr = newLine;
		myFileToWrite << newLineAsStr;

		if (!myFileToWrite)
		{
			std::cout << "Data was not saves successfully";
		}

		myFileToWrite.close();
	}

	delete[] fileName;
}

// gets top 5 players with best scores
char** getBestFiveScores(const int boardSize, int& count)
{
	const char* fileName = getFileName(boardSize);

	std::ifstream myFile;

	myFile.open(fileName);

	delete[] fileName;

	char** result = new char* [playersWithBestScoresCount];

	for (int i = 0; i < playersWithBestScoresCount; i++)
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

// gets file content length
int getFileLength(const char* fileName)
{
	std::fstream myFile;

	myFile.open(fileName, std::ios::in);

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