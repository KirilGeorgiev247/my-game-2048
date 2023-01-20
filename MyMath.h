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
* <header for math functions>
*
*/

#pragma once

// int casting makes it works differently from real log function (f.e. 2.6 will return 2)
int logFunc(double base, double argument);

// gets random playable number by first getting random number than seeing which closest lower number is power of two and returns it
int getRandomPlayableNumber(const size_t playerScore, const int boardScore);
