#pragma once
#define INF 0x3f3f3f3f
#define MaxDepth 4
#include <queue>
#include <conio.h>
#include <vector>

struct NNNNNN
{
	int v;
	int i, j;
	NNNNNN(int vv, int ii, int jj)
	{
		v = vv;
		i = ii;
		j = jj;
	}
	friend bool operator < (NNNNNN a, NNNNNN b)
	{
		return a.v < b.v;
	}
};

class Ai
{
public:
	void GetBoard(int b[15][15], int com, int man);
	void ManSet(int i, int j);
	void ComSet(int i, int j);
	void ReSet(int i, int j);
	int IsWin();
	int ChessToValue(int chess, int num);
	int BoardValue();
	void GetPoint(bool visit[15][15]);
	int MaxMinSearch(int depth, int alpha, int beta, bool flag);
	int FiveSearch(int depth, int alpha, int beta, bool flag);
	void Getij(int& i, int& j);
	bool xytoij(int x, int y, int& i, int& j);
	void Getij(int& i, int& j, int N);
	void Getnnn(int N, int& i, int & j);
	int board[15][15];
	int com;
	int man;
	int com_i, com_j;
};