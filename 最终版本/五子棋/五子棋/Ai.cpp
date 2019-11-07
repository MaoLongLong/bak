#include "Ai.h"
#include "Draw.h"
#include <graphics.h>
using namespace std;
Draw dr;
priority_queue<NNNNNN> que;
int ns[15][15];

void Ai::GetBoard(int b[15][15], int com, int man)
{
	for (int i = 0; i < 15; ++i)
		for (int j = 0; j < 15; ++j)
			board[i][j] = b[i][j];
	this->com = com;
	this->man = man;
}

void Ai::ManSet(int i, int j)
{
	board[i][j] = man;
}

void Ai::ComSet(int i, int j)
{
	board[i][j] = com;
}

void Ai::ReSet(int i, int j)
{
	board[i][j] = -1;
}

int Ai::IsWin() {
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			if (board[i][j] == -1)
				continue;
			int tmp = j;
			while (j < 15 - 1 && board[i][j] == board[i][j + 1])
				++j;
			if (j - tmp + 1 == 5)
				return board[i][tmp];
		}
	}
	for (int j = 0; j < 15; ++j) {
		for (int i = 0; i < 15; ++i) {
			if (board[i][j] == -1)
				continue;
			int tmp = i;
			while (i < 14 && board[i][j] == board[i + 1][j])
				++i;
			if (i - tmp + 1 == 5)
				return board[tmp][j];
		}
	}
	for (int k = 14; k >= 0; --k) {
		for (int i = k, j = 0; i < 15; ++i, ++j) {
			if (board[i][j] == -1)
				continue;
			int tmp1 = i, tmp2 = j;
			while (i < 14 && board[i][j] == board[i + 1][j + 1])
				++i, ++j;
			if (i - tmp1 + 1 == 5)
				return board[tmp1][tmp2];
		}
	}
	for (int k = 1; k < 15; ++k) {
		for (int i = 0, j = k; j < 15; ++i, ++j) {
			if (board[i][j] == -1)
				continue;
			int tmp1 = i, tmp2 = j;
			while (j < 14 && board[i][j] == board[i + 1][j + 1])
				++i, ++j;
			if (i - tmp1 + 1 == 5)
				return board[tmp1][tmp2];
		}
	}
	for (int k = 0; k < 15; ++k) {
		for (int i = k, j = 0; i >= 0; --i, ++j) {
			if (board[i][j] == -1)
				continue;
			int tmp1 = i, tmp2 = j;
			while (i > 0 && board[i][j] == board[i - 1][j + 1])
				--i, ++j;
			if (j - tmp2 + 1 == 5)
				return board[tmp1][tmp2];
		}
	}
	for (int k = 1; k < 15; ++k) {
		for (int i = 14, j = k; j < 15; --i, ++j) {
			if (board[i][j] == -1)
				continue;
			int tmp1 = i, tmp2 = j;
			while (j < 14 && board[i][j] == board[i - 1][j + 1])
				--i, ++j;
			if (j - tmp2 + 1 == 5)
				return board[tmp1][tmp2];
		}
	}
	return -1;
}

int Ai::ChessToValue(int chess, int num) {
	if (num == 5)
		return chess == com ? INF / 2 : -INF / 2;
	else if (num == 4)
		return chess == com ? 30000 : -50000;
	else if (num == 3)
		return chess == com ? 3000 : -5000;
	else if (num == 2)
		return chess == com ? 300 : -500;
	else if (num == 1)
		return chess == com ? 30 : -50;
	else
		return 0;
}

