/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 26, 2019
 *      Author: Adam Bates
 */

//============================================================================
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include "constants.h"
#include "utilities.h"

//============================================================================

using namespace std;
using namespace constants;

//============================================================================

struct entry { //create structure to hold word and number of times it appears
	string word;
	int number_occurances;
};

struct entry textArray[MAX_WORDS];

int slot = 0; //store unique words in array

//zero out array that tracks words and their occurrences
void clearArray() {
	slot = 0;
}

//how many unique words are in array
int getArraySize() {
	return slot;
}

//get data at a particular location
//	stuff you will need
std::string getArrayWordAt(int i) {
	return textArray[i].word;
}
int getArrayWord_NumbOccur_At(int i) {
	return textArray[i].number_occurances;
}

/*Keep track of how many times each token seen*/
void processToken(std::string &token) {
	strip_unwanted_chars(token);
	bool sameWord = false; //different process if word is duplicate

	{
		if (!token.empty()) {
			for (int i = 0; i < getArraySize(); i++) { //loop through array
				string tmp = textArray[i].word; //store word
				string tmp2 = token; //store token

				toUpper(tmp);
				toUpper(tmp2);

				if (tmp == tmp2) { //if same word increment times seen
					textArray[i].number_occurances++;
					sameWord = true;
				}
			}
			if (!sameWord) { //if different word add entry
				entry addEntry = { token, 1 };
				textArray[slot] = addEntry;
				slot++;
			}

		}
	}
}

/*take 1 line and extract all the tokens from it
 feed each token to processToken for recording*/
void processLine(std::string &myString) {
	stringstream ss(myString);
	string tempToken;

	while (getline(ss, tempToken, CHAR_TO_SEARCH_FOR))
		processToken(tempToken);
}

/*loop through whole file, one line at a time
 * call processLine on each line
 * returns false: myfstream is not open
 *         true: otherwise*/
bool processFile(std::fstream &myfstream) {
	string myfile = ""; //string to hold value from myfstream

	if (myfstream.is_open()) {
		while (getline(myfstream, myfile)) {
			processLine(myfile);
		}
		myfstream.close();
		return true;
	}
	return false;
}

/*if you are debugging the file must be in the project parent directory
 in this case Project2 with the .project and .cProject files*/
bool openFile(std::fstream &myfile, const std::string &myFileName,
		std::ios_base::openmode mode = std::ios_base::in) {
	myfile.open(myFileName, mode);
	bool open = true;
	if (!myfile.is_open() || myfile.fail()) { //if file is closed or fails to open
		open = false; //return false
	}
	return open;
}

/*iff myfile is open then close it*/
void closeFile(std::fstream &myfile) {
	if (myfile.is_open()) {
		myfile.close();
	}
}

/* serializes all content in myEntryArray to file outputfilename
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writeArraytoFile(const std::string &outputfilename) {
	ofstream myOutputFile;
	myOutputFile.open(outputfilename.c_str()); //open file turn into constant string

	if (slot == 0) {
		return FAIL_NO_ARRAY_DATA; //if slot never increased return no array data constant
	} else {
		for (int i = 0; i < slot; i++) { //loop through array, write to file
			myOutputFile << textArray[i].word << " "
					<< textArray[i].number_occurances << endl;
		}

	}
	myOutputFile.close(); //close file and return success constant
	return SUCCESS;
}

/*
 * Sort myEntryArray based on so enum value.
 * You must provide a solution that handles alphabetic sorting (A-Z)
 * The presence of the enum implies a switch statement based on its value
 */
void sortArray(constants::sortOrder so) {
	switch (so) { //Switch statement to pass non-ascending cases
	case ASCENDING: {
		bool swaps = true; //value to ensure swaps are recorded
		while (swaps) {
			swaps = false;
			for (int i = 0; i < slot - 1; i++) { //loop through array
				string nextWord = textArray[i + 1].word; //keep track of next word
				string word = textArray[i].word; //keep track of current word

				toUpper(nextWord);
				toUpper(word);

				if (word > nextWord) { //if word comes after next word
					entry currentState = textArray[i]; //swap places
					textArray[i] = textArray[i + 1];
					textArray[i + 1] = currentState;
					swaps = true;
				}
			}
		}
	} //if other case, handled automatically
	}
}
