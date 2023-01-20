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
* <header for square>
*
*/

#pragma once

struct Square {
	unsigned int rowIndex;
	unsigned int colIndex;

	Square(unsigned int rowIndex, unsigned int colIndex);

	Square();
};