int Ai::BoardValue() {
	int value = 0;
	// 行:
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			if (board[i][j] == -1)
				continue;
			int tmp = j;
			while (j < 15 - 1 && board[i][j] == board[i][j + 1])
				++j;
			if (j - tmp + 1 == 5)
				value += ChessToValue(board[i][tmp], j - tmp + 1);
			else
			{
				// 活:
				if (tmp > 0 && board[i][tmp - 1] == -1 && j < 14 && board[i][j + 1] == -1)
					value += ChessToValue(board[i][tmp], j - tmp + 1);
				// 单边死:
				else if (tmp > 0 && board[i][tmp - 1] == -1 || j < 14 && board[i][j + 1] == -1)
					value += ChessToValue(board[i][tmp], (j - tmp + 1) == 5 ? 5 : (j - tmp));
			}
		}
	}
	// 列:
	for (int j = 0; j < 15; ++j) {
		for (int i = 0; i < 15; ++i) {
			if (board[i][j] == -1)
				continue;
			int tmp = i;
			while (i < 14 && board[i][j] == board[i + 1][j])
				++i;
			if (i - tmp + 1 == 5)
				value += ChessToValue(board[tmp][j], i - tmp + 1);
			else
			{
				// 活:
				if (tmp > 0 && board[tmp - 1][j] == -1 && i < 14 && board[i + 1][j] == -1)
					value += ChessToValue(board[tmp][j], i - tmp + 1);
				else if (tmp > 0 && board[tmp - 1][j] == -1 || i < 14 && board[i + 1][j] == -1)
					value += ChessToValue(board[tmp][j], (i - tmp + 1) == 5 ? 5 : (i - tmp));
			}
		}
	}
	// 捺:
	for (int k = 14; k >= 0; --k) {
		for (int i = k, j = 0; i < 15; ++i, ++j) {
			if (board[i][j] == -1)
				continue;
			int tmp1 = i, tmp2 = j;
			while (i < 14 && board[i][j] == board[i + 1][j + 1])
				++i, ++j;
			if (i - tmp1 + 1 == 5)
				value = ChessToValue(board[tmp1][tmp2], i - tmp1 + 1);
			else
			{
				// 活:
				if (tmp2 > 0 && board[tmp1 - 1][tmp2 - 1] == -1 && i < 14 && board[i + 1][j + 1] == -1)
					value += ChessToValue(board[tmp1][tmp2], i - tmp1 + 1);
				else if (tmp2 > 0 && board[tmp1 - 1][tmp2 - 1] == -1 || i < 14 && board[i + 1][j + 1] == -1)
					value += ChessToValue(board[tmp1][tmp2], (i - tmp1 + 1) == 5 ? 5 : (i - tmp1));
			}
		}
	}
	for (int k = 1; k < 15; ++k) {
		for (int i = 0, j = k; j < 15; ++i, ++j) {
			if (board[i][j] == -1)
				continue;
			int tmp1 = i, tmp2 = j;
			while (j < 14 && board[i][j] == board[i + 1][j + 1])
				++i, ++j;
			if (i - tmp1 + 1 == 5)
				value += ChessToValue(board[tmp1][tmp2], i - tmp1 + 1);
			else
			{
				// 活:
				if (tmp1 > 0 && board[tmp1 - 1][tmp2 - 1] == -1 && j < 14 && board[i + 1][j + 1] == -1)
					value += ChessToValue(board[tmp1][tmp2], i - tmp1 + 1);
				if (tmp1 > 0 && board[tmp1 - 1][tmp2 - 1] == -1 || j < 14 && board[i + 1][j + 1] == -1)
					value += ChessToValue(board[tmp1][tmp2], (i - tmp1 + 1) == 5 ? 5 : (i - tmp1));
			}
		}
	}
	// 撇:
	for (int k = 0; k < 15; ++k) {
		for (int i = k, j = 0; i >= 0; --i, ++j) {
			if (board[i][j] == -1)
				continue;
			int tmp1 = i, tmp2 = j;
			while (i > 0 && board[i][j] == board[i - 1][j + 1])
				--i, ++j;
			if (j - tmp2 + 1 == 5)
				value += ChessToValue(board[tmp1][tmp2], j - tmp2 + 1);
			else
			{
				// 活:
				if (tmp2 > 0 && board[tmp1 + 1][tmp2 - 1] == -1 && i > 0 && board[i - 1][j + 1] == -1)
					value += ChessToValue(board[tmp1][tmp2], j - tmp2 + 1);
				else if (tmp2 > 0 && board[tmp1 + 1][tmp2 - 1] == -1 || i > 0 && board[i - 1][j + 1] == -1)
					value += ChessToValue(board[tmp1][tmp2], (j - tmp2 + 1) == 5 ? 5 : (j - tmp2));
			}
		}
	}
	for (int k = 1; k < 15; ++k) {
		for (int i = 14, j = k; j < 15; --i, ++j) {
			if (board[i][j] == -1)
				continue;
			int tmp1 = i, tmp2 = j;
			while (j < 14 && board[i][j] == board[i - 1][j + 1])
				--i, ++j;
			if (j - tmp2 + 1 == 5)
				value += ChessToValue(board[tmp1][tmp2], j - tmp2 + 1);
			else
			{
				// 活:
				if (tmp1 < 14 && board[tmp1 + 1][tmp2 - 1] == -1 && j < 14 && board[i - 1][j + 1] == -1)
					value += ChessToValue(board[tmp1][tmp2], j - tmp2 + 1);
				if (tmp1 < 14 && board[tmp1 + 1][tmp2 - 1] == -1 && j < 14 || board[i - 1][j + 1] == -1)
					value += ChessToValue(board[tmp1][tmp2], (j - tmp2 + 1) == 5 ? 5 : (j - tmp2));
			}
		}
	}
	return value;
}

