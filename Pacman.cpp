#include <iostream>
#include <cstdlib> // for system("cls") or system("clear")
#include <conio.h> // for _getch() in Windows
#include <sstream> // string stream prints the maze quickly
#include <time.h>  // for srand

using namespace std;

int print_maze();
int print_maze2();
int print_maze3();
void player_movement(char playerDirection);
void player_movement2(char player_direction);
int move_horizontal(int col, int mov);
int move_vertical(int row, int mov);
void ghost_movement(int g1, int g2, int g3, int g4);
void ghost_movement23(int g1, int g2, int g3, int g4);
void ghost_movement1();
void ghost_movement2();
void ghost_movement3();
void level1();
void level2();
void level3();
void pacman_reset();
void pacman_reset2();
void game_reset();
void game_reset2();
void game_reset3();
int pellet_detected();
int pellet_detected2();
void game_over();

// global player position
int player_row = 17;
int player_col = 22;

// global player position for portal
int pr = 14;
int pc1 = 0;
int pc2 = 43;

// global ghosts positions
int ghosts[4][2] = { {20, 33}, {8, 9}, {20,7}, {11, 23} };

int row_g1 = 8;  // 7 (top left)
int col_g1 = 9;

int row_g2 = 20; // 8 (bottom left)
int col_g2 = 7;

int row_g3 = 20; // 4 (bottom right)
int col_g3 = 33;

int row_g4 = 11; // 9 (middle)
int col_g4 = 23;

// global game states
int score = 0;
int lives = 3;
int pellets_remaining = 432;

/////////////////////////////////////////// MUSKAN PART 1 ///////////////////////////////////////////

const int ROWS = 31;
const int COLS = 44;

int maze[ROWS][COLS] =
{
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,5,1,0,0,0,0,0,1,2,1,0,0,0,0,0,0,0,0,1,2,1,1,2,1,0,0,0,0,0,0,0,0,1,2,1,0,0,0,0,0,1,5,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,2,2,2,2,2,2,2,2,7,1,1,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,2,9,2,2,2,2,2,2,2,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,1,1,2,1,1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,1,2,1,1,1,1,1,1,1,1,1 },
	{ 2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2 },
	{ 1,1,1,1,1,1,1,1,1,2,1,1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,1,2,1,1,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,6,2,2,2,2,2,2,2,2,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1 },
	{ 1,2,2,2,2,2,2,8,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,5,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,5,1 },
	{ 1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1 },
	{ 1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
};

int maze2[ROWS][COLS] =
{
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,5,1,0,0,0,0,0,1,2,1,0,0,0,0,0,0,0,0,1,2,1,1,2,1,0,0,0,0,0,0,0,0,1,2,1,0,0,0,0,0,1,5,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1 },
	{ 1,2,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,2,1 },
	{ 1,2,2,2,2,2,2,2,2,7,1,1,2,2,1,2,2,2,2,2,2,1,1,2,2,2,2,2,2,1,2,2,1,1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,2,9,2,2,2,2,2,2,2,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,1,1,2,1,1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,1,2,1,1,1,1,1,1,1,1,1 },
	{ 2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2 },
	{ 1,1,1,1,1,1,1,1,1,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,1,1,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,6,2,2,2,2,2,2,2,2,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1 },
	{ 1,2,2,2,1,2,2,8,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,1,2,2,2,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,5,2,2,2,2,2,1,1,2,2,2,2,2,1,2,2,2,2,2,2,1,1,2,2,2,2,2,2,1,2,2,2,2,2,1,1,2,2,2,2,2,5,1 },
	{ 1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1 },
	{ 1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
};


