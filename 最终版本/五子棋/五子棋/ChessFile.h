#pragma once
#include <queue>
#include <fstream>
#include <iostream>

struct chess
{
	int color;
	int i, j; // 数组下标
	// ...
};

int i_dir[15] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
char j_dir[15] = {'A','B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K','L','M','N','O'};

class Chessfile
{
public:
	~Chessfile()
	{
		std::ofstream f("D:\\test.txt");
		f << '{';
		while (!que.empty())
		{
			chess che = que.front();
			if (che.color == BLACK)
			{
				f << "B(" << j_dir[che.j] << ',' << i_dir[che.i] << ");";
			}
			else
			{
				f << "W(" << j_dir[che.j] << ',' << i_dir[che.i] << ");";
			}
			que.pop();
		}
		f << '}';
		f.close();
	}
	void Get(int i, int j, int color)
	{
		chess che;
		che.i = i;
		che.j = j;
		che.color = color;
		que.push(che);
	}
	std::queue<chess> que;
};