#include <iostream>
#include <graphics.h>
#include <cmath>
#include "menu"
using namespace std;
void deseneazaMeniuPrincipal() {
   //cleardevice();
//readimagefile("poza.bmp",100,110,200,200);
    settextstyle(3, HORIZ_DIR, 4);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setcolor(RED);
    outtextxy(320, 100, "GOBBLET");
    setcolor(GREEN);
    outtextxy(320, 50, "GOBBLERS");

    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    setcolor(WHITE);

    rectangle(200, 200, 440, 260);
    outtextxy(310, 230, "1. Start Joc");

    rectangle(200, 280, 440, 340);
    outtextxy(310, 310, "2. Instructiuni");

    rectangle(200, 360, 440, 420);
    outtextxy(310, 400, "3. Iesire");
      readimagefile("gg.bmp",0,0,getmaxx(),getmaxy());
}
void cumjoci()
{
    cleardevice();
    settextstyle(3, HORIZ_DIR, 4);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setcolor(RED);
    outtextxy(320, 100, "GOBBLET");
    setcolor(GREEN);
    outtextxy(320, 50, "GOBBLERS");

    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    setcolor(WHITE);

    rectangle(200, 200, 480, 260);
    outtextxy(330, 230, "SINGLEPLAYER-vs-PC");

    rectangle(200, 280, 480, 340);
    outtextxy(330, 310, "MULTIPLAYER");
}
/*int gestioneazacumjoci()
{
int x, y;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (x >= 200 && x <= 480 && y >= 200 && y <= 260) {
                return 1;
            }
            else if (x >= 200 && x <= 480 && y >= 280 && y <= 340) {
                return 2;
        }
    }
}
}*/
int gestioneazaIntrariMeniu() {
    int x, y;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (x >= 200 && x <= 440 && y >= 200 && y <= 260) {
                return 1;
            }
            else if (x >= 200 && x <= 440 && y >= 280 && y <= 340) {
                return 2;
            }
            else if (x >= 200 && x <= 440 && y >= 360 && y <= 420) {
                return 3;
            }
        }
    }
}

void afiseazaInstrucțiuni() {
    cleardevice();
    setbkcolor(BLACK);
    //clearviewport();
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 2);
    setcolor(YELLOW);
    outtextxy(320, 100, "INSTRUCTIUNI");

    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 1);
    setcolor(WHITE);
    outtextxy(300, 150, "1. Selecteaza pionul pe care doresti sa il muti.");
    outtextxy(300, 180, "2. Aseaza pionul pe o casuta goala sau peste unul mai mic.");
    outtextxy(300, 210, "3. Castiga prin alinierea a 3 piese de aceeasi culoare.");
    outtextxy(300, 240, "4. Pentru a reveni, apasa click oriunde.");

    clearmouseclick(WM_LBUTTONDOWN);
}

const int x = 150, y = 100, latura = 100;
const int DIMENSIUNE_TABLA = 3;

int tabla[DIMENSIUNE_TABLA][DIMENSIUNE_TABLA] = {0};
int centruX, centruY, raza;

void deschideGrafica() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "c:\\tc\\bgi");
}

void deseneazaTabla() {
       for (int i = 1; i < 3; i++) {

        setcolor(GREEN);
        line(x, y + i * latura, x + 3 * latura, y + i * latura);

    }
    for (int i = 1; i< 3; i++) {
        setcolor(FOREGROUND_RED );
        line(x + i * latura, y, x + i * latura, y + 3 * latura);
    }
}

void deseneazaCerc(int cx, int cy, int r, int culoare) {
    setcolor(culoare);
    setfillstyle(SOLID_FILL, culoare);
    fillellipse(cx, cy, r, r);
}

void deseneazaPioni() {
    for (int i = 1; i <= 3; i++) {
        deseneazaCerc(30, 50 + 65 * i, 10 * i, RED);
        deseneazaCerc(100, 50 + 65 * i, 10 * i, RED);
        deseneazaCerc(getmaxx() - 30, 50 + 65 * i, 10 * i, GREEN);
        deseneazaCerc(getmaxx() - 100, 50 + 65 * i, 10 * i, GREEN);
    }
}

