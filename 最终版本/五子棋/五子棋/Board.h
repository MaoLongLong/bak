#pragma once

class Board
{
public:
	void Init();
	bool xytoij(int x, int y, int& i, int& j);
	void Game();
	int IsWin();
	int board[15][15];
	int com;
	int man;
	int player;
};