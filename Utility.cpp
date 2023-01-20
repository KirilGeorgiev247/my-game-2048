#include "Utility.h"
#include "FileHelper.h"
#include <iostream>

const int maxScoreLength = 15;
const char comma = ',';
const char dash = '-';
const char whitespace = ' ';
const int minBoardSize = 4;
const int maxBoardSize = 10;
const int nicknameMinLength = 3;
const int nicknameMaxLength = 20;

// casts num from string to number
size_t getCastedNumAsInt(const char* numAsStr, const int numLength)
{
	size_t num = { 0 };
	size_t helpingNum = { 1 };

	for (size_t i = 0; i < numLength - 1; i++)
	{
		helpingNum *= 10;
	}

	for (size_t i = 0; i < numLength; i++)
	{
		char test = numAsStr[i];

		// gets int digit from char type
		int digit = numAsStr[i] - '0';
		int numToAdd = digit * helpingNum;
		num += numToAdd;
		helpingNum /= 10;
	}

	return num;
}

// gets score out of line of type nickname-score and returns it 
size_t getScoreOutOfLine(const char* line)
{
	char* score = new char[maxScoreLength];

	int lineIndex = { 0 };
	int scoreIndex = { 0 };

	while (true)
	{
		if (line[lineIndex] == dash)
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

// gets nickname out of line of type nickname-score and returns it
const char* getNicknameOutOfLine(const char* line)
{
	char* nickname = new char[nicknameMaxLength];

	int lineIndex = { 0 };

	while (true)
	{
		char currCh = line[lineIndex];

		if (currCh == '\0' || currCh == dash || currCh == whitespace)
		{
			nickname[lineIndex] = '\0';
			break;
		}

		nickname[lineIndex] = line[lineIndex++];
	}

	return nickname;
}

// returns true if they are the same
const bool compareStrings(const char* firstString, const char* secondString)
{
	int index = { 0 };

	bool areTheSame = true;

	while (true)
	{
		if (firstString[index] == '\0')
		{
			if (secondString[index] != '\0')
			{
				areTheSame = false;
			}

			break;
		}

		if (secondString[index] == '\0')
		{
			if (firstString[index] != '\0')
			{
				areTheSame = false;
			}

			break;
		}

		if (firstString[index] != secondString[index])
		{
			areTheSame = false;
			break;
		}

		index++;
	}

	return areTheSame;
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
void appendScoreToLine(char* line, const size_t playerScore, int& lineIndex)
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
				std::swap(scoreLines[j], scoreLines[j + 1]);
			}
		}
	}
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

// prints best 5 players when given information from file
void printBest5(char** best5Scores, const int scoresCount)
{
	int index = { 0 };

	for (size_t i = 0; i < scoresCount; i++)
	{
		int index = { 0 };
		const char* scoreLine = best5Scores[i];

		char currCh;
		while (true)
		{
			currCh = scoreLine[index++];

			if (currCh == dash)
			{
				std::cout << " - ";
			}
			else if (currCh == '\0')
			{
				std::cout << std::endl;
				break;
			}
			else
			{
				std::cout << currCh;
			}
		}
	}
}

// reads input and validates it until is pass the checks
void validateNicknameInput(char* nickname, const int boardSize)
{
	bool isFirstTimeReadingNickname = true;
	bool isThereExistingNickname = false;

	while (true)
	{
		if (isFirstTimeReadingNickname || isThereExistingNickname)
		{
			isThereExistingNickname = false;
			std::cout << "Enter your nickname: ";
			std::cin >> nickname;
			isFirstTimeReadingNickname = false;
		}

		int count = { 0 };
		char** best5players = getBestFiveScores(boardSize, count);

		for (int i = 0; i < count; i++)
		{
			if (compareStrings(nickname, getNicknameOutOfLine(best5players[i])))
			{
				isThereExistingNickname = true;
				std::cout << "There is one existing player with the same nickname" << std::endl;

				for (int i = 0; i < count; i++)
				{
					delete[] best5players[i];
				}

				delete best5players;

				break;
			}
		}

		if (isThereExistingNickname)
		{
			continue;
		}

		if (getStrLen(nickname) < nicknameMinLength || getStrLen(nickname) > nicknameMaxLength)
		{
			std::cout << std::endl;
			std::cout << "Enter valid nickname ( length between 3 and 20): ";
			std::cin >> nickname;

			if (getStrLen(nickname) >= nicknameMinLength && getStrLen(nickname) <= nicknameMaxLength)
			{
				break;
			}
		}
		else
		{
			break;
		}
	}
}

// reads input and validates it until is pass the checks
void validateBoardsizeInput(int& boardSize)
{
	bool isFirstTimeReadingBoardsize = true;

	while (true)
	{
		if (isFirstTimeReadingBoardsize)
		{
			std::cout << "Enter board size: ";
			std::cin >> boardSize;
			isFirstTimeReadingBoardsize = false;
		}

		if (boardSize < minBoardSize || boardSize > maxBoardSize)
		{
			std::cout << std::endl;
			std::cout << "Enter valid boardsize ( between 4 and 10): ";
			std::cin >> boardSize;

			if (boardSize >= minBoardSize && boardSize <= maxBoardSize)
			{
				break;
			}
		}
		else
		{
			break;
		}
	}
}