///////////////////////////////////////////////////////////////////////////////
// Main File:        cache1D.c
// This File:        cache1D.c
// Other Files:      cache1D.c cache2Drows.c cache2Dcols.c cache2Dclash.c
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
//////////////////////////// 80 columns wide ///////////////////////////////////

int arr[100000];

int main() {

	for (int i = 0; i < sizeOf(arr); i++) {
		arr[i] = i;
	}

	return 0;
