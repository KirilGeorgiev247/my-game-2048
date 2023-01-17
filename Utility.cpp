#include "Utility.h"
#include <iostream>

const int maxScoreLength = 15;
const char comma = ',';
const char dash = '-';

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