/*
************************************************************
THE SNAKE GAME PROJECT

PF LAB PROJECT


DONE BY : Rohit Kumar 21f-9279 

************************************************************

*/


#include<iostream>
#include <conio.h>                                                     // It is used for kibhit function
#include<stdio.h>                                                    
#include<stdlib.h>                                                     // It is used for Rand function to genrate random number 
#include<windows.h>                                                    // it contains built in console display manipulating functions 
#include<fstream>
using namespace std;
bool gameover;
const int width = 100;                                                                        // these are constant variables for length and width of border of game .
const int height = 25;
int x, y, fruitX, fruitY, speed, flag, score;                                                  //here variables are x and y coordinates of snake , speed ,score 
int tailX[100], tailY[100];
int counttail;                                                                               // this is for tail of snake 

int bestscore;                                                                              //this is for saving bestscore 
void gotoxy(int x, int y)
{
	COORD coord;                                                                    //This is built in function of window.h it will reset cursor at 0,0 position
	coord.X = x;                                                                    // instead of using system cls we used this because system cls provide much flickering
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


// This is the first page of game 

void page1() {


	system("color 0a");                                            // this system colour will change the colour of screen and text 

	cout << endl << endl << endl << endl << "\t\t \t\t\t\tWELCOME TO THE GAME " << endl << endl;

	cout << endl << "\t\t\t\t\t\tPRESS ANY KEY TO START" << endl;

	cin.get();



}

// This function is to set levels in game 
void level() {



	//system("cls");
	system("color 0E");
	cout << endl << endl << endl << "\t\tEnter Number for level :" << endl << endl << endl << endl << endl;

	cout << "\t\t 1. level 1  :  10" << endl << endl;
	cout << "\t\t 2. level 2  :  20" << endl << endl;
	cout << "\t\t 3. level 3  :  30" << endl << endl;
	cout << "\t\t 4. level 4  :  40" << endl << endl;
	cout << "\t\t 5. level 5  :  50" << endl << endl;

	cin >> speed;

	if (speed < 1 || speed>5) {
		system("cls");
		cout << "wrong input please try again" << endl;
		level();

	}




	system("cls");
	system("color 0C");

}


// This is the initial setup of the game .
// It has the initial position of the snake head and initial position of fruit. 
void Setup() {
	gameover = false;



	x = width / 2;

	y = height / 2;

	fruitX = rand() % width;

	fruitY = rand() % height;
	score = 0;

}


// This the main interface of the game, where the snake will move.

void display_design() {

	gotoxy(0, 0);

	for (int i = 0; i < width + 2; i++)

		cout << "|";

	cout << endl;

	for (int i = 0; i < height; i++) {

		for (int j = 0; j < width; j++) {

			if (j == 0)

				cout << "|";

			if (i == y && j == x)

				cout << "S";

			else if (i == fruitY && j == fruitX)

				cout << "o";

			else {

				bool print = false;

				// The count tail variable is for length of snake

				for (int k = 0; k < counttail; k++) {

					if (tailX[k] == j && tailY[k] == i) {

						cout << "o"; print = true;

					}

				}

				if (!print) cout << " ";

			}

			if (j == width - 1)

				cout << "|";

		}

		cout << endl;

	}

	for (int i = 0; i < width + 2; i++)

		cout << "|";

	cout << endl;

	cout << "**************" << "\t\t\t\t******************" << "\t\t\t******************" << endl;
	cout << "Score:" << score << "      *" << "\t\t\t\tPRESS p FOR PAUSE" << "\t\t\tPRESS x FOR Exit" << endl;
	cout << "**************" << "\t\t\t\t******************" << "\t\t\t******************" << endl;


}


//This function will take the input from user  to move the snake in particular direction


void Input()
{

	// kbhit is a built in function it returns zero until a user presses a key. 

	if (_kbhit()) {

		switch (_getch()) {

		case 'a':

			flag = 1;

			break;

		case 'd':

			flag = 2;

			break;

		case 'w':

			flag = 3;

			break;

		case 's':

			flag = 4;

			break;

		case 'x':

			gameover = true;

			break;
		case 'p':
			system("pause");
			break;

		}

	}

}


// This function is used for movement of snake 


void movinglogic()
{

	int prevX = tailX[0];

	int prevY = tailY[0];

	int prev2X, prev2Y;

	tailX[0] = x;

	tailY[0] = y;

	//In this loop we are shifting the numbers in array to increase the length of the snake

	for (int i = 1; i < counttail; i++) {

		prev2X = tailX[i];

		prev2Y = tailY[i];

		tailX[i] = prevX;

		tailY[i] = prevY;

		prevX = prev2X;

		prevY = prev2Y;

	}

	switch (flag) {

	case 1:

		x = x - speed;

		break;

	case 2:

		x = x + speed;

		break;

	case 3:

		y = y - speed;

		break;

	case 4:

		y = y + speed;

		break;

	default:

		break;

	}
	if (x<0 || x>width || y<0 || y>height)
		gameover = 1;

	if (x >= width) x = 0; else if (x < 0) x = width - 1;

	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < counttail; i++)

		if (tailX[i] == x && tailY[i] == y)
			gameover = true;

	if (x == fruitX && y == fruitY) {

		score += 10;

		fruitX = rand() % width;

		fruitY = rand() % height;

		counttail++;

	}

}

