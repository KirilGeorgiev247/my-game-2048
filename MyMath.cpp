#include "MyMath.h"
#include "cmath"
#include "random"

const int smallRange = 4;
const int middleRange = 16;
const int largeRange = 64;
const int middleRangeScoreRequired = 256;
const int largeRangeScoreRequired = 1024;

// int casting makes it works differently from real log function (f.e. 2.6 will return 2)
int logFunc(double base, double argument)
{
	return (int)(log(argument) / log(base));
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