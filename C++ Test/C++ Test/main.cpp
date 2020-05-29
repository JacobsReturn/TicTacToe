// C++ Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <Windows.h>
#include <time.h>
#include <random>
#include <cstdlib>
#include <conio.h>
#include "Point2D.h"
#include "mainDefine.h"

using namespace std;

// Making an AI :eyes:
class AI
{
	public:
		int Score(int win, int depth)
		{
			if (win == 0) return 10 - depth;
			else if (win == 1) return depth - 10;
			else return 0;
		}

		int Minimax(bool over, int depth)
		{
			if (over) return Score(2, 0);
		}
};


// GAME
void draw(int board[BOARD_HEIGHT][BOARD_WIDTH], Point2D player, Point2D winSpots[3])
{

	for (int y = 0; y < BOARD_HEIGHT; y++) 
	{
		cout << CSI << BOARD_HEIGHT + 3 + y << ";" << 10 << "H" << RESET_COLOR;

		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			bool win = false;
			for (int i = 0; i < 3; i++) 
			{
				if (winSpots[i].x == x && winSpots[i].y == y) win = true;
				//cout << winSpots[i].x << " " << winSpots[i].y << " ";
			}

			switch (board[y][x])
			{
				case EMPTY:
					if (player.x == x && player.y == y) cout << "[ " << WHITE << "#" << RESET_COLOR << " ]";
					else cout << "[ " << WHITE << " " << RESET_COLOR << " ]";
					
					break;
				case FULL_X:
					if (win) cout << RED << "[-X-]" << RESET_COLOR;
					else if (player.x == x && player.y == y) cout << "[ " << RED << "#" << RESET_COLOR << " ]";
					else cout << "[ " << RED << "X" << RESET_COLOR << " ]";
					
					break;
				case FULL_O:
					if (win) cout << GREEN << "[-X-]" << RESET_COLOR;
					else if (player.x == x && player.y == y) cout << "[ " << GREEN << "#" << RESET_COLOR << " ]";
					else cout << "[ " << GREEN << "O" << RESET_COLOR << " ]";

					break;
			}
		}
		cout << endl;
	}
}

int main()
{
	cout << SAVE_CURSOR_POS;

	bool gameOver = false;

	DWORD dwMode = 0;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);

	int board[BOARD_HEIGHT][BOARD_WIDTH];
	board[0][0] = 0;
	board[0][1] = 0;
	board[0][2] = 0;

	board[1][0] = 0;
	board[1][1] = 0;
	board[1][2] = 0;

	board[2][0] = 0;
	board[2][1] = 0;
	board[2][2] = 0;

	Point2D player = { 0, 0 };
	bool turn = true;

	bool win = false;
	Point2D winSpots[3] = { { -1, -1 }, { -1, -1 }, { -1, -1 } };

	string error = "";

	// game 
	cout << "\x1b[0;12H" << MAGENTA << "TIC TAC TOE \n" << endl;
	cout << YELLOW << "Press the arrow keys to select a tile. \nPress space to place at the selected tile." << RESET_COLOR << endl;

	while (!gameOver)
	{
		//Point2D position = { 0, 0 };

		draw(board, player, winSpots);

		cout << endl;
		string text = "Player 1's turn.";
		if (!turn) text = "Player 2's turn.";

		cout << "\x1b[10;10H" << WHITE << text << endl;
		cout << RED << error << endl;
		cout << endl;

		if (win)
		{
			cout << "Press enter to restart." << endl;
			cin.get();

			gameOver = true;

			system("cls");

			main();
		}

		int input = _getch();

		switch (input)
		{
			case DOWN:
				player.y += 1;
				error = "                                                             ";

				break;
			case UP:
				player.y -= 1;
				error = "                                                             ";

				break;
			case RIGHT:
				player.x += 1;
				error = "                                                             ";

				break;
			case LEFT:
				player.x -= 1;
				error = "                                                             ";

				break;
			case SPACE:
				if (board[player.y][player.x] != 0) 
				{
					error = "Error: You can only place on an open space!";
					break;
				}

				if (turn) board[player.y][player.x] = FULL_X;
				else board[player.y][player.x] = FULL_O;

				turn = !turn;

				player.x = 0;
				player.y = 0;

				error = "                                                             ";

				break;
			default:
				error = "                                                             ";
				error = "Error: That is not a valid key.";
				break;
		}

		if (player.x > BOARD_WIDTH - 1) player.x = 0;
		else if (player.x < 0) player.x = BOARD_WIDTH - 1;

		if (player.y > BOARD_HEIGHT - 1) player.y = 0;
		else if (player.y < 0) player.y = BOARD_HEIGHT - 1;

		if (board[0][0] > 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2])
		{
			winSpots[0] = { 0, 0 };
			winSpots[1] = { 1, 1 };
			winSpots[2] = { 2, 2 };

			win = true;
		}
		else if (board[2][0] > 0 && board[2][0] == board[1][1] && board[1][1] == board[0][2])
		{
			winSpots[0] = { 0, 2 };
			winSpots[1] = { 1, 1 };
			winSpots[2] = { 2, 0 };

			win = true;
		}

		for (int y = 0; y < BOARD_HEIGHT; y++)
		{
			if (board[y][0] > 0 && board[y][0] == board[y][1] && board[y][0] == board[y][2])
			{
				winSpots[0] = { 0, y };
				winSpots[1] = { 1, y };
				winSpots[2] = { 2, y };

				win = true;
			}

			for (int x = 0; x < BOARD_WIDTH; x++)
			{
				if (board[0][x] > 0 && board[0][x] == board[1][x] && board[1][x] == board[2][x])
				{
					winSpots[0] = { x, 0 };
					winSpots[1] = { x, 1 };
					winSpots[2] = { x, 2 };

					win = true;
				}
			}
		}

		bool allfull = true;
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{
			for (int x = 0; x < BOARD_WIDTH; x++)
			{
				if (board[y][x] == 0)
				{
					allfull = false;
				}
			}
		}
		if (allfull) 
		{
			if (win) allfull = false;
			else win = true;
		}

		if (win) 
		{
			if (allfull) error = "You both tied!";
			else if (turn) error = "Player 1 has won!";
			else error = "Player 2 has won!";
		}
		//cout << winSpots[0].x << " " << win << endl;

		/*if (win)
		{
			gameOver = true;

			system("cls");

			main();
		}*/
	}

    return 0;
}