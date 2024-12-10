#include <iostream>
#include <graphics.h>
#include <cmath>

using namespace std;

const int x = 150, y = 100, latura = 100;
const int DIMENSIUNE_TABLA = 3;

int tabla[DIMENSIUNE_TABLA][DIMENSIUNE_TABLA] = {0}; // Matrice logică: 0 = gol, >0 = dimensiunea piesei
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

    closegraph();
    return 0;
}