// This is to store the highest score 
void highscore() {

	score = bestscore;
	ifstream input("highest score.txt", ios::in);

	if (!input.is_open())
		cout << "the file is not opened";
	input >> bestscore;

	ofstream output("highest score.txt");

	if (score < bestscore) {

		output << score;
	}
	else {
		output << bestscore;
	}

	input.close();
	output.close();

}


// This function is used to  run the game 
void game() {
	system("cls");
	level();
	Setup();

	while (!gameover) {

		display_design();

		Input();

		movinglogic();

	}
}


// THis function is used to show the main menu page to user.
void mainmenu() {

	int choice;
	system("cls");
	system("color 0C");
	cout << endl << endl << "\t\t\t\t WELCOME TO MAIN MENU :" << endl << endl << endl << endl;

	cout << "\t\t\t\t 1. PLAY GAME  " << endl << endl;
	cout << "\t\t\t\t 2. HOW TO PLAY " << endl << endl;
	cout << "\t\t\t\t 3. HIGHEST SCORE " << endl << endl;
	cout << "\t\t\t\t 4. EXIT " << endl;

	cin >> choice;

	if (choice == 1) {
		game();

	}
	else if (choice == 2) {
		system("cls");

		system("color 09");

		cout << endl << endl << endl << endl << "\t\t \t\t HOW TO PLAY " << endl << endl << endl;

		cout << "\t\t \t\tPRESS W TO MOVE SNAKE UP" << endl << endl;
		cout << "\t\t \t\tPRESS S TO MOVE SNAKE DOWN" << endl << endl;
		cout << "\t\t \t\tPRESS S TO MOVE SNAKE LEFT " << endl << endl;
		cout << "\t\t \t\t PRESS D TO MOVE SNAKE RIGHT" << endl << endl << endl;

		cout << "\t\t \t\tIf you hit the Wall the Game will be over " << endl << endl << endl;

		cout << "\t\t \t\t PRESS ANY KEY  TO BACK TO MAIN MENU " << endl;

		cin.get();
		mainmenu();
	}
	else if (choice == 3) {
		highscore();
		cout << endl << endl << "THE BEST SCORE IS : " << bestscore;

	}
	else if (choice == 4) {
		system("color 0A");
		cout << "THE GAME IS EXITED";

		gameover = 1;
	}

}

int main()
{



	page1();
	mainmenu();

	if (gameover == true) {
		system("cls");
		char ch;
		cout << "\tDo you want to continue game press y to continue and n to exit" << endl;
		cin >> ch;

		if (ch == 'y')
			mainmenu();
		else
		{
			cout << "\tThe game is exited";
			return 0;


		}

	}

	return 0;

}