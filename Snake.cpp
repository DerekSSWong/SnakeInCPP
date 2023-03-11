#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int height=20;
const int width=20;

int x,y,fruitX,fruitY,score;

int tailX[100], tailY[100], nTail;

enum eDirction {STOP=0, UP, DOWN, LEFT, RIGHT};
eDirction dir;

void Setup() {
    gameOver = false;
    x=width/2; //Initial position, start in the middle
    y=height/2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    nTail = 0;
}

void Draw() {

    system("CLS");

    for (int i=0; i<width; i++) {
        cout<<"#";
    }cout<<endl;

    for (int i=0; i<height; i++) {
        for(int j=0; j<width; j++) {
            if(j==0 || j==width-1) {
                cout<<"#";
            }
            else if (i==y && j==x) {
                cout<<"Q";
            } else if (i==fruitY && j==fruitX) {
                cout<<"F";
            } else {
                bool printed = false;
                for (int k=0; k<nTail; k++) {
                    if (i == tailY[i] && j==tailX[i]) {
                        cout<<"o";
                        printed = true;
                    }
                }
                if (!printed) {cout<<" ";}
                
            }
        }cout<<endl;
    }

    for (int i=0; i<width; i++) {
        cout<<"#";
    }cout<<endl;
}

void Input() {
    if (_kbhit()) {
        switch(_getch()){
            case 'w':
                dir = UP;
                break;
            case 'a':
                dir = LEFT;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'd':
                dir = RIGHT;
                break;
            default:
                dir = STOP;
                break;
        }
    }
}

void Logic() {

    int prevX = tailX[0];
    int prevY = tailY[0];

    int prev2X, prev2Y; //buffer variables

    tailX[0] = x; //"head" is the start of "tail"
    tailY[0] = y;

    for(int i=1; i<nTail; i++) {
        prev2X = tailX[i]; //buffer current tail location
        prev2Y = tailY[i];
        tailX[i] = prevX; //Update tail list
        tailY[i] = prevY;
        prevX = prev2X; //Buffered current tail location will be the next prevTail location
        prevY = prev2Y;
    }

    switch(dir) {
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
    }

    if (x<0 || x>width || y<0 || y>height) {
        gameOver = true;
    }

    for (int i=0; i<nTail; i++) {
        if (x==tailX[i] && y==tailY[i]) {
            gameOver = true;
        }
    }

    if (x==fruitX && y==fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main() {
    Setup();
    while(!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(40);
    }
}