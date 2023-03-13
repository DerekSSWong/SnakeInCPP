#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <memory>

using namespace std;

class NumberBox {
    private:
        int number;
    public:
        NumberBox(int i) {number = i;}
        int getNumber() {return number;}
        void setNumber(int i) {number = i;}
        void printNumber() {cout<<number<<endl;}
};

int getFromPointer(const unique_ptr<NumberBox>& nbox) {
    return nbox -> getNumber();
};


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

//unique_ptr<FoodManager> foodmanager = make_unique<FoodManager>;

int main() {
    unique_ptr<FoodManager> foodmanager = make_unique<FoodManager>(10,10);
    foodmanager -> addFood("1",1);
    foodmanager -> addFood("2",2);
    foodmanager -> addFood("3",3);
    foodmanager -> shuffle();
}

// int main() {

//     //Const unique_ptr cannot be moved
//     const unique_ptr<NumberBox> constPtrBox = make_unique<NumberBox>(1);
//     constPtrBox -> printNumber();
//     constPtrBox -> setNumber(2);
//     constPtrBox -> printNumber();

//     //Passing pointers into a function
//     //const unique_ptr<X>& foo
//     const unique_ptr<NumberBox> ptrBox = make_unique<NumberBox>(10);
//     cout<<getFromPointer(ptrBox)<<endl;

//     //Creating a vector to store pointers in
//     vector<unique_ptr<NumberBox>> boxes;
//     boxes.push_back(make_unique<NumberBox>(100));
//     cout<<boxes[0] -> getNumber()<<endl;

//     vector<unique_ptr<NumberBox>> numBoxes; //Make vector
//     numBoxes.push_back(make_unique<NumberBox>(123)); //Put unique_ptr in vector
//     const vector<unique_ptr<NumberBox>>& constRef = numBoxes; //Create const ref of vector
//     cout<<constRef[0] -> getNumber()<<endl; //Prints 123

//     //ref = someVector
//     //somefunction(ref)
//     //print ref


// }