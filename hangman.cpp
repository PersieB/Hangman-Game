/*
 * File:   hangman.cpp
 * Author: Percy George Brown
 *
 * Created on 18 April 2020, 15:49
 */
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#define ASK_USER
#define ONE_AT_A_TIME
#define FINAL_RESULT

//forward declaration of functions

bool FinishGuess(string lucky_word, string guesses);
string GenerateRandom(string group_of_words[]);

const int MAX = 10; // The maximum number of times the game can be played.
const int word_size = 5;    //all words are 5 letter words

/*
*This function takes a string array of possible words to be guessed
*Generates and returns the random word
*/

string GenerateRandom(string group_of_words[]){
	int number_of_words = 10;
	int random_number = rand() % number_of_words;            //generates random number from 0 to 9
	string word_to_guess = group_of_words[random_number];    //Uses random number as index to generate random word
	return word_to_guess;
}

/*
*While the user enters each choice, it is important to keep track of them
*This function takes the word and all choices made so far as a string
*Checks whether or not the random word contains a choice or not
*When all choices have been checked, it returns true when the lucky word contains 5 of the potential 10 choices
*And returns false otherwise
*/

bool FinishGuess(string lucky_word, string choices_made){
	//For each letter guessed, check whether it is found in the random word
		for(int i = 0; i < word_size; i++){
			bool all_correct = false;
			for(int k = 0; k < MAX; k++){
				char each_letter = choices_made[k];     //each choice is a character
				if(lucky_word[i] == each_letter){        //compare each choice to see if it's in the word.
					all_correct = true;
					break;
				}
			}

			//if after all choices, 5 were not found in the word
			if(all_correct == false){
				return false;
			}
		}
		return true;


}

/*
*This function stimulates the hangman game
*User has 10 choices to guess a 5 letter word
*Programs ends and prints the random word if it's guessed in less than 10 attempts
*/

int main(){
	// string array of ten 5 letter words
	string five_letter_words[] = {"WATER", "GOOSE", "GRADE", "QUEEN", "TABLE", "RADIO", "PHONE", "BEARD", "NAIVE", "HOUSE"};
	string chosen = GenerateRandom(five_letter_words);         //random word generated
	string total_choices = "";                                     //to keep track of all choices at each attempt
	int attempts_taken = 0;                                        //attempts so far
	string choice;

	//Brief Hangman Game Descrition

	cout << "Welcome to Hangman" << endl;
	cout << "You have 10 attempts to guess a five letter word" << endl;
	cout << "The letters you guess right are separated by hyphens" << endl;
	cout << "To make it more fun and tricky, should you guess the last letter right at first..." << endl;
	cout << "Program still provides hyphen after the last letter to confuse the player" << endl;
	cout << "Aim is not to make the last letter obvious but make you think through well" << endl;
	cout <<"\n";
	cout << "**************************" << endl;

	/*
	*While the user is yet to completely guess the random word and still has attempts to do so
	*Prints the choice if found in word
	*Prints underscores between the letters
	*/

	while((FinishGuess(chosen,total_choices)== false) && (attempts_taken < MAX)){

		//checks each choice at a time

		#ifdef ONE_AT_A_TIME

			for(int i = 0; i < word_size; i++){
				bool GuessOne = false;
				for(int j = 0; j < MAX; j++){
					char one_choice = total_choices[j];
					if(chosen[i] == one_choice){                     //checks each choice at a time
						cout << chosen[i];							//prints choice if valid
						GuessOne = true;
						break;
					}
				}
				cout << "-";                     //hyphen between letters
			}

		#endif

	//asks user for choice and prints attempts left

	#ifdef ASK_USER

		cout << " | Attempts left: " << MAX - attempts_taken  << endl;          //attempts left
		cout << "Your choice: ";                                   //takes choice
		cin >> choice;
		transform(choice.begin(), choice.end(), choice.begin(), ::toupper);           //converts to uppercase
		total_choices+=choice;                        //keeps track of choices guessed at every attemt
		attempts_taken++;                              //adds one to attempts taken
		cout << "**************************" <<endl;

	#endif

	}

	/*
	*if at any stage, the right word has been guessed,
	*User is notified as a winner
	*And loser otherwise
	*/

	#ifdef FINAL_RESULT

	if(FinishGuess(chosen, total_choices) == true){          //if word guessed right
		cout << "The word was: " << chosen <<endl;
		cout << "Bravo! You won!" << endl;
	}
	else{                                              //wrong guess
		cout << "The word was: "<< chosen <<endl;
		cout << "You lost. Try again :)" << endl;
	}

	#endif

	return 0;
}