// change to a different level here!
int main()
{
	srand(time(NULL)); // seeds random values for every different code run, instead of generating the same random values for each run

	/////////////////////////////////////////// DANYAH PART 1 ///////////////////////////////////////////

	int choice;
	do {

		system("Color 06");

		cout << "======================================================================================================================================================== =" << endl;
		cout << " || 00000000000000         0              00000000            0               0            0           0          00000000           0000000000000      ||" << endl;
		cout << " || 0000000000000000      000           000000000000          000           000           000          000        00000000         00000000000000000    ||" << endl;
		cout << " || 00000000000000000    00000        000000000000000         0000         0000          00000         00000      00000000        0000000000000000000   ||" << endl;
		cout << " || 0000000 0000000000  0000000      0000000000000            00000       00000         0000000        000000     00000000       00000   00000   00000  ||" << endl;
		cout << " || 00000000000000000  000000000    00000000000               000000     000000        000000000       00000000   00000000      00000   o 000   o 00000 ||" << endl;
		cout << " || 000000000000000   00000 00000   000000000          00000  0000000   0000000       00000 00000      000000000  00000000      000000   00000   000000 ||" << endl;
		cout << " || 000000000000     0000000000000  00000000000        00000  00000000 00000000      0000000000000     0000000000 00000000      00000000000000000000000 ||" << endl;
		cout << " || 00000           000000000000000  0000000000000            00000000000000000     000000000000000    0000000000000000000      00000000000000000000000 ||" << endl;
		cout << " || 00000          00000000000000000  000000000000000         00000000000000000    00000000000000000   0000000000000000000      00000000000000000000000 ||" << endl;
		cout << " || 00000         0000000000000000000   000000000000          00000000000000000   0000000000000000000  0000000000000000000      000 0000000 0000000 000 ||" << endl;
		cout << " || 00000        000000000000000000000    00000000            00000000000000000  000000000000000000000 0000000000000000000      00   00000   00000   00 ||" << endl;
		cout << "======================================================================================================================================================== =" << endl;
		cout << endl;

		cout << "\n\n\n\n\n\t\t\t\t\t\t\t\t WELCOME TO PACMAN! :)" << endl;
		cout << "\n\n\t\t\t\t\t\t  Press '1' and then 'Enter' to READ THE INSTRUCTONS" << endl;
		cout << "\t\t\t\t\t\t  Press '2' and then 'Enter' to START THE GAME" << endl;
		cin >> choice;


		system("cls");

		if (choice == 1) {
			system("Color 09");
			cout << "\n\n\n\n\n\n\n\n\t\tINSTRUCTIONS: " << endl;
			cout << "\t\t\t\tPress 'w' to move Up     ^" << endl;
			cout << "\t\t\t\tPress 'a' to move Left   <" << endl;
			cout << "\t\t\t\tPress 's' to move Down   v" << endl;
			cout << "\t\t\t\tPress 'd' to move Right  >" << endl;

			cout << "\033[32m" << "\n\t\t\t\tPress any key to go back!" << endl;
			_getch();          // we need the player to press "any" key, we dont need a variable to store that key

			system("cls");
		}
	} while (choice == 1);

	if (choice == 2)
	{
		// you can comment out a level depending on which one you want to play
		level1();
		level2();
		level3();
	}
}

/////////////////////////////////////////// MUSKAN PART 2 ///////////////////////////////////////////

int print_maze()
{
	int pellets_remaining = 0;

	stringstream maze_stream;

	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			switch (maze[r][c])
			{
				// blank spaces = 0
				// walls = 1
				// pellets = 2
				// gates = 3
				// ghosts = 4, 7, 8, 9
				// power ups = 5
				// player = 6
			case 0:
				maze_stream << " ";
				break;
			case 1:
				maze_stream << "\x1b[34m#\x1b[0m";
				break;
			case 2:
				maze_stream << "\x1b[37m.\x1b[0m";
				pellets_remaining++;
				break;
			case 3:
				maze_stream << "\x1b[36m=\x1b[0m";
				break;
			case 4:
				maze_stream << "\x1b[31mG\x1b[0m";
				break;
			case 5:
				maze_stream << "\x1b[37mo\x1b[0m";
				break;
			case 6:
				maze_stream << "\x1b[33mP\x1b[0m";
				break;
			case 7:
				maze_stream << "\x1b[31mG\x1b[0m";
				break;
			case 8:
				maze_stream << "\x1b[31mG\x1b[0m";
				break;
			case 9:
				maze_stream << "\x1b[31mG\x1b[0m";
				break;
			default:
				break;
			}

			maze_stream << " ";
		}
		maze_stream << "\n";
	}

	// output the entire maze at once
	cout << maze_stream.str();

	return pellets_remaining;
}

/////////////////////////////////////////// EMAN ///////////////////////////////////////////

