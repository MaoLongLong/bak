#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <queue>
#include <cmath>
#include "ChessToFile.h"
#define INF 0x3f3f3f3f

using namespace std;

ChessToFile ctf;
int s;

int RedValueDir[5][5] = { {0, 1, 1, 1, 1},
						{1, 2, 2, 2, 3},
						{1, 2, 4, 4, 5},
						{1, 2, 4, 8, 10},
						{1, 3, 5, 10, 16} };

int BlueValueDir[5][5] = { {16, 10, 5, 3, 1},
						 {10, 8, 4, 2, 1},
						 {5, 4, 4, 2, 1},
						 {3, 2, 2, 2, 1},
						 {1, 1, 1, 1, 0} };

int RedDir[3][2] = { {1, 1}, {0, 1}, {1, 0} };
int BlueDir[3][2] = { {-1, -1}, {-1, 0}, {0, -1} };

int board[5][5];
int man, com, player, com_i, com_j;
void Init();
void PrintBoard();
void Set(int i, int j, int color, int id);
void Move(int i, int j, int ni, int nj, int id);
int GetValue(int x, int y);
bool Find(int id, int color, int& x, int& y);
int ManSearch(int x, int y);
int ComSearch(int x, int y);
bool IsWin()
{
	if (board[0][0] < 0)
		return true;
	if (board[4][4] > 0)
		return true;
	int cnt = 0;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
			if (board[i][j] > 0)
				++cnt;
	}
	if (cnt == 0)
		return true;
	cnt = 0;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
			if (board[i][j] < 0)
				++cnt;
	}
	if (cnt == 0)
		return true;
	return false;
}
void Game();

int main()
{
	Init();
	ctf.GetBoard(board);
	PrintBoard();
	Game();
	system("pause");
	return 0;
}

void Init()
{
	int fir;
	cout << "机器是否先手?[1/0]" << endl;
	cin >> fir;
	if (fir == 1)
	{
		com = RED;
		man = BLUE;
		player = com;
		board[0][0] = 6, board[0][1] = 2, board[0][2] = 4;
		board[1][0] = 1, board[1][1] = 5;
		board[2][0] = 3;
	}
	else
	{
		com = BLUE;
		man = RED;
		player = man;
		board[2][4] = -3;
		board[3][3] = -5, board[3][4] = -1;
		board[4][2] = -4, board[4][3] = -2, board[4][4] = -6;
	}
	PrintBoard();
	system("pause");
	system("cls");
	cout << "请输入对方的棋子" << endl;
	if (man == RED)
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3 - i; ++j)
				cin >> board[i][j];
		}
	}
	else
	{
		for (int i = 2; i < 5; ++i)
		{
			for (int j = 4 - i + 2; j < 5; ++j)
			{
				cin >> board[i][j];
				board[i][j] = -board[i][j];
			}
		}
	}
}

void PrintBoard()
{
	cout << "     0    1    2    3    4\n";
	cout << "  --------------------------\n";
	for (int i = 0; i < 5; ++i)
	{
		cout << i << " ";
		for (int j = 0; j < 5; ++j)
		{
			if (board[i][j] == 0)
				cout << "|    ";
			else
			{
				cout << "| ";
				cout << setw(2) << board[i][j];
				cout << " ";
			}
		}
		cout << "|\n  --------------------------\n";
	}
}

void Set(int i, int j, int color, int id)
{
	board[i][j] = color * id;
}

void Move(int i, int j, int ni, int nj, int id)
{
	board[i][j] = 0;
	board[ni][nj] = id;
}

int GetValue(int x, int y)
{
	int value = 0;
	if (com == RED)
	{
		for (int i = x; i < x + 3; ++i)
		{
			for (int j = y; j < y + 3; ++j)
			{
				if (i < 5 && j < 5)
				{
					if (board[i][j] > 0)
						value += RedValueDir[i][j];
					else if (board[i][j] < 0)
						value -= BlueValueDir[i][j];
				}
			}
		}
	}
	else
	{
		for (int i = x - 2; i <= x; ++i)
		{
			for (int j = y - 2; j <= y; ++j)
			{
				if (i >= 0 && j >= 0)
				{
					if (board[i][j] > 0)
						value -= RedValueDir[i][j];
					else if (board[i][j] < 0)
						value += BlueValueDir[i][j];
				}
			}
		}
	}
	return value;
}

