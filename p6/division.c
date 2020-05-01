///////////////////////////////////////////////////////////////////////////////
// Main File:        division.c
// This File:        division.c
// Other Files:      sendsig.c, division.c
// Semester:         CS 354 Spring 2020
//
// Author:           Clifford Dunteman
// Email:            clifford@wisc.edu
// CS Login:         clifford
//
/////////////////////////// OTHER SOURCES OF HELP /////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2013,2019-2020
// Posting or sharing this file is prohibited, including any changes/additions.
//
////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<string.h>
#include<signal.h>
int counter;

void handler_SIGINT(int sig) {
	printf("\nTotal number of operations successfully completed: %d\n", counter);
	printf("The program will be terminated.\n");
	exit(0);
}

void handler_SIGFPE(int sig) {
	printf("Error: a division by 0 operation was attempted.\n");
    printf("Total number of operations completed successfully: %d\n", counter);
	printf("The program will be terminated.\n");
    exit(0);
}

int main(int argc, char** argv) {
	struct sigaction actfpe, actint;

	memset(&actfpe, 0, sizeof(actfpe));
	actfpe.sa_handler = handler_SIGFPE;

	if (sigaction(SIGFPE, &actfpe, NULL) <0) {
		perror("Error binding sigaction for SIGFPE!\n");
		return 1;
	}

	memset(&actint, 0, sizeof(actint));
	actint.sa_handler = handler_SIGINT;

	if (sigaction(SIGINT, &actint, NULL) <0) {
		perror("Error binding sigaction for SIGINT!\n");
	}

	while(1) {
		char buf[100];
		int num1, num2, res;
		printf("Enter first integer: ");
		fgets(buf, 100, stdin);
		num1 = atoi(buf);
		printf("Enter second integer: ");
		fgets(buf, 100, stdin);
		num2 = atoi(buf);
		res = num1 / num2;
		printf("%d / %d is %d with a remainder of %d\n",\
        num1, num2, res, num1 - num2*res);
		counter++;
	}
	return 0;
}
