// Project 1 - Algorithm Verification_David Tu.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>

//Globals
const int ROWS = 5;
const int COLS = 25;
int input[ROWS][COLS] = { 0 };
std::string output[ROWS][COLS] = { "NULL" };

//The sendEvents array will contain all of the send event values, in their corresponding positions
//For instance, for s1 = 10, 10 will be stored in sendEvents[0]
int sendEvents[COLS];

//Prototypes
void printIntMatrix(int **mat, const std::string name, const int rows, const int cols);
void printIntArr(const int array[], const int size, const std::string name);

//Dependant on ROWS and COLS
void prepVerificationTest(int **mat, const std::string testName, const int rows, const int cols);
void verify();
void printIntMat(const int mat[ROWS][COLS], const std::string name);
void printStrMat(const std::string mat[ROWS][COLS], const std::string name);

int main(){
	//Variables that will to hold user input:
	std::string name = "Test 1";
	int rows = ROWS;
	int cols = COLS;

	int input[3][4] = {
		{1, 2, 8, 9},
		{1, 6, 7, 0},
		{2, 3, 4, 5}
	};

	rows = 3;
	cols = 4;

	//Normal arrays don't support variable sizes, so I need to allocate it in the heap
	int **test_1 = new int*[rows];

	//For each row, allocate the number of columns (i.e. the number of entries)
	for (int i = 0; i < rows; i++) {
		test_1[i] = new int[cols];
	}

	//Initialize the newly allocated matrix with NULL strings
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			test_1[i][j] = 0;
		}
	}

	printIntMatrix(test_1, "Initialized " + name + "[" + std::to_string(rows) + "][" + std::to_string(cols) + "]", rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			test_1[i][j] = input[i][j];
		}
	}

	prepVerificationTest(test_1, name + " Test Case", 3, 4);

	std::cout << "Verifying algorithm..." << std::endl;
	verify();
	printStrMat(output, name + " Test Results");

	return 0;
}

void printIntMat(const int mat[ROWS][COLS], const std::string name) {
	std::cout << name << ":" << std::endl;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (j == COLS - 1) {
				std::cout << mat[i][j] << std::endl;
			}

			else {
				std::cout << mat[i][j] << ", ";
			}
		}
	}

	std::cout << std::endl;
}

void printStrMat(const std::string mat[ROWS][COLS], const std::string name) {
	std::cout << name << ":" << std::endl;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (j == COLS - 1) {
				std::cout << mat[i][j] << std::endl;
			}

			else {
				std::cout << mat[i][j] << ", ";
			}
		}
	}

	std::cout << std::endl;
}

void printIntArr(const int array[], const int size, const std::string name) {
	std::cout << name << ":" << std::endl;

	for (int i = 0; i < size; i++) {
		if (i == size - 1) {
			std::cout << array[i] << std::endl;
		}

		else {
			std::cout << array[i] << ", ";
		}
	}

	std::cout << std::endl;
}

void printIntMatrix(int **mat, const std::string name, const int rows, const int cols) {
	std::cout << name << ":" << std::endl;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (j == cols - 1) {
				std::cout << mat[i][j] << std::endl;
			}

			else {
				std::cout << mat[i][j] << ", ";
			}
		}
	}

	std::cout << std::endl;
}

void prepVerificationTest(int **mat, const std::string testName, const int rows, const int cols) {
	//Initialize the test space to 0
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			input[i][j] = 0;
		}
	}

	printIntMat(input, "Initialized test space");
	
	//To avoid out of bounds errors, transfer the given matrix to a bigger one
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			input[i][j] = mat[i][j];
		}
	}

	printIntMat(input, testName);

	//Initialize the output
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			output[i][j] = "NULL";
		}
	}

	printStrMat(output, "Initialized Output");

	//Initialize sendEvents array to -1
	for (int i = 0; i < COLS; i++) {
		sendEvents[i] = -1;
	}

	printIntArr(sendEvents, COLS, "Initialized sendEvents array");
}

void verify() {
	std::string alpha = "a";
	int sendEventNumber = 1;

	for (int i = 0; i < ROWS; i++) {
		int counter = 1;

		for (int j = 0; j < COLS; j++) {
			//If the input entry is 0, then that means we are at the end of the process, so skip it
			if (input[i][j] == 0) {
				break;
			}

			//If there's already an entry in the optput, skip it
			if (output[i][j] != "NULL") {
				break;
			}

			if (input[i][j] == counter) {
				output[i][j] = alpha;
				//TODO: find a way to increment alpha
				counter++;
			}

			//Receive event suspect
			else {
				std::cout << "The suspected receive event is: " << input[i][j] << std::endl;
				int maximum = input[i][j] - 1;
				std::cout << "Therefore, a search will be conducted for " << maximum << ", within the input matrix:";
				
				//Search for this max within the input matrix
				//TODO: Find a way to stop these loops once the max has been found
				for (int k = 0; k < ROWS; k++) {
					std::cout << std::endl;
					
					for (int l = 0; l < COLS; l++) {
						std::cout << input[k][l] << ", ";
						
						if (input[k][l] == maximum) {
							//If the max is found, then it is the send event
							//Update the entry in the output as a send event
							output[k][l] = "s";
							//output[k][l] = "s" + sendEventNumber;
						}
					}
				}

				std::cout << std::endl << std::endl;

				//Update the entry in the output as a receive event (different position than send event position)
				//output[i][j] = "r" + sendEventNumber;
				output[i][j] = "r";
				sendEventNumber++;

				//Upgrade and increment the counter
				counter = input[i][j] + 1;
			}

		}
	}
}