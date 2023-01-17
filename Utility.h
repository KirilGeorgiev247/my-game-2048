#pragma once

// casts num from string to number
size_t getCastedNumAsInt(const char* numAsStr, const int numLength);

// gets score out of line of type nickname-score and returns it 
size_t getScoreOutOfLine(const char* line);

// gets num digits
int getNumLength(size_t num);

// appends score to nickname
void appendScoreToLine(char* line, const size_t playerScore, int& lineIndex);

// sorts best 5 scores compared to the new one
void sortCurrentScoreLine(char** scoreLines, char* currScoreLine, const int scoresCount);

// gets length of string
int getStrLen(char* str);