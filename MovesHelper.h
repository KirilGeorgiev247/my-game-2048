#pragma once

#include "Square.h"


// checks if current square has been doubled already
bool containsSquare(const Square square, const Square* squares, const int length);

// gets index of the current doubled squares 
int getIndexOfSquare(const Square square, const Square* squares, const int length);
