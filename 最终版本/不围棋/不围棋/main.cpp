#include <iostream>
#include <cstdlib>
#define N 9
#define BLACK 1
#define WHITE -1
#define MaxDepth 3
#define MaxStep 81
#define INF 0x3f3f3f3f

using namespace std;

int com, man, player;
int board[N][N];
int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
bool visited[N][N];
int com_i, com_j, STEP = 0;

void Init();
void PrintBoard();
bool dfs(int i, int j, int color);
bool Judge(int i, int j, int color);
int GetValue();
int MaxMinSearch(int depth, int step, int alpha, int beta, bool flag);
void Game();
int IsWin();

int main()
{
	Init();
	PrintBoard();
	Game();
	system("pause");
	return 0;
}

void Init()
{
	cout << "ÊÇ·ñÏÈÊÖ?[1/0]" << endl;
	int fir;
	cin >> fir;
	if (fir == 1)
	{
		com = BLACK;
		man = WHITE;
		board[4][4] = com;
		++STEP;
		player = man;
	}
	else
	{
		com = WHITE;
		man = BLACK;
		player = man;
	}
	system("cls");
}

void PrintBoard()
{
	cout << "    0   1   2   3   4   5   6   7   8\n";
	cout << "  -------------------------------------\n";
	for (int i = 0; i < N; ++i)
	{
		cout << i << " ";
		for (int j = 0; j < N; ++j)
		{
			if (board[i][j] == 1)
				cout << "| X ";
			else if (board[i][j] == -1)
				cout << "| O ";
			else
				cout << "|   ";
		}
		cout << "|\n  -------------------------------------\n";
	}
}

bool dfs(int i, int j, int color)
{
	visited[i][j] = true;
	if (board[i][j] == 0)
		return true;
	for (int k = 0; k < 4; ++k)
	{
		int ni = i + dir[k][0];
		int nj = j + dir[k][1];
		if (!visited[ni][nj] && ni >= 0 && nj >= 0 && ni < N && nj < N && board[ni][nj] != -color)
			if (dfs(ni, nj, color))
				return true;
	}
	return false;
}

bool Judge(int i, int j, int color)
{
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			visited[i][j] = false;
	return dfs(i, j, color);
}

int GetValue()
{
	int val1 = 0, val2 = 0;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (board[i][j] == 0)
			{
				board[i][j] = com;
				if (Judge(i, j, com))
					++val1;
				for (int k = 0; k < 4; ++k)
				{
					int ni = i + dir[k][0];
					int nj = j + dir[k][1];
					if (ni >= 0 && nj >= 0 && ni < N && nj < N)
						if (!Judge(ni, nj, man))
						{
							--val1;
							break;
						}
				}
				board[i][j] = man;
				if (Judge(i, j, man))
					++val2;
				for (int k = 0; k < 4; ++k)
				{
					int ni = i + dir[k][0];
					int nj = j + dir[k][1];
					if (ni >= 0 && nj >= 0 && ni < N && nj < N)
						if (!Judge(ni, nj, com))
						{
							--val2;
							break;
						}
				}
				board[i][j] = 0;
			}
		}
	}
	return (val1 - val2);
}

int MaxMinSearch(int depth, int step, int alpha, int beta, bool flag)
{
	if (depth == MaxDepth || step == 81)
		return GetValue();
	int value;
	if (flag)
	{
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (board[i][j] != 0)
					continue;
				board[i][j] = com;
				if (!Judge(i, j, com))
				{
					board[i][j] = 0;
					continue;
				}
				value = MaxMinSearch(depth + 1, step + 1, alpha, beta, !flag);
				board[i][j] = 0;
				if (value > alpha)
				{
					if (depth == 1)
						com_i = i, com_j = j;
					alpha = value;
				}
				if (alpha > beta)
					return alpha;
			}
		}
		return alpha;
	}
	else
	{
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (board[i][j] != 0)
					continue;
				board[i][j] = man;
				value = MaxMinSearch(depth + 1, step + 1, alpha, beta, !flag);
				board[i][j] = 0;
				if (value < beta)
					beta = value;
				if (alpha > beta)
					return beta;
			}
		}
		return beta;
	}
}

void Game()
{
	int x, y;
	while (true)
	{
		if (player == man)
		{
			cin >> x >> y;
			board[x][y] = man;
			++STEP;
			player = com;
		}
		else
		{
			MaxMinSearch(1, STEP, -INF, INF, true);
			board[com_i][com_j] = com;
			//cout << com_i << " " << com_j << endl;
			++STEP;
			player = man;
		}
		system("cls");
		PrintBoard();
		if (player == man)
			cout << com_i << " " << com_j << endl;
		if (IsWin())
			return;
	}
}

int IsWin()
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (board[i][j] != 0)
				if (!Judge(i, j, board[i][j]))
					return board[i][j];
		}
	}
	return 0;
}