void Ai::GetPoint(bool visit[15][15]) {
	for (int i = 0; i < 15; ++i)
		for (int j = 0; j < 15; ++j)
			visit[i][j] = false;
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			if (board[i][j] == -1)
				continue;
			if (i > 0 && board[i - 1][j] == -1)
				visit[i - 1][j] = true;
			if (j > 0 && board[i][j - 1] == -1)
				visit[i][j - 1] = true;
			if (i > 1 && board[i - 2][j] == -1)
				visit[i - 2][j] = true;
			if (j > 1 && board[i][j - 2] == -1)
				visit[i][j - 2] = true;
			if (i < 14 && board[i + 1][j] == -1)
				visit[i + 1][j] = true;
			if (j < 14 && board[i][j + 1] == -1)
				visit[i][j + 1] = true;
			if (i < 13 && board[i + 2][j] == -1)
				visit[i + 2][j] = true;
			if (j < 13 && board[i][j + 2] == -1)
				visit[i][j + 2] = true;
			if (i > 0 && j > 0 && board[i - 1][j - 1] == -1)
				visit[i - 1][j - 1] = true;
			if (i > 1 && j > 1 && board[i - 2][j - 2] == -1)
				visit[i - 2][j - 2] = true;
			if (i > 0 && j < 14 && board[i - 1][j + 1] == -1)
				visit[i - 1][j + 1] = true;
			if (i > 1 && j < 13 && board[i - 2][j + 2] == -1)
				visit[i - 2][j + 2] = true;
			if (i < 14 && j > 0 && board[i + 1][j - 1] == -1)
				visit[i + 1][j - 1] = true;
			if (i < 13 && j > 1 && board[i + 2][j - 2] == -1)
				visit[i + 2][j - 2] = true;
			if (i < 14 && j < 14 && board[i + 1][j + 1] == -1)
				visit[i + 1][j + 1] = true;
			if (i < 13 && j < 13 && board[i + 2][j + 2] == -1)
				visit[i + 2][j + 2] = true;
		}
	}
}

int Ai::MaxMinSearch(int depth, int alpha, int beta, bool flag) {
	int win = IsWin();
	if (win != -1)
		return BoardValue();
	if (depth == MaxDepth)
		return BoardValue();
	int value;
	bool visit[15][15];
	GetPoint(visit);
	// Max
	if (!flag) {
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				if (visit[i][j]) {
					ComSet(i, j);
					value = MaxMinSearch(depth + 1, alpha, beta, !flag);
					ReSet(i, j);
					if (value > alpha) {
						if (depth == 1)
							com_i = i, com_j = j;
						alpha = value;
					}
					if (alpha > beta)
						return alpha;
				}
			}
		}
		return alpha;
	}
	// Min
	else {
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				if (visit[i][j]) {
					ManSet(i, j);
					value = MaxMinSearch(depth + 1, alpha, beta, !flag);
					ReSet(i, j);
					if (value < beta) {
						beta = value;
					}
					if (alpha > beta)
						return beta;
				}
			}
		}
		return beta;
	}
}

