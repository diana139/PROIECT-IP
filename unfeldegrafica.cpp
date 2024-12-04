#include <iostream>

#include <graphics.h>

using namespace std;

int X_OFFSET=150, Y_OFFSET=100, CELL_SIZE=100;

void OpenGraph()

{

	 int gd=DETECT,gm;

	initgraph(&gd,&gm,"c:\\bc\\bgi");

}



void drawBoard() {

    setfillstyle(SOLID_FILL,MAGENTA);

    for (int i = 1; i < 3; i++) {



        setcolor(GREEN);

        line(X_OFFSET, Y_OFFSET + i * CELL_SIZE, X_OFFSET + 3 * CELL_SIZE, Y_OFFSET + i * CELL_SIZE);



    }

    for (int i = 1; i< 3; i++) {

        setcolor(FOREGROUND_RED );

        line(X_OFFSET + i * CELL_SIZE, Y_OFFSET, X_OFFSET + i * CELL_SIZE, Y_OFFSET + 3 * CELL_SIZE);

    }



}



int main()

{

    OpenGraph();

    settextstyle(3,HORIZ_DIR,4);

	settextjustify(CENTER_TEXT,CENTER_TEXT);

	

	setcolor(RED);

	outtextxy(320,25,"GOBBLET ");

	

	setcolor(GREEN);

	outtextxy(320, 50, "GOBBLERS");

    

    setbkcolor(WHITE);

	

	bar(30, 60,getmaxx()-30,getmaxy()-30);

    

    drawBoard();

    

    getch();

	closegraph();

    return 0;

}
