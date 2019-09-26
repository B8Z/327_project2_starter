/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 */

//============================================================================
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <array>
//#include "array_functions.h"
#include "constants.h"
#include "utilities.h"

//============================================================================

using namespace std;
using namespace constants;

//============================================================================
//	stuff you will need

struct entry {
	string word;
	int number_occurances;
};

struct entry textArray[MAX_WORDS];
int slot = 1;

//zero out array that tracks words and their occurrences
void clearArray() {
	for (int i = 0; i < slot; i++) {
		textArray[i].word = "";
		textArray[i].number_occurances = 0;
	}
}

//how many unique words are in array
int getArraySize() {
	return slot - 1;
}

//get data at a particular location
std::string getArrayWordAt(int i) {
	return textArray[i].word;
}
int getArrayWord_NumbOccur_At(int i) {
	return textArray[i].number_occurances;
}



/*loop through whole file, one line at a time
 * call processLine on each line
 * returns false: myfstream is not open
 *         true: otherwise*/
bool processFile(std::fstream &myfstream) {
	std::string myfile = "";

	myfstream.open(myfile.c_str(), ios::in);

	if (myfstream.is_open()) {
		while (getline(myfstream, myfile)) {
			processLine(myfile);
		}
		myfstream.close();
		return true;
	}
	return false;
}

/*take 1 line and extract all the tokens from it
 feed each token to processToken for recording*/
void processLine(std::string &myString) {
	for(int i=0; i<myString.length(); i++){
		processToken(myString[i]);
	}
}

/*Keep track of how many times each token seen*/
void processToken(std::string &token) {
	if(textArray[slot].word.compare(token) == 0){
		textArray[slot].number_occurances++;
	}
}

void extractTokensFromLine(std::string &myString) {

	stringstream ss(myString);

	string tempToken;

	while (getline(ss, tempToken, CHAR_TO_SEARCH_FOR)) {
		processToken(tempToken);
	}
}

/*if you are debugging the file must be in the project parent directory
 in this case Project2 with the .project and .cProject files*/
bool openFile(std::fstream &myfile, const std::string &myFileName,
		std::ios_base::openmode mode = std::ios_base::in) {
	myfile.open(myFileName, mode);
	bool open = true;
	if (!myfile.is_open() || myfile.fail()) {
		open = false;
	}
	return open;
}

/*iff myfile is open then close it*/
void closeFile(std::fstream &myfile) {
	if(myfile.is_open()){
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
	myOutputFile.open(outputfilename.c_str());

	//fixme


	myOutputFile.close();
}

/*
 * Sort myEntryArray based on so enum value.
 * You must provide a solution that handles alphabetic sorting (A-Z)
 * The presence of the enum implies a switch statement based on its value
 */
void sortArray(constants::sortOrder so) {

}
//============================================================================
//TODO define a structure to track words and number of times they occur

//TODO add a global array of entry structs (global to this file)

//TODO add variable to keep track of next available slot in array

//TODO define all functions in header file

//TODO look in utilities.h for useful functions, particularly strip_unwanted_chars!