void player_movement(char player_direction)
{
	switch (player_direction)
	{
	case 'w':
		// move up
		if ((maze[player_row - 1][player_col] != 1) && (maze[player_row - 1][player_col] != 4) && (maze[player_row - 1][player_col] != 7) && (maze[player_row - 1][player_col] != 8) && (maze[player_row - 1][player_col] != 9)) {
			maze[player_row][player_col] = 0;      // clear the current player position
			player_row--;                         // move the player up one row
		}
		else if ((maze[player_row - 1][player_col] == 4) || (maze[player_row - 1][player_col] == 7) || (maze[player_row - 1][player_col] == 8) || (maze[player_row - 1][player_col] == 9)) {
			cout << "\a";
			lives--;
			pacman_reset();
		}
		break;
	case 's':
		// move down
		if ((maze[player_row + 1][player_col] != 1) && (maze[player_row + 1][player_col] != 4) && (maze[player_row + 1][player_col] != 7) && (maze[player_row + 1][player_col] != 8) && (maze[player_row + 1][player_col] != 9)) {
			maze[player_row][player_col] = 0;
			player_row++;
		}
		else if ((maze[player_row + 1][player_col] == 4) || (maze[player_row + 1][player_col] == 7) || (maze[player_row + 1][player_col] == 8) || (maze[player_row + 1][player_col] == 9)) {
			cout << "\a";
			lives--;
			pacman_reset();
		}
		break;
	case 'a':
		// move left
		if ((maze[player_row][player_col - 1] != 1) && (maze[player_row][player_col - 1] != 4) && (maze[player_row][player_col - 1] != 7) && (maze[player_row][player_col - 1] != 8) && (maze[player_row][player_col - 1] != 9)) {
			if ((player_row == pr) && (player_col - 1 == pc1)) { 	             // portal transition
				maze[player_row][player_col] = 0;                              // first column to last column
				player_row = pr;
				player_col = pc2;
			}
			else {
				maze[player_row][player_col] = 0;
				player_col--;
			}
		}
		else if ((maze[player_row][player_col - 1] == 4) || (maze[player_row][player_col - 1] == 7) || (maze[player_row][player_col - 1] == 8) || (maze[player_row][player_col - 1] == 9)) {
			cout << "\a";
			lives--;
			pacman_reset();
		}
		break;
	case 'd':
		// move right
		if ((maze[player_row][player_col + 1] != 1) && (maze[player_row][player_col + 1] != 4) && (maze[player_row][player_col + 1] != 7) && (maze[player_row][player_col + 1] != 8) && (maze[player_row][player_col + 1] != 9)) {
			if ((player_row == pr) && (player_col + 1 == pc2)) { 	             // portal transition
				maze[player_row][player_col] = 0;                              // last column to first column
				player_row = pr;
				player_col = pc1;
			}
			else {
				maze[player_row][player_col] = 0;		// former position = empty
				player_col++;						// move in some direction
			}
		}
		else if ((maze[player_row][player_col + 1] == 4) || (maze[player_row][player_col + 1] == 7) || (maze[player_row][player_col + 1] == 8) || (maze[player_row][player_col + 1] == 9)) {
			cout << "\a";
			lives--;
			pacman_reset();
		}
		break;
	case 'q':
		// quit game
		cout << "Quitting The Game!" << endl;
		break;
	default:
		cout << "Invalid Input";
		exit(0);
		break;
	}

	pellet_detected();
	maze[player_row][player_col] = 6;      // set the new player position in the maze
}

void player_movement2(char player_direction)
{
	switch (player_direction)
	{
	case 'w':
		// move up
		if ((maze2[player_row - 1][player_col] != 1) && (maze2[player_row - 1][player_col] != 4) && (maze2[player_row - 1][player_col] != 7) && (maze2[player_row - 1][player_col] != 8) && (maze2[player_row - 1][player_col] != 9)) {
			maze2[player_row][player_col] = 0;      // clear the current player position
			player_row--;                           // move the player up one row
		}
		else if ((maze2[player_row - 1][player_col] == 4) || (maze2[player_row - 1][player_col] == 7) || (maze2[player_row - 1][player_col] == 8) || (maze2[player_row - 1][player_col] == 9)) {
			cout << "\a";
			lives--;
			pacman_reset2();
		}
		break;
	case 's':
		// move down
		if ((maze2[player_row + 1][player_col] != 1) && (maze2[player_row + 1][player_col] != 4) && (maze2[player_row + 1][player_col] != 7) && (maze2[player_row + 1][player_col] != 8) && (maze2[player_row + 1][player_col] != 9)) {
			maze2[player_row][player_col] = 0;
			player_row++;
		}
		else if ((maze2[player_row + 1][player_col] == 4) || (maze2[player_row + 1][player_col] == 7) || (maze2[player_row + 1][player_col] == 8) || (maze2[player_row + 1][player_col] == 9)) {
			cout << "\a";
			lives--;
			pacman_reset2();
		}
		break;
	case 'a':
		// move left
		if ((maze2[player_row][player_col - 1] != 1) && (maze2[player_row][player_col - 1] != 4) && (maze2[player_row][player_col - 1] != 7) && (maze2[player_row][player_col - 1] != 8) && (maze2[player_row][player_col - 1] != 9)) {
			if ((player_row == pr) && (player_col - 1 == pc1)) { 	             // portal transition
				maze2[player_row][player_col] = 0;                               // first column to last column
				player_row = pr;
				player_col = pc2;
			}
			else {
				maze2[player_row][player_col] = 0;
				player_col--;
			}
		}
		else if ((maze2[player_row][player_col - 1] == 4) || (maze2[player_row][player_col - 1] == 7) || (maze2[player_row][player_col - 1] == 8) || (maze2[player_row][player_col - 1] == 9)) {
			cout << "\a";
			lives--;
			pacman_reset2();
		}
		break;
	case 'd':
		// move right
		if ((maze2[player_row][player_col + 1] != 1) && (maze2[player_row][player_col + 1] != 4) && (maze2[player_row][player_col + 1] != 7) && (maze2[player_row][player_col + 1] != 8) && (maze2[player_row][player_col + 1] != 9)) {
			if ((player_row == pr) && (player_col + 1 == pc2)) { 	             // portal transition
				maze2[player_row][player_col] = 0;                               // last column to first column
				player_row = pr;
				player_col = pc1;
			}
			else {
				maze2[player_row][player_col] = 0;		// former position = empty
				player_col++;					     	// move in some direction
			}
		}
		else if ((maze2[player_row][player_col + 1] == 4) || (maze2[player_row][player_col + 1] == 7) || (maze2[player_row][player_col + 1] == 8) || (maze2[player_row][player_col + 1] == 9)) {
			cout << "\a";
			lives--;
			pacman_reset2();
		}
		break;
	case 'q':
		// quit game
		cout << "Quitting The Game!" << endl;
		break;
	default:
		cout << "Invalid Input";
		exit(0);
		break;
	}

	pellet_detected2();
	maze2[player_row][player_col] = 6;      // set the new player position in the maze2
}

