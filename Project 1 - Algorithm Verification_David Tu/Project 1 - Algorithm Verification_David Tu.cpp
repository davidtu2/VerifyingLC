// Project 1 - Algorithm Verification_David Tu.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>

//Globals
const int ROWS = 5;
const int COLS = 25;
int SEND_NO = 1;
char ALPHA = 'a';
//Indicates whether or not the program should accept user input
bool requestIn = false;
int input[ROWS][COLS] = { 0 };
std::string output[ROWS][COLS] = { "NULL" };

//Prototypes
void printIntMatrix(int **mat, const std::string name, const int rows, const int cols);
void printIntArr(const int array[], const int size, const std::string name);

//Dependant on ROWS and COLS
void prepVerificationTest(int **mat, const std::string testName, const int rows, const int cols);
void printIntMat(const int mat[ROWS][COLS], const std::string name);
void printStrMat(const std::string mat[ROWS][COLS], const std::string name);
void toFile(const std::string mat[ROWS][COLS], const std::string name, const bool result);
bool verifyAlgo(const int row);

int main(){
	//Variables that will to hold user input:
	std::string name = "Test 1";
	int rows = 3;
	int cols = 6;

	int given1[3][6] = {
		{1, 2, 8, 9, 0, 0},
		{1, 6, 7, 0, 0, 0},
		{3, 4, 5, 6, 0, 0}
	};

	int given2[3][6] = {
		{1, 2, 8, 9, 0, 0},
		{1, 6, 7, 0, 0, 0},
		{2, 3, 4, 5, 0, 0}
	};

	int input1[3][6]{
		{1, 3, 4, 5, 6, 7},
		{1, 3, 4, 6, 7, 8},
		{1, 2, 3, 6, 7, 8}
	};

	int incorrect[3][6]{
		{1, 2, 8, 9, 0, 0},
		{1, 6, 7, 0, 0, 0},
		{2, 4, 5, 6, 0, 0}
	};

	//Request user input:
	if (requestIn) {
		std::cout << "What is the name of your matrix? ";
		std::cin >> name;
		std::cout << "Enter the number of rows:";
		std::cin >> rows;
		std::cout << "Enter the number of cols:";
		std::cin >> cols;
		std::cout << std::endl;
	}

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

	if (requestIn) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				std::cout << "Enter entry for " << name << "[" << i << "][" << j << "]:";
				std::cin >> test_1[i][j];
			}
		}

		std::cout << std::endl;
	}

	//Transfer the array into the allocated one
	else {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				test_1[i][j] = input1[i][j];
			}
		}
	}

	printIntMatrix(test_1, "This is your input matrix, " + name + "[" + std::to_string(rows) + "][" + std::to_string(cols) + "]", rows, cols);

	prepVerificationTest(test_1, name + " Test Case", rows, cols);

	std::cout << "Verifying algorithm..." << std::endl;
	bool results = verifyAlgo(0);

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
}

bool verifyAlgo(const int row) {
	for (int i = row; i < ROWS; i++) {
		int counter = 1;
		std::cout << "Processing P" << i << ":" << std::endl;

		for (int j = 0; j < COLS; j++) {
			std::cout << "Calculating event at [" << i << "][" << j << "] = " << input[i][j] << ":" << std::endl;

			//If the entry at the given row is 0, then skip this row entirely
			//This condition also serves to break recursion
			if (input[i][j] == 0) {
				std::cout << "Reached the end of process, proceeding to the next one...\n" << std::endl;
				break;
			}

			//If the entry was already processed from a prior run via recursion, then exit the function
			if (output[i][j] != "NULL") {
				if (output[i][j].at(0) == 's') {
					counter = input[i][j];
				}

				else {
					std::cout << "This event has already been processed. Returning from function...\n" << std::endl;
					return true;
				}
			}

			//Identified as potential internal event
			if (input[i][j] == counter) {
				//Reset ALPHA global to 'a' if I ran out of the alphabet
				if (ALPHA == '{') {
					ALPHA = 'a';
				}

				//If the event is NULL, then update it as an iternal event (otherwise it's a send event, so just skip it)
				if (output[i][j] == "NULL") {
					output[i][j] = ALPHA;
					std::cout << "Result: " << ALPHA << std::endl;
					ALPHA++;
				}

				counter++;
			}
			
			//Identified as a receive event due to sequential deviation
			else{
				std::cout << input[i][j] << " is suspected of being a receive event! Proceeding to the next row\n" << std::endl;
				//For now, let's deal with the receive event later and process the next row
				bool results = verifyAlgo(row + 1);

				//If the recursive run wasn't able to find a send event, return this function indicating that
				if (results == false) {
					return false;
				}

				//When the above function returns, start looking for potential sent event entries
				int max = input[i][j] - 1;
				std::cout << "Returning to P" << i << ":\nA search will be conducted for the max, " << max << ", within the input matrix" << std::endl;

				//Search for the potentials
				bool found = false;
				int sendEventNo = 0;

				for (int k = 0; k < ROWS; k++) {
					for (int l = 0; l < COLS; l++) {
						//Only deal with either send, internal or unprocessed events (NULLS)
						if (input[k][l] == max && !found && output[k][l].at(0) != 'r') {
							//Send event
							if (output[k][l].at(0) == 's') {
								sendEventNo = output[k][l].at(1) - 48;
								std::cout << "Duplicate receive event found. ";
							}

							//Internal event and NULLS
							else {
								output[k][l] = "s" + std::to_string(SEND_NO);
								sendEventNo = SEND_NO;
							}

							std::cout << "Result: output[" << k << "][" << l << "] = " << output[k][l];
							found = true;
						}
					}
				}

				//Once the search is complete, determine if a potential send event was found
				//If not, return the function and indicate that the input values are incorrect
				if (!found) {
					std::cout << "Search failed..." << std::endl;
					return false;
				}
				
				//If it has been found, associate the receive event with the send and perform the appropriate increments
				else {
					output[i][j] = "r" + std::to_string(sendEventNo);
					std::cout << " and output[" << i << "][" << j << "] = " << output[i][j] << std::endl;
					SEND_NO++;
					counter = input[i][j] + 1;
				}
			}
		}
	}

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