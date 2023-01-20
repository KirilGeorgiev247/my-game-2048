/**
*
* Solution to course project # 4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Kiril Georgiev
* @idnumber 8MI0600268* @compiler Visual Studio
*
* <main file>
*
*/

#include "iostream"
#include "MyMath.h"
#include "Utility.h"
#include "Square.h"
#include "MovesHelper.h"
#include "FileHelper.h"
#include "Board.h"

const int playMode = 1;
const int leaderboardMode = 2;
const int exitMode = 3;
const char dash = '-';
const int nicknameMaxLength = 20;
const int extraLengthForNicknameToDoTheValidation = 10;

int main()
{
	int gameMode = { 0 };

	while (true)
	{
		std::cout << "1. Start game" << std::endl;
		std::cout << "2. Leaderboard" << std::endl;
		std::cout << "3. Quit" << std::endl;
		std::cout << "Choose a command number (f.e. 1): ";
		std::cin >> gameMode;

		if (gameMode == playMode)
		{
			// start game
			int boardSize = { 0 };
			size_t playerScore = { 0 };
			char* nickname = new char[nicknameMaxLength + extraLengthForNicknameToDoTheValidation];

			validateBoardsizeInput(boardSize);
			validateNicknameInput(nickname, boardSize);

			int** board = new int* [boardSize];

			initializeBoard(board, playerScore, boardSize);

			play(board, playerScore, boardSize);

			writeScore(nickname, playerScore, boardSize);

			delete[] nickname;
		}
		else if (gameMode == leaderboardMode)
		{
			int boardSize = { 0 };
			std::cout << "Enter board size: ";
			std::cin >> boardSize;

			int scoresCount = { 0 };
			char** best5Scores = getBestFiveScores(boardSize, scoresCount);

			// check if file is empty
			const char* filename = getFileName(boardSize);
			int fileLength = getFileLength(filename);

			if (fileLength == 0)
			{
				std::cout << "File is empty" << std::endl;
				continue;
			}

			printBest5(best5Scores, scoresCount);

			for (size_t i = 0; i < scoresCount; i++)
			{
				delete[] best5Scores[i];
			}

			delete[] best5Scores;
		}
		else if (gameMode == exitMode)
		{
			break;
		}
		else 
		{
			std::cout << "Invalid mode" << std::endl;
		}
	}

	return 0;
}