/////////////////////////////////////////// ANAYA ///////////////////////////////////////////

// Movement Functions

int move_horizontal(int col, int mov) {
	if (mov == 1) {
		// move right
		col++;
		return col;
	}
	else {
		// move left
		col--;
		return col;
	}
}

int move_vertical(int row, int mov) {
	if (mov == 3) {
		// move up
		row++;
	}
	else {
		// move down
		row--;
	}
	return row;
}

// Random + Chase Behaviour

void ghost_movement(int g1, int g2, int g3, int g4) {

	// move g1
	if (g1 == 1 || g1 == 2) {
		// 1 right, 2 left
		int new_col = move_horizontal(col_g1, g1);
		if (maze[row_g1][new_col] != 1) {
			int temp = maze[row_g1][new_col];
			if (maze[row_g1][new_col] != 6)
			{
				maze[row_g1][new_col] = maze[row_g1][col_g1];
				maze[row_g1][col_g1] = temp;
				col_g1 = new_col;
			}
		}
	}
	else {
		// 3 up, 4 down
		int new_row = move_vertical(row_g1, g1);
		if (maze[new_row][col_g1] != 1) {
			int temp = maze[new_row][col_g1];
			if (maze[new_row][col_g1] != 6)
			{
				maze[new_row][col_g1] = maze[row_g1][col_g1];
				maze[row_g1][col_g1] = temp;
				row_g1 = new_row;
			}
		}
	}


	// move g2
	if (g2 == 1 || g2 == 2) { // 1 right, 2 left
		int new_col = move_horizontal(col_g2, g2);
		if (maze[row_g2][new_col] != 1) {
			int temp = maze[row_g2][new_col];
			if (maze[row_g2][new_col] != 6)
			{
				maze[row_g2][new_col] = maze[row_g2][col_g2];
				maze[row_g2][col_g2] = temp;
				col_g2 = new_col;
			}
		}
	}
	else { // 3 up, 4 down
		int new_row = move_vertical(row_g2, g2);
		if (maze[new_row][col_g2] != 1) {
			int temp = maze[new_row][col_g2];
			if (maze[new_row][col_g2] != 6)
			{
				maze[new_row][col_g2] = maze[row_g2][col_g2];
				maze[row_g2][col_g2] = temp;
				row_g2 = new_row;
			}
		}
	}


	// move g3
	if (g3 == 1 || g3 == 2) { // 1 right, 2 left
		int new_col = move_horizontal(col_g3, g3);
		if (maze[row_g3][new_col] != 1) {
			int temp = maze[row_g3][new_col];
			if (maze[row_g3][new_col] != 6)
			{
				maze[row_g3][new_col] = maze[row_g3][col_g3];
				maze[row_g3][col_g3] = temp;
				col_g3 = new_col;
			}
		}
	}
	else { // 3 up, 4 down
		int new_row = move_vertical(row_g3, g3);
		if (maze[new_row][col_g3] != 1) {
			int temp = maze[new_row][col_g3];
			if (maze[new_row][col_g3] != 6)
			{
				maze[new_row][col_g3] = maze[row_g3][col_g3];
				maze[row_g3][col_g3] = temp;
				row_g3 = new_row;
			}
		}
	}

	// move g4
	if (g4 == 1 || g4 == 2) { // 1 right, 2 left
		int new_col = move_horizontal(col_g4, g4);
		if (maze[row_g4][new_col] != 1) {
			int temp = maze[row_g4][new_col];
			if (maze[row_g4][new_col] != 6)
			{
				maze[row_g4][new_col] = maze[row_g4][col_g4];
				maze[row_g4][col_g4] = temp;
				col_g4 = new_col;
			}
		}
	}
	else { // 3 up, 4 down
		int new_row = move_vertical(row_g4, g4);
		if (maze[new_row][col_g4] != 1) {
			int temp = maze[new_row][col_g4];
			if (maze[new_row][col_g4] != 6)
			{
				maze[new_row][col_g4] = maze[row_g4][col_g4];
				maze[row_g4][col_g4] = temp;
				row_g4 = new_row;
			}
		}
	}
}

