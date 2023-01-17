#pragma once

#include "Square.h"

// player starts playing
void play(int** board, size_t& playerScore, const int boardSize);

// executes move command
// returns if the command has executed successfully
bool executeCommand(int** board, size_t& playerScore, const char command, const int boardSize);

// moves numbers on the board on the highest row possible
void upMove(int** board, const int boardSize);

// moves numbers on the board on the most left row possible
void leftMove(int** board, const int boardSize);

// moves numbers on the board on the lowest row possible
void downMove(int** board, const int boardSize);

// moves numbers on the board on the most right row possible
void rightMove(int** board, const int boardSize);

// checks if up command is possible to be executed
bool isUpCommandPossible(int** board, const int boardSize);

// checks if left command is possible to be executed
bool isLeftCommandPossible(int** board, const int boardSize);

// checks if down command is possible to be executed
bool isDownCommandPossible(int** board, const int boardSize);

// checks if right command is possible to be executed
bool isRigthCommandPossible(int** board, const int boardSize);

// checks if there is a valid turn to be played
bool isThereValidTurn(int** board, const int boardSize);

// gets random square on the board with coordinates row and col indexes
Square getRandomSquareOnBoard(int** board, const int boardSize);

// gets random square on the board and puts a playable number there
void putNewNumberOnBoard(int** board, size_t& playerScore, const int boardSize);

// initializes a 2D array
void createBoard(int** board, const int boardSize);

// prints digits on every square on the board
void printBoard(int** board, const size_t playerScore, const int boardSize);

// creates board, puts number on the it and prints it
void freeBoard(int** board, const int boardSize);

// frees the memory that the board uses
void initializeBoard(int** board, size_t& playerScore, const int boardSize);