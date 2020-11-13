#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <vector>
using namespace std;

int getKey();
string getMessage();
void encryptMessage();
void decryptMessage();

int main()
{
	bool isRunning = true;
	while (isRunning) {		//menu loop
		cout << "Select one of the following \n 1) Encoding a message? \n 2) Decoding a message? \n 3) Exit" << endl;
		int menuInput;
		int key;
		string message;

		cin >> menuInput;

		if (menuInput == 1) {
			cin.clear();
			cin.ignore();
			encryptMessage();
		}
		else if (menuInput == 2) {
			cin.clear();
			cin.ignore();
			decryptMessage();
		}
		else if (menuInput == 3) {
			isRunning = false;
		}
		else {
			cin.clear();
			cin.ignore();
			cout << "Invalid menu entry. Enter a 1, 2, or 3" << endl;
		}
	}
}

int getKey()
{							//gets user inputted key
	int key;
	cout << "Enter an integer key: ";
	cin >> key;
	return key;
}

string getMessage()
{							//gets user inputted message
	string message;
	cout << "Enter a message: ";
	getline(cin, message);
	return message;
}

void encryptMessage()
{							 //encryption function
	bool isSymbol = false;
	char newChar;
	int calculation;
	int key;
	int numWrap;
	string temp;
	string message;
	vector<string> messageTokens;

	key = getKey(); //enter key value
	cin.clear();
	cin.ignore();
	message = getMessage(); //enter message

	while (key > 26) {	//reduces key if greater than 26
		key %= 26;
	}

	stringstream sstream(message);

	while (getline(sstream, temp, ' ')) { //tokenize the message
		messageTokens.push_back(temp);
	}

	size_t vectorSize = messageTokens.size();
	for (size_t i = 0; i < vectorSize; i++) { //loop for each word
		size_t tokenSize = messageTokens[i].size();
		for (size_t j = 0; j < tokenSize; j++) { //loop for each character
			char letter = messageTokens[i].at(j);
			int asciiDec = int(letter);

			if (asciiDec >= 65 && asciiDec <= 90) {	//convert uppercase letters
				calculation = asciiDec + key;
			}
			else if (asciiDec >= 97 && asciiDec <= 122) {	//convert lowercase letters
				calculation = asciiDec + key;
			}
			else {	//if character is a symbol
				isSymbol = true;
				calculation = asciiDec;
			}

			if (isSymbol == false) {	//checks if character is a symbol. verifies ascii does not exceed the range of alphabet
				if (calculation > 90 && calculation < 97) {// loop back to 'A' if character > 'Z'
					numWrap = calculation - 90;
					int startingPosition = 64; // 'A' =  65
					calculation = startingPosition + numWrap;
					newChar = calculation;
				}
				else if (calculation > 122 && calculation < 149) {// loop back to 'a' if character > 'z'
					numWrap = (calculation - 122) + 96; // 'a' = 97
					calculation = numWrap;
				}
				else {
					// do nothing
				}
			}
			newChar = calculation;
			messageTokens[i].at(j) = newChar;
			isSymbol = false;
		}
	}
	cout << "\nEncrypted message: ";
	vectorSize = messageTokens.size();
	for (size_t i = 0; i < vectorSize; i++) { // prints out the entire message
		cout << messageTokens[i] << " ";
	}
	cout << "\n";
}

void decryptMessage()
{							//decryption function
	bool isSymbol = false;
	char newChar;
	int key;
	int calculation;
	int letterCase = -1;	//0 = uppercase, 1 = lowercase
	int numWrap;
	string temp;
	string message;
	vector<string> messageTokens;

	key = getKey(); //enter key value
	cin.clear();
	cin.ignore();
	message = getMessage(); //enter message

	stringstream sstream(message);

	while (getline(sstream, temp, ' ')) {
		messageTokens.push_back(temp);
	}

	while (key > 26) {		//reduces key if greater than 26
		key %= 26;
	}

	size_t vectorSize = messageTokens.size();
	for (size_t i = 0; i < vectorSize; i++) { // loop for each word
		size_t tokenSize = messageTokens[i].size();
		for (size_t j = 0; j < tokenSize; j++) { // loop for each character
			char letter = messageTokens[i].at(j);
			int asciiDec = int(letter);
			char check = asciiDec;

			if (asciiDec >= 65 && asciiDec <= 90) { // convert uppercase letters
				calculation = asciiDec - key;
				letterCase = 0;
			}

			else if (asciiDec >= 97 && asciiDec <= 122) { //convert lowercase letters
				calculation = asciiDec - key;
				letterCase = 1;
			}
			else { //  if character is a symbol
				isSymbol = true;
				calculation = asciiDec;
			}

			if (isSymbol == false) {		//checks if character is a symbol. verifies ascii does not exceed the range of alphabet
				if (calculation > 38 && calculation < 65 && letterCase == 0) { // loop back to 'Z' if character < 'A'
					numWrap = 65 - calculation;
					int startPosition = 91; // 'Z' is 90
					calculation = startPosition - numWrap;
				}
				else if (calculation > 70 && calculation < 97 && letterCase == 1) { // loop back to 'z' if character < 'a'
					numWrap = 97 - calculation;
					int startPosition = 123; // 'z' is 122
					calculation = startPosition - numWrap;
				}
				else {
					// do nothing
				}
			}
			newChar = calculation;
			messageTokens[i].at(j) = newChar;
			isSymbol = false;
			letterCase = -1;
		}
	}
	cout << "\nDecrypted message: ";
	vectorSize = messageTokens.size();
	for (size_t i = 0; i < vectorSize; i++) { // prints out the entire message
		cout << messageTokens[i] << " ";
	}
	cout << "\n";
}