// move until hits wall
//
//bool can_move(int row, int col, int direction) {
//	if (direction == 1 && maze[row][col + 1] != 1) {
//		return true;
//	}
//	else if (direction == 2 && maze[row][col - 1] != 1) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}

void ghost_movement23(int g1, int g2, int g3, int g4) {

	// move g1
	if (g1 == 1 || g1 == 2) {
		// 1 right, 2 left
		int new_col = move_horizontal(col_g1, g1);
		if (maze2[row_g1][new_col] != 1) {
			int temp = maze2[row_g1][new_col];
			if (maze2[row_g1][new_col] != 6)
			{
				maze2[row_g1][new_col] = maze2[row_g1][col_g1];
				maze2[row_g1][col_g1] = temp;
				col_g1 = new_col;
			}
		}
	}
	else {
		// 3 up, 4 down
		int new_row = move_vertical(row_g1, g1);
		if (maze2[new_row][col_g1] != 1) {
			int temp = maze2[new_row][col_g1];
			if (maze2[new_row][col_g1] != 6)
			{
				maze2[new_row][col_g1] = maze2[row_g1][col_g1];
				maze2[row_g1][col_g1] = temp;
				row_g1 = new_row;
			}
		}
	}


	// move g2
	if (g2 == 1 || g2 == 2) { // 1 right, 2 left
		int new_col = move_horizontal(col_g2, g2);
		if (maze2[row_g2][new_col] != 1) {
			int temp = maze2[row_g2][new_col];
			if (maze2[row_g2][new_col] != 6)
			{
				maze2[row_g2][new_col] = maze2[row_g2][col_g2];
				maze2[row_g2][col_g2] = temp;
				col_g2 = new_col;
			}
		}
	}
	else { // 3 up, 4 down
		int new_row = move_vertical(row_g2, g2);
		if (maze2[new_row][col_g2] != 1) {
			int temp = maze2[new_row][col_g2];
			if (maze2[new_row][col_g2] != 6)
			{
				maze2[new_row][col_g2] = maze2[row_g2][col_g2];
				maze2[row_g2][col_g2] = temp;
				row_g2 = new_row;
			}
		}
	}


	// move g3
	if (g3 == 1 || g3 == 2) { // 1 right, 2 left
		int new_col = move_horizontal(col_g3, g3);
		if (maze2[row_g3][new_col] != 1) {
			int temp = maze2[row_g3][new_col];
			if (maze2[row_g3][new_col] != 6)
			{
				maze2[row_g3][new_col] = maze2[row_g3][col_g3];
				maze2[row_g3][col_g3] = temp;
				col_g3 = new_col;
			}
		}
	}
	else { // 3 up, 4 down
		int new_row = move_vertical(row_g3, g3);
		if (maze2[new_row][col_g3] != 1) {
			int temp = maze2[new_row][col_g3];
			if (maze2[new_row][col_g3] != 6)
			{
				maze2[new_row][col_g3] = maze2[row_g3][col_g3];
				maze2[row_g3][col_g3] = temp;
				row_g3 = new_row;
			}
		}
	}

	// move g4
	if (g4 == 1 || g4 == 2) { // 1 right, 2 left
		int new_col = move_horizontal(col_g4, g4);
		if (maze2[row_g4][new_col] != 1) {
			int temp = maze2[row_g4][new_col];
			if (maze2[row_g4][new_col] != 6)
			{
				maze2[row_g4][new_col] = maze2[row_g4][col_g4];
				maze2[row_g4][col_g4] = temp;
				col_g4 = new_col;
			}
		}
	}
	else { // 3 up, 4 down
		int new_row = move_vertical(row_g4, g4);
		if (maze2[new_row][col_g4] != 1) {
			int temp = maze2[new_row][col_g4];
			if (maze2[new_row][col_g4] != 6)
			{
				maze2[new_row][col_g4] = maze2[row_g4][col_g4];
				maze2[row_g4][col_g4] = temp;
				row_g4 = new_row;
			}
		}
	}
}


////////// LEVEL 1 //////////

void ghost_movement1() {

	int g1 = rand() % 4 + 1;
	int g2 = rand() % 4 + 1;
	int g3 = rand() % 4 + 1;
	int g4 = rand() % 4 + 1;

	ghost_movement(g1, g2, g3, g4);
}

////////// LEVEL 2 //////////

