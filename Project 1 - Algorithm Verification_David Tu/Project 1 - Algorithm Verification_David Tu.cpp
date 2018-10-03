// Project 1 - Algorithm Verification_David Tu.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>

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
void printIntMat(const int mat[ROWS][COLS], const std::string name);
void printStrMat(const std::string mat[ROWS][COLS], const std::string name);
void toFile(const std::string mat[ROWS][COLS], const std::string name, const bool result);
bool verify();

int main(){
	//Variables that will to hold user input:
	std::string name = "Test 1";
	int rows = ROWS;
	int cols = COLS;

	int input1[3][4] = {
		{1, 2, 8, 9},
		{1, 6, 7, 0},
		{2, 3, 4, 5}
	};

	int input2[3][4]{
		{1, 2, 8, 9},
		{1, 6, 7, 0},
		{3, 4, 5, 6}
	};

	int input3[3][6]{
		{1, 2, 3, 6, 7, 8},
		{7, 8, 9, 10, 0, 0},
		{3, 4, 5, 6, 0, 0}
	};

	int incorrect[3][4]{
		{1, 2, 8, 9},
		{1, 6, 7, 0},
		{2, 4, 5, 6}
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
			test_1[i][j] = incorrect[i][j];
		}
	}

	prepVerificationTest(test_1, name + " Test Case", rows, cols);

	std::cout << "Verifying algorithm..." << std::endl;
	bool results = verify();

	if (results) {
		printStrMat(output, name + " Test Results");
	}

	else {
		std::cout << "\nINCORRECT" << std::endl;
	}

	//Make sure to deallocate
	//Delete the column arrays that's within each row
	for (int i = 0; i < rows; i++) {
		delete[] test_1[i];
	}

	//Then delete the row array itself
	delete[] test_1;

	toFile(output, name + " Test Case Results", results);
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

bool verify() {
	char alpha = 'a';
	int sendEventNumber = 1;

	for (int i = 0; i < ROWS; i++) {
		int counter = 1;
		std::cout << "Processing P" << i << ":" << std::endl;

		for (int j = 0; j < COLS; j++) {
			std::cout << "Calculating event at [" << i << "][" <<  j << "] = " << input[i][j] << ":" << std::endl;

			//If the input entry is 0, then that means we are at the end of the process, so just skip to the next process
			if (input[i][j] == 0) {
				std::cout << "Reached the end of process, proceeding to the next one...\n" << std::endl;
				break;
			}

			//Only deal with entries in the output labeled as NULL since we need to determine what kind of event it should be
			if (output[i][j] == "NULL") {

				//Internal events:
				if (input[i][j] == counter) {
					output[i][j] = alpha;
					std::cout << "Result: " << alpha << std::endl;
					alpha++;
					counter++;
				}

				//Receive event suspect
				else {
					std::cout << input[i][j] << " is suspected as being a receive event!!!" << std::endl;
					int maximum = input[i][j] - 1;
					std::cout << "Therefore, a search will be conducted for " << maximum << ", within the input matrix" << std::endl;
					
					//Prevents duplication of send events
					bool found = false;

					//Send event assignment:
					//Search for maximum within the input matrix
					for (int k = 0; k < ROWS; k++) {
						for (int l = 0; l < COLS; l++) {
							if (input[k][l] == maximum && !found && output[k][l].at(0) != 'r') {
								//If the FIRST maximum is found and it's not a receive event, then assign it as the send event
								//Update the entry in the output matrix
								output[k][l] = "s" + std::to_string(sendEventNumber);
								std::cout << "Result: output[" << k << "][" << l << "] = " << output[k][l];
								found = true;
							}
						}
					}

					//break out of the entire function if a send event wasn't found
					if (found == false) {
						std::cout << "Search failed..." << std::endl;
						return false;
					}

					//Receive events:
					//Update the entry in the output as a receive event (different position than send event position)
					output[i][j] = "r" + std::to_string(sendEventNumber);
					std::cout << " and output[" << i << "][" << j << "] = " << output[i][j] << std::endl;
					sendEventNumber++;

					//Upgrade and increment the counter
					counter = input[i][j] + 1;
				}
			}

			//If there's already an entry in the optput, skip it
			else {
				counter = input[i][j] + 1;
			}
		}
	}

	//Indicates that the verification was completed without error
	return true;
}

void toFile(const std::string mat[ROWS][COLS], const std::string name, const bool result) {
	std::ofstream myFile;
	myFile.open("myFile.txt");

	myFile << name << ":\n";

	if (result == true) {
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				if (j == COLS - 1) {
					myFile << output[i][j] << "\n";
				}

				else {
					myFile << output[i][j] << ", ";
				}
			}
		}
	}

	else {
		myFile << "INCORRECT";
	}

	myFile << "\n";
	myFile.close();
}