#pragma once
#include <queue>
#include <fstream>
#define RED 1
#define BLUE -1

using namespace std;

struct Chess
{
	int color;
	int sz;
	int id;
	int i, j;
};

int i_dir[5] = { 5, 4, 3, 2, 1 };
char j_dir[5] = { 'A', 'B', 'C', 'D', 'E' };

class ChessToFile
{
public:
	void GetBoard(int board[5][5])
	{
		ri.resize(7);
		rj.resize(7);
		bi.resize(7);
		bj.resize(7);
		// R
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3 - i; ++j)
			{
				ri[board[i][j]] = i;
				rj[board[i][j]] = j;
			}
		}
		// B
		for (int i = 2; i < 5; ++i)
		{
			for (int j = 4 - i + 2; j < 5; ++j)
			{
				bi[-board[i][j]] = i;
				bj[-board[i][j]] = j;
			}
		}
	}
	void GetChess(int color, int sz, int id, int i, int j)
	{
		Chess che;
		che.color = color;
		che.sz = sz;
		che.id = id;
		che.i = i;
		che.j = j;
		que.push(che);
	}
	~ChessToFile()
	{
		fstream fout("D:\\test.txt", ios::out);
		fout << "R:";
		for (int i = 1; i < 7; ++i)
		{
			fout << j_dir[rj[i]] << i_dir[ri[i]] << '-' << i;
			if (i < 6)
				fout << ';';
		}
		fout << "\nB:";
		for (int i = 1; i < 7; ++i)
		{
			fout << j_dir[bj[i]] << i_dir[bi[i]] << '-' << i;
			if (i < 6)
				fout << ';';
		}
		fout << endl;
		int index = 0;
		while (!que.empty())
		{
			Chess che = que.front();
			que.pop();
			fout << ++index << ':' << che.sz << ";(";
			if (che.color == RED)
				fout << 'R';
			else
				fout << 'B';
			fout << che.id;
			fout << ',';
			fout << j_dir[che.j] << i_dir[che.i] << ")\n";
		}
	}
	vector<int> ri;
	vector<int> rj;
	vector<int> bi;
	vector<int> bj;
	queue<Chess> que;
};