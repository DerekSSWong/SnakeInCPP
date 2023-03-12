#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
bool isQuitting;
const int height=20;
const int width=20;

int headX,headY,fruitX,fruitY,score;

int tailX[100], tailY[100], nTail;

enum eDirction {STOP=0, UP, DOWN, LEFT, RIGHT};
eDirction dir;

void Setup() {
    gameOver = false;
    isQuitting = false;
    headX = width/2; //Initial position, start in the middle
    headY = height/2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    nTail = 0;
    score = 0;
}

void Draw() {

    system("CLS"); //Clear screen

    if (!gameOver) {
        //Upper wall
        for (int i=0; i<width; i++) {
            cout<<"#";
        }cout<<endl;

        for (int i=0; i<height; i++) {
            for(int j=0; j<width; j++) {

                //Side walls
                if(j==0 || j==width-1) {
                    cout<<"#";
                }

                //Head
                else if (i==headY && j==headX) {
                    cout<<"Q";
                } 
                
                //Fruit
                else if (i==fruitY && j==fruitX) {
                    cout<<"F";
                } 
                
                //Tail
                else {
                    bool printed = false;
                    for (int k=0; k<nTail; k++) {
                        if (i == tailY[k] && j==tailX[k]) {
                            cout<<"o";
                            printed = true;
                        }
                    }
                    if (!printed) {cout<<" ";}
                }
            }cout<<endl;
        }
    }

    else {
        cout<<"GAME OVER"<<endl;
        cout<<"PRESS R TO RESTART"<<endl;
    }
    

    for (int i=0; i<width; i++) {
        cout<<"#";
    }cout<<endl;

    cout<<"Score: "<< score <<endl;
    cout<<"Restart (r)    Quit (x)"<<endl;
}

void Input() {
    if (_kbhit()) {
        switch(_getch()){
            case 'w':
                if (dir != DOWN) {dir = UP;}
                break;
            case 'a':
                if (dir != RIGHT) {dir = LEFT;}
                break;
            case 's':
                if (dir != UP) {dir = DOWN;}
                break;
            case 'd':
                if (dir != LEFT) {dir = RIGHT;}
                break;
            case 'x':
                isQuitting = true;
                break;
            case 'r':
                Setup();
                dir = STOP;
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

    tailX[0] = headX; //"head" is the start of "tail"
    tailY[0] = headY;

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
            headY--;
            break;
        case DOWN:
            headY++;
            break;
        case LEFT:
            headX--;
            break;
        case RIGHT:
            headX++;
            break;
    }

    if (headX<0 || headX>width || headY<0 || headY>height) {
        gameOver = true;
    }

    for (int i=0; i<nTail; i++) {
        if (headX == tailX[i] && headY==tailY[i]) {
            gameOver = true;
        }
    }

    if (headX==fruitX && headY==fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main() {
    Setup();
    while(!isQuitting) {
        Draw();
        Input();
        Logic();
        Sleep(40);
    }
}