bool esteClickInCerc(int clickX, int clickY, int centruX, int centruY, int raza) {
    int dx = clickX - centruX;
    int dy = clickY - centruY;
    return (dx * dx + dy * dy) <= (raza * raza);
}

bool poatePunePiesa(int linie, int coloana, int dimensiune) {
    return tabla[linie][coloana] == 0 || tabla[linie][coloana] < dimensiune;
}

void actualizeazaTabla(int linie, int coloana, int dimensiune) {
    tabla[linie][coloana] = dimensiune;
}

void gestioneazaMutari() {
    bool selectat = false;
    int culoareSelectata = 0;
    int dimensiuneSelectata = 0;

    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            clearmouseclick(WM_LBUTTONDOWN);
            int mouseX = mousex();
            int mouseY = mousey();

            if (!selectat) {
                // Selectarea unui pion
                for (int i = 1; i <= 3; i++) {
                    // Pioni roșii
                    if (mouseX < 150) {
                        centruX = (mouseX < 65) ? 30 : 100;
                        centruY = 50 + 65 * i;
                        raza = 10 * i;

                        if (esteClickInCerc(mouseX, mouseY, centruX, centruY, raza)) {
                            selectat = true;
                            culoareSelectata = RED;
                            dimensiuneSelectata = 10 * i;
                            setcolor(BLACK);
                            setfillstyle(SOLID_FILL, BLACK);
                            fillellipse(centruX, centruY, raza, raza);
                            break;
                        }
                    }
                    // Pioni verzi
                    if (mouseX > getmaxx() - 150) {
                        centruX = (mouseX > getmaxx() - 65) ? getmaxx() - 30 : getmaxx() - 100;
                        centruY = 50 + 65 * i;
                        raza = 10 * i;

                        if (esteClickInCerc(mouseX, mouseY, centruX, centruY, raza)) {
                            selectat = true;
                            culoareSelectata = GREEN;
                            dimensiuneSelectata = 10 * i;
                            setcolor(BLACK);
                            setfillstyle(SOLID_FILL, BLACK);
                            fillellipse(centruX, centruY, raza, raza);
                            break;
                        }
                    }
                }
            } else {
                // Mutarea pionului pe tablă
                int linie = (mouseY - y) / latura;
                int coloana = (mouseX - x) / latura;

                if (linie >= 0 && linie < DIMENSIUNE_TABLA && coloana >= 0 && coloana < DIMENSIUNE_TABLA) {
                    if (poatePunePiesa(linie, coloana, dimensiuneSelectata)) {
                        centruX = x + coloana * latura + latura / 2;
                        centruY = y + linie * latura + latura / 2;


                        deseneazaCerc(centruX, centruY, dimensiuneSelectata, culoareSelectata);

                        actualizeazaTabla(linie, coloana, dimensiuneSelectata);

                        selectat = false;
                    }
                }
            }
        }
    }
}

int main() {

    deschideGrafica();

    while (true) {
        deseneazaMeniuPrincipal();
        int optiune = gestioneazaIntrariMeniu();

        if (optiune == 1) {
            while (true) {
                cumjoci();
                int mod = gestioneazacumjoci();
                if(mod==1)
                {
            cleardevice();settextstyle(3, HORIZ_DIR, 4);
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            setcolor(RED);
            outtextxy(320, 25, "GOBBLET");
            setcolor(GREEN);
            outtextxy(320, 50, "GOBBLERS");

            setbkcolor(WHITE);
            deseneazaTabla();
            deseneazaPioni();
            gestioneazaMutari();
                }

            else{
            cleardevice();
            settextstyle(3, HORIZ_DIR, 4);
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            setcolor(RED);
            outtextxy(320, 25, "GOBBLET");
            setcolor(GREEN);
            outtextxy(320, 50, "GOBBLERS");

            setbkcolor(WHITE);
            deseneazaTabla();
            deseneazaPioni();
            gestioneazaMutari();
            }
        }
        }
        else if (optiune == 2)
            afiseazaInstrucțiuni();

        else if (optiune == 3) {

            closegraph();
            exit(0);
        }
    }

    return 0;
}