void ghost_movement2() {

	int g1 = rand() % 4 + 1;
	int g2 = rand() % 4 + 1;
	int g3 = rand() % 4 + 1;
	int g4 = rand() % 4 + 1;


	if (row_g1 == player_row) { // check row
		if (player_col > col_g1) {
			g1 = 1; // move right
		}
		else {
			g1 = 2; // move left
		}
	}
	else if (col_g1 == player_col) { // check col
		if (player_row > row_g1) {
			g1 = 3; // move up
		}
		else {
			g1 = 4; // move down
		}
	}

	if (row_g2 == player_row) { // check row
		if (player_col > col_g2) {
			g2 = 1; // move right
		}
		else {
			g2 = 2; // move left
		}
	}
	else if (col_g2 == player_col) { // check col
		if (player_row > row_g2) {
			g2 = 3; // move up
		}
		else {
			g2 = 4; // move down
		}
	}

	ghost_movement23(g1, g2, g3, g4);

}

////////// LEVEL 3 //////////

void ghost_movement3() {

	int g1 = rand() % 4 + 1;
	int g2 = rand() % 4 + 1;
	int g3 = rand() % 4 + 1;
	int g4 = rand() % 4 + 1;


	if (row_g1 == player_row) { // check row
		if (player_col > col_g1) {
			g1 = 1; // move right
		}
		else {
			g1 = 2; // move left
		}
	}
	else if (col_g1 == player_col) { // check col
		if (player_row > row_g1) {
			g1 = 3; // move up
		}
		else {
			g1 = 4; // move down
		}
	}

	if (row_g2 == player_row) { // check row
		if (player_col > col_g2) {
			g2 = 1; // move right
		}
		else {
			g2 = 2; // move left
		}
	}
	else if (col_g2 == player_col) { // check col
		if (player_row > row_g2) {
			g2 = 3; // move up
		}
		else {
			g2 = 4; // move down
		}
	}

	if (row_g3 == player_row) { // check row
		if (player_col > col_g3) {
			g3 = 1; // move right
		}
		else {
			g3 = 2; // move left
		}
	}
	else if (col_g3 == player_col) { // check col
		if (player_row > row_g3) {
			g3 = 3; // move up
		}
		else {
			g3 = 4; // move down
		}
	}

	if (row_g4 == player_row) { // check row
		if (player_col > col_g4) {
			g4 = 1; // move right
		}
		else {
			g4 = 2; // move left
		}
	}
	else if (col_g4 == player_col) { // check col
		if (player_row > row_g4) {
			g4 = 3; // move up
		}
		else {
			g4 = 4; // move down
		}
	}

	ghost_movement23(g1, g2, g3, g4);

}

/////////////////////////////////////////// MUSKAN PART 3 ///////////////////////////////////////////

int print_maze2()
{
	pellets_remaining = 0;

	stringstream maze_stream;

	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			switch (maze2[r][c])
			{
			case 0:
				maze_stream << " ";
				break;
			case 1:
				maze_stream << "\x1b[35m#\x1b[0m";
				break;
			case 2:
				maze_stream << "\x1b[37m.\x1b[0m";
				pellets_remaining++;
				break;
			case 3:
				maze_stream << "\x1b[105m=\x1b[0m";
				break;
			case 4:
				maze_stream << "\x1b[31mG\x1b[0m";
				break;
			case 5:
				maze_stream << "\x1b[37mo\x1b[0m";
				break;
			case 6:
				maze_stream << "\x1b[33mP\x1b[0m";
				break;
			case 7:
				maze_stream << "\x1b[31mG\x1b[0m";
				break;
			case 8:
				maze_stream << "\x1b[31mG\x1b[0m";
				break;
			case 9:
				maze_stream << "\x1b[31mG\x1b[0m";
				break;
			default:
				break;
			}

			maze_stream << " ";
		}
		maze_stream << "\n";

	}
	// output the entire maze at once
	cout << maze_stream.str();

	return pellets_remaining;
}

int print_maze3()
{
	pellets_remaining = 0;

	stringstream maze_stream;

	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			switch (maze2[r][c])
			{
				// blank spaces = 0
				// walls = 1
				// pellets = 2
				// gates = 3
				// ghosts = 4, 7, 8, 9
				// power ups = 5
				// player = 6
			case 0:
				maze_stream << " ";
				break;
			case 1:
				maze_stream << "\x1b[31m#\x1b[0m";
				break;
			case 2:
				maze_stream << "\x1b[37m.\x1b[0m";
				pellets_remaining++;
				break;
			case 3:
				maze_stream << "\x1b[105m=\x1b[0m";
				break;
			case 4:
				maze_stream << "\x1b[32mG\x1b[0m";
				break;
			case 5:
				maze_stream << "\x1b[37mo\x1b[0m";
				break;
			case 6:
				maze_stream << "\x1b[33mP\x1b[0m";
				break;
			case 7:
				maze_stream << "\x1b[32mG\x1b[0m";
				break;
			case 8:
				maze_stream << "\x1b[32mG\x1b[0m";
				break;
			case 9:
				maze_stream << "\x1b[32mG\x1b[0m";
				break;
			default:
				break;
			}

			maze_stream << " ";
		}
		maze_stream << "\n";
	}

	// output the entire maze at once
	cout << maze_stream.str();

	return pellets_remaining;
}