bool Find(int id, int color, int& x, int& y)
{
	for (x = 0; x < 5; ++x)
	{
		for (y = 0; y < 5; ++y)
		{
			if (board[x][y] == id * color)
				return true;
		}
	}
	return false;
}

int ManSearch(int x, int y)
{
	int value = GetValue(x, y);
	if (com == RED)
	{
		for (int i = x; i < x + 3; ++i)
		{
			for (int j = y; j < y + 3; ++j)
			{
				if (i < 5 && j < 5 && board[i][j] < 0)
				{
					for (int k = 0; k < 3; ++k)
					{
						int ni = i + BlueDir[k][0];
						int nj = j + BlueDir[k][1];
						if (ni >= 0 && nj >= 0)
						{
							int temp = board[ni][nj];
							board[ni][nj] = board[i][j];
							board[i][j] = 0;
							int val = GetValue(x, y);
							board[i][j] = board[ni][nj];
							board[ni][nj] = temp;
							if (val < value)
								value = val;
						}
					}
				}
			}
		}
	}
	else
	{
		for (int i = x - 2; i <= x; ++i)
		{
			for (int j = y - 2; j <= y; ++j)
			{
				if (i >= 0 && j >= 0 && board[i][j] > 0)
				{
					for (int k = 0; k < 3; ++k)
					{
						int ni = i + RedDir[k][0];
						int nj = j + RedDir[k][1];
						if (ni < 5 && nj < 5)
						{
							int temp = board[ni][nj];
							board[ni][nj] = board[i][j];
							board[i][j] = 0;
							int val = GetValue(x, y);
							board[i][j] = board[ni][nj];
							board[ni][nj] = temp;
							if (val < value)
								value = val;
						}
					}
				}
			}
		}
	}
	return value;
}

int ComSearch(int x, int y)
{
	int value = -INF;
	if (com == RED)
	{
		for (int i = 0; i < 3; ++i)
		{
			int nx = x + RedDir[i][0];
			int ny = y + RedDir[i][1];
			if (nx < 5 && ny < 5)
			{
				int temp = board[nx][ny];
				board[nx][ny] = board[x][y];
				board[x][y] = 0;
				int val = ManSearch(x, y);
				board[x][y] = board[nx][ny];
				board[nx][ny] = temp;
				if (val > value)
				{
					value = val;
					com_i = nx;
					com_j = ny;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 3; ++i)
		{
			int nx = x + BlueDir[i][0];
			int ny = y + BlueDir[i][1];
			if (nx >= 0 && ny >= 0)
			{
				int temp = board[nx][ny];
				board[nx][ny] = board[x][y];
				board[x][y] = 0;
				int val = ManSearch(x, y);
				board[x][y] = board[nx][ny];
				board[nx][ny] = temp;
				if (val > value)
				{
					value = val;
					com_i = nx;
					com_j = ny;
				}
			}
		}
	}
	return value;
}

void Game()
{
	while (true)
	{
		if (player == man)
		{
			int s, i, j, ni, nj;
			cout << "输入色子和要移动的棋子坐标\n";
			cin >> s >> i >> j;
			cout << "移动到哪?\n";
			cin >> ni >> nj;
			Move(i, j, ni, nj, board[i][j]);
			ctf.GetChess(board[ni][nj] > 0 ? RED : BLUE, s, abs(board[ni][nj]), ni, nj);
			system("cls");
			PrintBoard();
			player = com;
			if (IsWin())
				return;
		}
		else
		{ /////////////////////////////////////////////
			int i, j;
			cout << "输入色子\n";
			cin >> s;
			if (!Find(s, com, i, j))
			{
				int l = s, r = s, v1 = -INF, v2 = -INF;
				while (l > 0)
				{
					--l;
					if (Find(l, com, i, j))
					{
						v1 = ComSearch(i, j);
						break;
					}
				}
				while (r < 6)
				{
					++r;
					if (Find(r, com, i, j))
					{
						v2 = ComSearch(i, j);
						break;
					}
				}
				if (v1 > v2)
					Find(l, com, i, j);
				else
					Find(r, com, i, j);
			}
			ComSearch(i, j);
			Move(i, j, com_i, com_j, board[i][j]);
			ctf.GetChess(board[com_i][com_j] > 0 ? RED : BLUE, s, abs(board[com_i][com_j]), com_i, com_j);
			system("cls");
			PrintBoard();
			player = man;
			if (IsWin())
				return;
		}
	}
}