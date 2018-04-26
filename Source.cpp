//course: CS215-007
//Project: Programming Assignment 1
//Date: 10/04/2016
//Purpose: Plays the game of nim by asking for the pile size then takes turn with the user and computer(the computer will try to make the pile 2^n -1 size)
//and can only remove from the pile from 1 to half the pile size until the last marble is removed
//Author: Jared Rigdon

#include <iostream>
#include <string>
#include <random>
#include <stdlib.h>  
#include <time.h> 

using namespace std;
void pause_215(bool have_newline);
bool deadNum(int);
int compute(int);
//int comp_turn(int pile);
//int user_turn(int input, int pile);

//the main function will contain the openning and closing messages as well as asking the user for input for amount of pile size
int main()
{
	int take;
	//random seed
	srand(time(NULL));
	int pile;
	//int input;
	cout << "Welcome to the game of Nim.\nTo start, please enter a number greater than 10 to serve as\nthe max range of the pile size." << endl;

	//asks for input
	cin >> pile;

	//goes into a while loop if there was an input failure or if size is less than or equal to 10
	while (cin.fail() || pile <= 10) {
		cout << "Invalid input, please try again..." << endl;
		cout << "Welcome to the game of Nim.\nTo start, please enter a number greater than 10 to serve as\nthe max range of the pile size." << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> pile;
	}
	
	//generate a random pile size from 10 to the integer the user entered
	pile = rand() % (pile-10+1)+10;

	//generate a random number of either 0 or 1 to determine who goes first
	int turn = rand() % 2;
	
	//if the turn = 0 then the user goes first, else the computer does
	if (turn == 0) {
		cout << "You play first." << endl;
	}
	else {
		cout << "Computer goes first." << endl;
	}

	while (pile != 1) {
		cout << "The size of the pile is " << pile << endl;

		//if the turn = 0 then the user goes, else the computer does
		//user turn
		if (turn == 0) {
			//pile = user_turn(pile);
			int input;
			cout << "How many marbles would you like to remove?" << endl;
			cin >> input;
			//if input fails or is less than 1 or greater the half the pile repeatedly ask the user for valid input
			while (cin.fail() || input <=0 || input > (pile / 2)) {
				if (cin.fail()) {
					cout << "How many marbles would you like to remove?" << endl;
					cin.clear();
					cin.ignore(256, '\n');
				}
				else {
					cout << "Illegal move. You must remove at least 1 or at most half of\nthe marbles." << endl;
					cin.clear();
				}
				cin >> input;
			}
			//get the new pile size and return it to the main function
			pile -= input;
		}
		//computer turn
		else {
			if (deadNum(pile)) {
				take = 1 + rand() % (pile / 2);
				pile -= take;
				cout << "Computer removes " << take << " marbles." << endl;
				cout << "This size of the pile is " << pile << endl;
			}
			else {
				/* use the strategy */
				take = compute(pile);
				pile -= take;
				cout << "Computer removes " << take << " marbles." << endl;
				cout << "This size of the pile is " << pile << endl;
			}
		}
		//change the turn variable to switch between player and computer
		if (turn == 0) {
			turn = 1;
		}
		else {
			turn = 0;
		}
	}
	//determine the winner
	if (turn == 0) {
		cout << "You win." << endl;
	}
	else {
		cout << "The computer wins." << endl;
	}
	pause_215(true);
	return 0;
}

//return true if n is 1 less than any power of 2; return false otherwise
bool deadNum(int n) {
	int i = -1;
	while ((int)pow(2.0, ++i) < n)
		;
	return ((int)pow(2.0, i) == n + 1);
}

//return the number of marbles smart computer should draw
int compute(int n) {
	if (n == 2)
		return 1;
	int i = -1;
	while ((int)pow(2.0, ++i) < n)
		;
	i--;
	return n - ((int)pow(2.0, i) - 1);
}

void pause_215(bool have_newline)
{
	if (have_newline) {
		// Ignore the newline after the user's previous input.
		cin.ignore(256, '\n');
	}

	// Prompt for the user to press ENTER, then wait for a newline.
	cout << endl << "Press ENTER to continue." << endl;
	cin.ignore(256, '\n');
}