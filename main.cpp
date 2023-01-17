#include "iostream"

#include "MyMath.h"
#include "Utility.h"
#include "Square.h"
#include "MovesHelper.h"
#include "FileHelper.h"
#include "Board.h"

const int minBoardSize = 4;
const int maxBoardSize = 10;
const int nicknameMinLength = 3;
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

		if (gameMode == 1)
		{
			// start game
			int boardSize = { 0 };
			size_t playerScore = { 0 };
			char* nickname = new char[nicknameMaxLength + extraLengthForNicknameToDoTheValidation];

			bool isFirstTimeReadingNickname = true;

			while (true)
			{
				if (isFirstTimeReadingNickname)
				{
					std::cout << "Enter your nickname: ";
					std::cin >> nickname;
					isFirstTimeReadingNickname = false;
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

			int** board = new int* [boardSize];

			initializeBoard(board, playerScore, boardSize);

			play(board, playerScore, boardSize);

			writeScore(nickname, playerScore, boardSize);
		}
		else if (gameMode == 2)
		{
			int boardSize = { 0 };
			std::cout << "Enter board size: ";
			std::cin >> boardSize;

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

			for (size_t i = 0; i < scoresCount; i++)
			{
				delete[] best5Scores[i];
			}

			delete[] best5Scores;
		}
		else if (gameMode == 3)
		{
			break;
		}
	}
}
