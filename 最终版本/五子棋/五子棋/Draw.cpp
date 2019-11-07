#include "Draw.h"
#include <graphics.h>
#include "ChessFile.h"

Chessfile che;

void Draw::DrawBoard()
{
	setbkcolor(BROWN);
	cleardevice();
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	for (int i = 19; i <= 621; i += 43)
	{
		line(19, i, 621, i);
		line(i, 19, i, 621);
	}
}

void Draw::DrawChess(int i, int j, int color)
{
	setfillcolor(color);
	solidcircle(j * 43 + 19, i * 43 + 19, 13);
	che.Get(i, j, color);
}

void Draw::DrawNNN(int i, int j, int color)
{
	setfillcolor(color);
	solidcircle(j * 43 + 19, i * 43 + 19, 13);
}

void Draw::Re(int i, int j)
{
	setfillcolor(BROWN);
	solidcircle(j * 43 + 19, i * 43 + 19, 13);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	line(j * 43 + 19, i * 43 + 6, j * 43 + 19, i * 43 + 32);
	line(j * 43 + 6, i * 43 + 19, j * 43 + 32, i * 43 + 19);
}
