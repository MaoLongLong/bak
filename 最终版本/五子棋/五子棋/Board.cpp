#include "Board.h"
#include "Draw.h"
#include "Ai.h"
#include <graphics.h>
#include <conio.h>
#include <Windows.h>
#include <queue>
using namespace std;

Draw dra;
Ai ai;
MOUSEMSG m;
int step = 4;
int N;

void Board::Init()
{
	dra.DrawBoard();
	for (int i = 0; i < 15; ++i)
		for (int j = 0; j < 15; ++j)
			board[i][j] = -1;
	_getch();
	wchar_t nNn[2];
	InputBox(nNn, 2, L"N的值[1/0]");
	N = _wtoi(nNn);
	wchar_t fir[2];
	InputBox(fir, 2, L"机器是否先手?[1/0]");
	if (fir[0] == '1')
	{
		com = BLACK;
		man = WHITE;
		dra.DrawChess(7, 7, com);
		board[7][7] = com;
		dra.DrawChess(8, 7, man);
		board[8][7] = man;
		dra.DrawChess(6, 6, com);
		board[6][6] = com;
		_getch();
		wchar_t swa[2];player = man;
		InputBox(swa, 2, L"是否换手?[1/0]");
		if (swa[0] == '1')
		{
			//++step;
			com = WHITE;
			man = BLACK;
			player = com;
			/*dra.DrawChess(8, 8, com);
			board[8][8] = com;*/
			/*dra.DrawChess(7, 8, com);
			board[7][8] = com;*/
		}
		
	}
	else
	{
		com = WHITE;
		man = BLACK;
		while (true)
		{
			m = GetMouseMsg();
			if (m.mkLButton)
			{
				int i, j;
				if (xytoij(m.x, m.y, i, j))
				{
					dra.DrawChess(i, j, man);
					board[i][j] = man;
					break;
				}
			}
		}
		while (true)
		{
			m = GetMouseMsg();
			if (m.mkLButton)
			{
				int i, j;
				if (xytoij(m.x, m.y, i, j))
				{
					dra.DrawChess(i, j, com);
					board[i][j] = com;
					break;
				}
			}
		}
		while (true)
		{
			m = GetMouseMsg();
			if (m.mkLButton)
			{
				int i, j;
				if (xytoij(m.x, m.y, i, j))
				{
					dra.DrawChess(i, j, man);
					board[i][j] = man;
					break;
				}
			}
		}player = com;
		_getch();
		wchar_t swa[2];
		InputBox(swa, 2, L"是否换手?[1/0]");
		if (swa[0] == '1')
		{
			//++step;
			com = BLACK;
			man = WHITE;player = man;
			/*for (int i = 0; i < 2; ++i)
			{*/
			/*while (true)
			{
				m = GetMouseMsg();
				if (m.mkLButton)
				{
					int i, j;
					if (xytoij(m.x, m.y, i, j))
					{
						dra.DrawChess(i, j, man);
						board[i][j] = man;
						break;
					}
				}
			}*/
			//}
		}
		
	}
}

bool Board::xytoij(int x, int y, int& i, int& j)
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
	if (flag == 2 && board[i][j] == -1)
		return true;
	else
		return false;
}

void Board::Game()
{
	while (true)
	{
		if (step == 5)
		{
			if (com == BLACK)
			{
				++step;
				int i, j;
				ai.GetBoard(board, com, man);
				ai.Getij(i, j, N);
				dra.DrawChess(i, j, com);
				board[i][j] = com;
				player = man;
			}
			else
			{
				int i, j;
				++step;
				ai.GetBoard(board, com, man);
				ai.Getnnn(N, i, j);
				dra.DrawChess(i, j, man);
				board[i][j] = man;
				player = com;
			}
			continue;
		}
		if (player == com)
		{
			++step;
			int i, j;
			ai.GetBoard(board, com, man);
			ai.Getij(i, j);
			dra.DrawChess(i, j, com);
			board[i][j] = com;
			player = man;
			if (IsWin() != -1)
				return;
		}
		else
		{
			++step;
			while (true)
			{
				m = GetMouseMsg();
				if (m.mkLButton)
				{
					int i, j;
					if (xytoij(m.x, m.y, i, j))
					{
						dra.DrawChess(i, j, man);
						board[i][j] = man;
						player = com;
						if (IsWin() != -1)
							return;
						break;
					}
				}
			}
		}
	}
}

int Board::IsWin() {
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