/////////////////////////////////////////// DANYAH PART 2 ///////////////////////////////////////////

int pellet_detected()       // to record scores
{
	if (maze[player_row][player_col] == 2)
		score += 10;
	if (maze[player_row][player_col] == 5)
		score += 50;

	return score;
}

int pellet_detected2()       // to record scores
{
	if (maze2[player_row][player_col] == 2)
		score += 10;
	if (maze2[player_row][player_col] == 5)
		score += 50;

	return score;
}


void pacman_reset()
{
	maze[player_row][player_col] = 0;
	maze[17][22] = 6;
	player_row = 17;         // reset player position
	player_col = 22;
}

void pacman_reset2()
{
	maze2[player_row][player_col] = 0;
	maze2[17][22] = 6;
	player_row = 17;         // reset player position
	player_col = 22;
}


void game_reset()
{   // to reset the initial state of ghosts and maze
	score = 0;
	lives = 3;
	player_row = 17;
	player_col = 22;

	ghosts[0][0] = 20;
	ghosts[0][1] = 33;
	ghosts[1][0] = 8;
	ghosts[1][1] = 9;
	ghosts[2][0] = 20;
	ghosts[2][1] = 7;
	ghosts[3][0] = 11;
	ghosts[3][1] = 23;

	row_g1 = 8;  // 7 (top left)
	col_g1 = 9;

	row_g2 = 20; // 8 (bottom left)
	col_g2 = 7;

	row_g3 = 20; // 4 (bottom right)
	col_g3 = 33;

	row_g4 = 11; // 9 (middle)
	col_g4 = 23;

	int initial_maze[ROWS][COLS] = {
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,5,1,0,0,0,0,0,1,2,1,0,0,0,0,0,0,0,0,1,2,1,1,2,1,0,0,0,0,0,0,0,0,1,2,1,0,0,0,0,0,1,5,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,2,2,2,2,2,2,2,2,7,1,1,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,2,9,2,2,2,2,2,2,2,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,1,1,2,1,1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,1,2,1,1,1,1,1,1,1,1,1 },
	{ 2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2 },
	{ 1,1,1,1,1,1,1,1,1,2,1,1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,1,2,1,1,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,6,2,2,2,2,2,2,2,2,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1 },
	{ 1,2,2,2,2,2,2,8,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,5,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,5,1 },
	{ 1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1 },
	{ 1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	};

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			maze[i][j] = initial_maze[i][j];
		}
	}
}


void game_reset2()
{
	score = 0;
	lives = 3;
	player_row = 17;
	player_col = 22;

	ghosts[0][0] = 20;
	ghosts[0][1] = 33;
	ghosts[1][0] = 8;
	ghosts[1][1] = 9;
	ghosts[2][0] = 20;
	ghosts[2][1] = 7;
	ghosts[3][0] = 11;
	ghosts[3][1] = 23;

	row_g1 = 8;  // 7 (top left)
	col_g1 = 9;

	row_g2 = 20; // 8 (bottom left)
	col_g2 = 7;

	row_g3 = 20; // 4 (bottom right)
	col_g3 = 33;

	row_g4 = 11; // 9 (middle)
	col_g4 = 23;

	int initial_maze2[ROWS][COLS] = {
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,5,1,0,0,0,0,0,1,2,1,0,0,0,0,0,0,0,0,1,2,1,1,2,1,0,0,0,0,0,0,0,0,1,2,1,0,0,0,0,0,1,5,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1 },
	{ 1,2,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,2,1 },
	{ 1,2,2,2,2,2,2,2,2,7,1,1,2,2,1,2,2,2,2,2,2,1,1,2,2,2,2,2,2,1,2,2,1,1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,2,9,2,2,2,2,2,2,2,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,1,1,2,1,1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,1,2,1,1,1,1,1,1,1,1,1 },
	{ 2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2 },
	{ 1,1,1,1,1,1,1,1,1,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,1,1,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,6,2,2,2,2,2,2,2,2,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1 },
	{ 1,2,2,2,1,2,2,8,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,1,2,2,2,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,5,2,2,2,2,2,1,1,2,2,2,2,2,1,2,2,2,2,2,2,1,1,2,2,2,2,2,2,1,2,2,2,2,2,1,1,2,2,2,2,2,5,1 },
	{ 1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1 },
	{ 1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	};

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			maze2[i][j] = initial_maze2[i][j];
		}
	}
}


