#include <graphics.h>
#include <conio.h>
#include "Board.h"

int main()
{
	initgraph(640, 640);
	Board boa;
	boa.Init();
	boa.Game();
	_getch();
	closegraph();
	return 0;
}