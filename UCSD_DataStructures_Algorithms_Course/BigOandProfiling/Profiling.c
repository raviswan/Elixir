/*
 * File:		main.c
 * Author:  Ray Mitchell
 * Date:		2010-09-27
 *
 * Simple program demonstrating how to profile a section of code to determine
 * how long the section of code takes to execute.
 *
 * Program output (on my MacBook Pro, 2.53 GHz Intel Core 2 Duo):
 *		Operation took 0.290777 seconds to complete.
 */
#include <stdio.h>
#include <time.h>

void doSomeLengthyOperation()
{
	int i;
	for (i = 0; i < 10000000; ++i)
		printf(".");
}

int main()
{
	clock_t startTicks;
	clock_t stopTicks;
	double elapsedSeconds;

	/* Get elapsed processor ticks prior to executing section of code */
	startTicks = clock();

	/* Execute the section of code */
	doSomeLengthyOperation();

	/* Get elapsed processor ticks after executing section of code */
	stopTicks = clock();

	/* Output time section of code took to complete */
	elapsedSeconds = (double)(stopTicks - startTicks) / CLOCKS_PER_SEC;
	printf("Operation took %g seconds to complete.\n", elapsedSeconds);
}
