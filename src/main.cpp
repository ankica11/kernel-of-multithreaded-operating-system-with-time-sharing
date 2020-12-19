/*
 * main.cpp
 *
 *  Created on: Aug 30, 2019
 *      Author: OS1
 */


#include <stdio.h>


#include "timer.h"

extern int userMain(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	Timer::inic();

	int retVal=userMain(argc, argv);

	Timer::restore();

	return retVal;
}


