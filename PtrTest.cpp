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


class Food {
    protected:
        string visual;
        int score;
    public:
        const string& getVisual() const {return visual;}
        int getScore() const {return score;}

};

class SmallFood : public Food {
    public:
        SmallFood(const string&& v) {
            visual = v;
            score = 1;
        }
};

class FoodManager {
    private:
        
    public:
        vector<unique_ptr<const Food>> foodList;
        void addFood(unique_ptr<const Food> food) {
            foodList.push_back(forward<unique_ptr<const Food>>(food));
        }
        unique_ptr<const Food>& getRandFood() {
            if (foodList.size() <= 0) {
                cout<<"NONE"<<endl;
            }
            return foodList[rand()%foodList.size()];
        }

};

string getVis(unique_ptr<const Food>& foodptr) {
    return foodptr -> getVisual();
}

//unique_ptr<FoodManager> foodmanager = make_unique<FoodManager>;

int testNum = 12;
FoodManager foodManager;
void editor() {
    foodManager.addFood(make_unique<const SmallFood>("x"));
    foodManager.addFood(make_unique<const SmallFood>("y"));
};

int randIndex;
void rando() {
    randIndex = rand()%foodManager.foodList.size();
}
int main() {
    editor();
    rando();
    cout<<foodManager.foodList[randIndex] -> getVisual()<<endl;
    rando();
    cout<<foodManager.foodList[randIndex] -> getVisual()<<endl;
    rando();
    cout<<foodManager.foodList[randIndex] -> getVisual()<<endl;
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