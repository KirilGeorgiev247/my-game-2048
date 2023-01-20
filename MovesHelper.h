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
* <header for the moves helper>
*
*/

#pragma once

#include "Square.h"


// checks if current square has been doubled already
bool containsSquare(const Square square, const Square* squares, const int length);

// gets index of the current doubled squares 
int getIndexOfSquare(const Square square, const Square* squares, const int length);
