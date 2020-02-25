//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        n_in_a_row.c
// This File:        n_in_a_row.c
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Spring 2020
//
// Author:           Clifford Dunteman
// Email:            cdunteman@wisc.edu
// CS Login:         clifford
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
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
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
     
char *COMMA = ",";  
     
/* COMPLETED:       
 * Retrieves from the first line of the input file,
 * the size of the board (number of rows and columns).
 * 
 * fp: file pointer for input file
 * size: pointer to size
 */
void get_dimensions(FILE *fp, int *size) {      
    char *line = NULL;
    size_t len = 0;
    if (getline(&line, &len, fp) == -1) 
    {
        printf("Error in reading the file.\n");
        exit(1);
    }

    char *token = NULL;
    token = strtok(line, COMMA);
    *size = atoi(token);
}       
 
   
  
/* COMPLETED:
 * Returns 1 if and only if the board is in a valid state.
 * Otherwise returns 0.
 * 
 * board: heap allocated 2D board
 * size: number of rows and columns
 */
int n_in_a_row(int **board, int size) {

    //Check if board has odd number off rows and columns    
    if (size % 2 == 0) 
    {
        return 0;
    }

    //Count total number of x's and o's on board
    int tot_x = 0;
    int tot_o = 0;

    //Count x's and o's in current row, column, or diagonal
    int num_x = 0;
    int num_o = 0;

    //Count wins
    int x_wins = 0;
    int o_wins = 0;

    //Iterate through rows
    for (int i = 0; i < size; i++) {
	num_x = 0;
        num_o = 0;
	for (int j = 0; j < size; j++) {
	    if (*(*(board + i) + j) == 1)
            {
	        tot_x += 1;
		num_x += 1;
	    }
            else if (*(*(board + i) + j) == 2) {
                tot_o += 1;
		num_o += 1;
	    }
        }

	if (num_x == size)
	{
	    x_wins += 1;	
        }
	else if (num_o == size)
	{
            o_wins += 1;
	}
    }

    num_x = 0;
    num_o = 0;

    //Check if valid number of wins
    if (x_wins > 1 || o_wins > 1)
    {
	return 0;
    }
    else if (x_wins == 1 && o_wins == 1)
    {
	return 0;
    }

    x_wins = 0;
    o_wins = 0;

    //Check if x always goes first
    if (num_x - num_o != 0 && num_x - num_o)
    {
	return 0;
    }

    //Iterate through columns
    for (int i = 0; i < size; i++) {
	num_x = 0;
	num_o = 0;
        for (int j = 0; j < size; j++) {
	    if (*(*(board + j) + i) == 1) 
	    {
                num_x += 1;
	    }
	    else if (*(*(board + j) + i) == 2) {
		num_o += 1;
	}
	if (num_x == size) {
	    x_wins += 1;
	}
	else if (num_o == size) 
	{
            o_wins += 1;
	}
	}
    }


    //Check if valid number of wins
    if (x_wins > 1 || o_wins > 1) {
        return 0;
    }
    else if (x_wins == 1 && o_wins == 1)
    {
        return 0;
    }

    x_wins = 0;
    o_wins = 0;

    //Board state is valid
    return 1;
}


/* COMPLETED
 * This program prints Valid if the input file contains
 * a game board with either 1 or no winners; and where
 * there is at most 1 more X than O.
 * 
 * argc: CLA count
 * argv: CLA value
 */
int main(int argc, char *argv[]) {              
     
    //Check if number of command-line arguments is correct.
    if(argc != 2)
    {
	printf("Usage: ./n_in_a_row <input_filename>\n");
	return 0;
    }

    //Open the file and check if it opened successfully.
    FILE *fp = fopen(*(argv + 1), "r");
    if (fp == NULL)
    {
        printf("Can't open file for reading.\n");
        exit(1);
    }

    //Declare local variables.
    int size;
    int *sizeptr = &size;

    //Call get_dimensions to retrieve the board size.
    get_dimensions(fp, sizeptr);

    //Dynamically allocate a 2D array of dimensions retrieved above.
    int **board = malloc(sizeof(int) * size);
    if (board == NULL)
    {
	exit(1);
    }
    for (int i = 0; i < size; i++)
    {
	board[i] = malloc(sizeof(int) * size);
    }

    //Read the file line by line.
    //Tokenize each line with comma to store the values in your 2D array.
    char *line = NULL;
    size_t len = 0;
    char *token = NULL;
    for (int i = 0; i < size; i++) {

        if (getline(&line, &len, fp) == -1)
       	{
            printf("Error while reading the file.\n");
            exit(1);
	}
        token = strtok(line, COMMA);
        for (int j = 0; j < size; j++) {
            //Complete the line of code below
            //to initialize your 2D array.
            *(j + *(board+i)) = atoi(token);
            token = strtok(NULL, COMMA);
        }
    }

    //Call the function n_in_a_row and print the appropriate
    //output depending on the function's return value.
    int result = n_in_a_row(board, size);
	if (result == 0) 
	{
	    printf("invalid\n");
	}
	    else if (result == 1) 
	{
	    printf("valid\n");
	}

    // Free all dynamically allocated memory.
    free(board);
    board = NULL;

    //Close the file.
    if (fclose(fp) != 0)
    {
        printf("Error while closing the file.\n");
        exit(1);
    } 
     
    return 0;       
}
