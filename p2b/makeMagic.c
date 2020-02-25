///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        makeMagic.c
// This File:        makeMagic.c
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Spring 2020
//
// Author:           Clifford Dunteman
// Email:            cdunteman@wisc.edu	
// CS Login:         clifford
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   Avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct {
    int size;     // dimension of the square
    int **msquare; // pointer to heap allocated magic square
} MSquare;

/* TODO:
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize() {
	printf("Enter magic square's size (odd integer >=3)");

	int number;
	scanf("%d", &number);

	if (number % 2 != 1) {
		printf("Size must be odd.\n");
		exit(1);
	}

	if (number < 3) {
		printf("Size must be >= 3.\n");
		exit(1);
	}

	return number;   
} 
   
/* TODO:
 * Makes a magic square of size n using the Siamese algorithm
 * and returns a pointer to the completed MSquare struct.
 *
 * n the number of rosw and columns
 */
MSquare *generateMSquare(int n) {
	
	struct MSquare *outputSquareStruct = (struct MSquare*)malloc(sizeof(struct MSquare));
    outputSquareStruct-> msquare = (int **)malloc(n * sizeof(int*));
    
	for (int i = 0; i < n; i++) {
        *(outputSquareStruct->msquare+i) = (int *)malloc(n * sizeof(int));
    }

    outputSquareStruct->size = n;
    int **square = outputSquareStruct->msquare; 
    int startingPoint = n / 2;

    int maxValue = n*n;
    int i = 0;
    int j = 0;
    int iCorrection = 0; //corrections for when you index into a filled box
    int jCorrection = 0; //corrections for when you index into a filled box
    //loops through all the numbers you have to put into the magic square
    //the indexing is handled by variables called i and j
    //I know there is a more consice way to do the indexing but this is
    //equivalent so sorry for being hard to read
    for (int k = 0; k < maxValue; k++) {
	i = (maxValue - k + iCorrection) % n;
	j = (k + startingPoint + jCorrection)  % n;
	//if the space is already full you should drop down one box,
	//these corrections terms will do exactly that
        if (*(*(square + i) + j) != 0) {
	    iCorrection = iCorrection + 2;
	    jCorrection--;
	}
        //recalculates i and j for with correction terms
	i = (maxValue - k + iCorrection) % n;
	j = (k + startingPoint + jCorrection)  % n;
	*(*(square + i) + j) = k + 1;

    }

    return outputSquareStruct;    
} 

/* TODO:  
 * Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * msquare the magic square to output
 * filename the name of the output file
 */
void outputMSquare(MSquare *msquare, char *filename) {
	FILE *ofp = fopen(filename, "w");
	if (ofp == NULL) 
	{
		fprintf(stderr, "Can't open output file %s!\n", filename);
		exit(1);
	}

	for (int i = 0; i < msquare -> size; i++) {
		fprintf(ofp, "%s", "\n");
		for (int j = 0; j < msquare -> size; j++) {
			fprintf(ofp, "%d", *(*(msquare -> msquare + i) + j));
			if (j % msquare -> size != 0) {
				fprintf(ofp, "%s", ",");
			}
		}
	}

}

/* TODO:
 * Generates a magic square of the user specified size and
 * output the quare to the output filename
 */
int main(int argc, char *argv[]) {	
	if (argc != 2)
	{
		fprintf(stderr, "Usage: ./makeMagic <output_filename>\n");
		exit(1);
	}

    // Get magin square's size from user
	int size = getSize();

	// Generate the magic square
	struct MSquare *testSquare = generateMSquare(size);

    printf("Generate square works\n");
	
	// TODO: Output the magic square
	outputMSquare(msquare, argv[1]);

	free(msquare -> msquare);
	free(msquare);
    return 0;
} 	