int Ai::FiveSearch(int depth, int alpha, int beta, bool flag)
{
	int win = IsWin();
	if (win != -1)
		return BoardValue();
	if (depth == MaxDepth)
		return BoardValue();
	int value;
	bool visit[15][15];
	GetPoint(visit);
	// Max
	if (!flag) {
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				if (visit[i][j]) {
					ComSet(i, j);
					value = FiveSearch(depth + 1, alpha, beta, !flag);
					ReSet(i, j);
					if (depth == 1)
						que.push(NNNNNN(value, i, j));
					if (value > alpha) {
						if (depth == 1)
							com_i = i, com_j = j;
						alpha = value;
					}
					if (alpha > beta)
						return alpha;
				}
			}
		}
		return alpha;
	}
	// Min
	else {
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				if (visit[i][j]) {
					ManSet(i, j);
					value = FiveSearch(depth + 1, alpha, beta, !flag);
					ReSet(i, j);
					if (value < beta) {
						beta = value;
					}
					if (alpha > beta)
						return beta;
				}
			}
		}
		return beta;
	}
}

void Ai::Getij(int& i, int& j)
{
	MaxMinSearch(1, -INF, INF, false);
	i = com_i, j = com_j;
}

bool Ai::xytoij(int x, int y, int& i, int& j)
{
	int flag = 0, p = 0, q = 38;
	for (j = 0; j < 15; ++j, p += 43, q += 43)
	{
		if (x > p && x < q)
		{
			++flag;
			x = (p + q) / 2;
			break;
		}
	}
	p = 0, q = 38;
	for (i = 0; i < 15; ++i, p += 43, q += 43)
	{
		if (y > p && y < q)
		{
			++flag;
			y = (p + q) / 2;
			break;
		}
	}
	if (flag == 2)
		return true;
	else
		return false;
}

void Ai::Getij(int& i, int& j, int N)
{
	FiveSearch(1, -INF, INF, false);
	for (int k = 0; k < N; ++k)
	{
		NNNNNN nnn = que.top();
		que.pop();
		ns[nnn.i][nnn.j] = 1;
		dr.DrawNNN(nnn.i, nnn.j, 0x0000AA);
	}
	while (true)
	{
		MOUSEMSG m = GetMouseMsg();
		if (m.mkLButton)
		{
			if (xytoij(m.x, m.y, i, j) && ns[i][j] == 1)
			{
				ns[i][j] = 0;
				break;
			}
		}
	}
	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			if (ns[i][j] == 1)
				dr.Re(i, j);
		}
	}
}

void Ai::Getnnn(int N, int& i, int& j)
{
	int v = -INF;
	for (int k = 0; k < N; ++k)
	{
		while (true)
		{
			MOUSEMSG m = GetMouseMsg();
			if (m.mkLButton)
			{
				if (xytoij(m.x, m.y, i, j) && ns[i][j] == 0 && board[i][j] == -1)
				{
					ns[i][j] = 1;
					dr.DrawNNN(i, j, 0x0000AA);
					break;
				}
			}
		}

	}
	for (int p = 0; p < 15; ++p)
	{
		for (int q = 0; q < 15; ++q)
		{
			if (ns[p][q] == 1)
			{
				board[p][q] = BLACK;
				if (BoardValue() > v)
				{
					v = BoardValue();
					i = p;
					j = q;
				}
				board[p][q] = -1;
			}
		}
	}
	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			if (ns[i][j] == 1)
				dr.Re(i, j);
		}
	}
}