void game_reset3()
{
	score = 0;
	lives = 3;
	player_row = 17;
	player_col = 22;

	ghosts[0][0] = 20;
	ghosts[0][1] = 33;
	ghosts[1][0] = 8;
	ghosts[1][1] = 9;
	ghosts[2][0] = 20;
	ghosts[2][1] = 7;
	ghosts[3][0] = 11;
	ghosts[3][1] = 23;

	row_g1 = 8;  // 7 (top left)
	col_g1 = 9;

	row_g2 = 20; // 8 (bottom left)
	col_g2 = 7;

	row_g3 = 20; // 4 (bottom right)
	col_g3 = 33;

	row_g4 = 11; // 9 (middle)
	col_g4 = 23;

	int initial_maze3[ROWS][COLS] = {
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,5,1,0,0,0,0,0,1,2,1,0,0,0,0,0,0,0,0,1,2,1,1,2,1,0,0,0,0,0,0,0,0,1,2,1,0,0,0,0,0,1,5,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1 },
	{ 1,2,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,2,1 },
	{ 1,2,2,2,2,2,2,2,2,7,1,1,2,2,1,2,2,2,2,2,2,1,1,2,2,2,2,2,2,1,2,2,1,1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,2,9,2,2,2,2,2,2,2,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,1,1,2,1,1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,1,2,1,1,1,1,1,1,1,1,1 },
	{ 2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2 },
	{ 1,1,1,1,1,1,1,1,1,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,1,1,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,6,2,2,2,2,2,2,2,2,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1 },
	{ 1,2,2,2,1,2,2,8,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,1,2,2,2,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1 },
	{ 1,5,2,2,2,2,2,1,1,2,2,2,2,2,1,2,2,2,2,2,2,1,1,2,2,2,2,2,2,1,2,2,2,2,2,1,1,2,2,2,2,2,5,1 },
	{ 1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1 },
	{ 1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	};

	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			maze2[i][j] = initial_maze3[i][j];
}


// LEVEL 1
void level1()
{
	system("cls");

	game_reset();

	cout << "\a";          // this will make a beep indicating the game has started
	while (print_maze() != 0)
	{
		char player_direction = _getch();

		player_movement(player_direction);

		ghost_movement1();

		system("cls");

		if (lives == 0)
			game_over();
	}
}

// LEVEL 2
void level2()
{
	system("cls");
	cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t  Congratulations! \n\t\t\t\t You successfully completed LEVEL 1! :)" << endl;
	cout << "\n\n\t\t\t\t\tYour Current Score : " << score;

	cout << "\n\n\t\t\t\t Press any key to proceed to Level 2!" << endl;
	_getch();

	system("cls");

	game_reset2();

	cout << "\a";          // this will make a beep indicating the game has started

	while (print_maze2() != 0)
	{
		char player_direction = _getch();

		player_movement2(player_direction);

		ghost_movement2();

		system("cls");

		if (lives == 0)
			game_over();
	}
}

// LEVEL 3
void level3()
{
	char choice_restart;
	system("cls");

	cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t  Congratulations! \n\t\t\t\t You successfully completed LEVEL 2! :)" << endl;
	cout << "\n\n\t\t\t\t\tYour Current Score : " << score << endl;

	cout << "\n\n\t\t\t\t Press any key to proceed to Level 3!" << endl;
	_getch();

	system("cls");

	game_reset3();

	cout << "\a";                                                // this will make a beep indicating the game has started

	while (print_maze3() != 0)
	{
		char player_direction = _getch();

		player_movement2(player_direction);

		ghost_movement3();

		system("cls");

		if (lives == 0)
			game_over();
	}

	system("cls");

	cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t  CONGRATULATIONS! \n\t\t\t\t\t\t YOU WON! :)" << endl;
	cout << "\n\n\t\t\t\t\tYour Score : " << score << endl;

	cout << "\n\n\t\t\t\t\t Press any key to exit" << endl;
	_getch();
}


void game_over()
{
	char choice_restart;

	system("cls"); // clear the console

	system("Color 04");
	cout << "\a";
	cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t       GAME OVER!";
	cout << "\n\n" << endl;
	cout << "\033[37m" << "\t\t\t\t  Your Final Score : " << score << endl;


	cout << "\033[32m" << "\n\n\n\n\t\t\t       Do you want to play again?" << endl;
	cout << "\033[37m" << "\n\t\t\t    Press 'Y' and then 'Enter' if YES" << endl;
	cout << "\t\t\t    Press 'N' and then 'Enter' if NO" << endl;

	cin >> choice_restart;

	if (choice_restart == 'Y' || choice_restart == 'y')
	{
		system("cls"); // clear the console

		main();        // restart the game

	}

	else if (choice_restart == 'N' || choice_restart == 'n')
	{
		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\t\t\t\tThank You for playing PACMAN! :) \n\t\t\t\tSee You Soon!\n\n\n\n\n\n\n\n\n\n" << endl;
		exit(0);
	}


}


/////////////////////////////////////////// END CODE ///////////////////////////////////////////