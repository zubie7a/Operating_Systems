#include <iostream>

using namespace std;

class Par {
// Declaration of the Par class
private:
// These are the private variables and methods of the class.
    int left;
    int right;
    // Two integer variables, left and right
    string state;
    // A string called state for storing a state

public:
// These are the public variables and methods of the class.
    Par(int l, int r):left(l),right(r) {
       if(l > r) { state = "left-unbalanced"; }
       if(l < r) { state = "right-unbalanced"; }
       if(l == r) { state = "balanced"; }
    }
    // Constructor method, will initialize the left and right values.
    // This wat of initializing is used with left(l), right(r). Then
    // a pair of braces comes up. They can be left empty, or some
    // program logic that happens once a class is initialized can
    // be put inside of them.

    Par(int n): left(n), right(n) {
        state = "balanced";
    }
    // What is this, another constructor? Yes! This is a proof of polymorphism
    // or overloading. In this case, if two parameters are passed, then the 1st
    // constructor will be called. If only one parameter is passed, then the 2nd
    // constructor will be called

    Par(): left(0), right(0) {
        state = "balanced";
    }
    // A third constructor, in the case zero variables are passed. It will initi-
    // alize both sides in 0, and since both are equal, by default its balanced.

    Par(string x, int n) {
        right = n;
        left = n;
        state = "balanced";
        cout << x << endl;
    }
    // A 4th constructor. This has the same number of arguments than the 2nd cons
    // tructor, but the arguments are different in type, so this has a different
    // function signature and as long as the function signatures differ its fine.
    // Par(string, int) != Par(int, int).
    // In this case, it will receive a string which it will print, and a number
    // which will be set to both left and right values. Notice that no assigning
    // was done like left(x) or right(x), and this is fine.

    int sum(){
        return left + right;
    }
    // A method that returns the sum of the left and right values

    void sub(int x){
        left -= x;
        right -= x;
    }
    // A method that permanently substracts an x value from both sides

    void inc(int x) {
        left += x;
        right += x;
    }
    // A method that permanently adds an x value to both sides

    string getState();
    // This function was only declared/prototyped.. but thats it..
};

string Par::getState() {
// This is the function that was previously declared/prototyped inside the Par
// class. It does the same as if it was put inside of there, but that way was
// inlined, whereas this one isn't. Its good to use inlined if the class is on-
// ly for use in a .cpp program but if its meant to be used as a header (or the
// user meant to implement part of the method) its better to do it this way.
// Doing it like this allows the header to contain only the definition of the
// function and variable signatures, but the user has the freedom to implement
// this function whoever it sees it fit.
    return state;
}

int main() {
    // Now, this will be about the use of classes in C++.
    int n, m;
    cout << "Enter two values to put into a certain data structure: ";
    cin >> n >> m;
    cout << endl << '\n' << "\n";
    cout << "Now, this structure will contain two values as 'left' and 'right'"
            "\nleft is: " << n << ", and right is " << m << endl;
    Par var1(n,m);
    // This creates an instance of the Par class named var1. Classes can either
    // be initializated or not. In this case, pass the parameters inside (...).
    cout << "The sum of both sides is: " << var1.sum() << endl;
    // cout << "The state of the structure is: " << var1.state << endl;
    // This can't be done since the state variable in var1 was declared private
    cout << "The state of the structure is: " << var1.getState() << endl;
    cout << "\n" << '\n' << endl;
    cout << "The possible states are:\n"
         << "Left unbalanced: left number is bigger than right number.\n"
         << "Right unbalanced: right number is bigger than left number.\n"
         << "Balanced: left and right numbers are both equal.\n";
    return 0;
    // Its good practice to use return values, since these programs may be exe-
    // cuted by other programs (like, using system calls) and they will return
    // a value which will be useful to know the exiting status of a program.
    // 0 usually means that it exited sucesfully.
}
