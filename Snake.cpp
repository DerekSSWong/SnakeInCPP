#include <iostream>
#include <conio.h>
#include <windows.h>
#include <memory>
#include <vector>

using namespace std;

bool gameOver;
bool isQuitting;
const int height=20;
const int width=20;

int headX,headY,fruitX,fruitY,score;

int tailX[100], tailY[100], nTail;

enum eDirction {STOP=0, UP, DOWN, LEFT, RIGHT};
eDirction dir;

class FoodType {
    private:
        string visual;
        int score;
    public:
        FoodType(string v, int s) {visual = v; score = s;}
        const string& getVisual() {return visual;}
        const int& getScore() {return score;}
};

class FoodManager {
    private:
        vector<FoodType> foodList;
        int width, height, currentFoodIndex, x, y;
        FoodType& getCurrentFood() {return foodList[currentFoodIndex];}
    public:
        FoodManager(int w, int h) {
            width = w;
            height = h;
        }
        void addFood(string v, int s) {
            FoodType x(v,s);
            foodList.push_back(x);
        }
        void shuffle() {
            x = rand()%width;
            y = rand()%height;
            currentFoodIndex = rand()%foodList.size();
            //cout<<currentFoodIndex<<endl;
        }
        const string& getVisual() {return getCurrentFood().getVisual();}
        const int& getScore() {return getCurrentFood().getScore();}
        const int& getX() {return x;}
        const int& getY() {return y;}
};

void Setup(unique_ptr<FoodManager>& fm) {
    gameOver = false;
    isQuitting = false;
    headX = width/2; //Initial position, start in the middle
    headY = height/2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    nTail = 0;
    score = 0;
    fm -> shuffle();
}

void Draw(unique_ptr<FoodManager>& fm) {

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
                else if (i==fm->getY() && j==fm->getX()) {
                    cout<<fm->getVisual();
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
    //cout<<pfood.getX()<<endl;
}

void Input(unique_ptr<FoodManager>& fm) {
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
                Setup(fm);
                dir = STOP;
                break;
            default:
                dir = STOP;
                break;
        }
    }
}

void Logic(unique_ptr<FoodManager>& fm) {

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

    if (headX==fm->getX() && headY==fm->getY()) {
        score += fm -> getScore();
        fm -> shuffle();
        nTail++;
    }
}

int main() {
    unique_ptr<FoodManager> foodmanager = make_unique<FoodManager>(10,10);
    foodmanager -> addFood("1",1);
    foodmanager -> addFood("2",2);
    foodmanager -> addFood("3",3);
    Setup(foodmanager);
    while(!isQuitting) {
        Draw(foodmanager);
        Input(foodmanager);
        Logic(foodmanager);
        Sleep(40);
    }
}