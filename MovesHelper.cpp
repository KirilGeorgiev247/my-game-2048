#include "MovesHelper.h"

// checks if current square has been doubled already
bool containsSquare(const Square square, const Square* squares, const int length)
{
	for (int i = 0; i < length; i++)
	{
		if (squares[i].rowIndex == square.rowIndex
			&& squares[i].colIndex == square.colIndex)
		{
			return true;
		}
	}
	return false;
}

// gets index of the current doubled squares 
// returns -1 if it does not contain this square
int getIndexOfSquare(const Square square, const Square* squares, const int length)
{
	for (int i = 0; i < length; i++)
	{
		if (squares[i].rowIndex == square.rowIndex
			&& squares[i].colIndex == square.colIndex)
		{
			return (int)i;
		}
	}

	return -1;
}