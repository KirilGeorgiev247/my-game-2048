#pragma once

// gets the name of a file depending on the board size
const char* getFileName(const int boardSize);

// writes player score in format player - score
void writeScore(const char* nickname, const size_t playerScore, const int boardSize);

// gets file content length
int getFileLength(const char* fileName);

// gets top 5 players with best scores
char** getBestFiveScores(const int boardSize, int& count);
