#pragma once

// casts num from string to number
size_t getCastedNumAsInt(const char* numAsStr, const int numLength);

// gets score out of line of type nickname-score and returns it 
size_t getScoreOutOfLine(const char* line);

// gets nickname out of line of type nickname-score and returns it
const char* getNicknameOutOfLine(const char* line);

// gets num digits
int getNumLength(size_t num);

// appends score to nickname
void appendScoreToLine(char* line, const size_t playerScore, int& lineIndex);

// sorts best 5 scores compared to the new one
void sortCurrentScoreLine(char** scoreLines, char* currScoreLine, const int scoresCount);

// gets length of string
int getStrLen(char* str);

// returns true if they are the same
const bool compareStrings(const char* firstString, const char* secondString);

// prints best 5 players when given information from file
void printBest5(char** best5Scores, const int scoresCount);

// reads input and validates it until is pass the checks
void validateBoardsizeInput(int& boardSize);

// reads input and validates it until is pass the checks
void validateNicknameInput(char* nickname, const int boardSize);