#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define DEFAULT_SIDES 3
#define DEFAULT_LENGTH 1
#define PI 4 * atan(1.0)
#define MAX(X, Y) (((X) > (Y))? (X) : (Y))
// This is a macro definition, its like some code that will be inserted where-
// ever the compiler finds the first given thing. The first two are not really
// variables, but whenever the compiler finds these names, the following numb-
// ers will be inserted. There can be more complex macros such as:
#define forEach(list) for(int index = 0; index < list.size(); index++)
#define forRange(i1, i2) for(int index = i1; index < i2; index++)
// The piece of code at the right will be inserted at these places. Variables
// that are declared in macros will be available in the scope of the macro (in
// the case of ifs/fors/whiles, will be available in their inner scope).

class RegularShape{
// This class will define a regular shape, one of n sides, each one of length l
protected:
// You may wonder, what's the difference between 'private' and 'protected'?
// 'private' means that only, only, ONLY this class can access to these members.
// 'protected' means that this class, and any inheriting class can access them.
    int sides;
    int length;
public:
    RegularShape(int s=DEFAULT_SIDES, int l=DEFAULT_LENGTH) {
    // Default assignation is what is set as value in case it isn't passed
       sides = s;
       length = l;
    }
    // There's a thing to note, and is that based on the previous example, you
    // can declare a function many times with differing signatures without any
    // problem, if you declare two functions with the same signature:
    // RegularShape(int, int) == RegularShape(int, int) ... its not possible
    // But there's also another case where it isn't possible, with different
    // signatures, but with some implied ambiguity:
    // RegularShape(int, int=something) ~= RegularShape(int)
    // The 1st function takes two parameters and the 2nd takes one parameter
    // But the 1st function may not always be called with two parameters, as
    // it has a default parameter, it can be called with only one parameter
    // and the second one instantly becoming a default value, but them ambi-
    // guity arises as whether to call the first function or the second, thus
    // the compiler will stop with an error when presented with such ambiguity.
    int getSides() {
       return sides;
    }

    int getLength() {
       return length;
    }

    double getPerimeter() {
       return (double)(sides) * (double)(length);
    }

    double getApothem() {
       return (double)(length) / (2 * tan(PI / (double)(sides)));
    }

    double getArea() {
       double apothem = getApothem();
       double perimeter = getPerimeter();
       // Area: (1/2) * apothem * perimeter
       return 0.5 * apothem * perimeter;
    }
};

class Misc {
public:
   Misc() {}
   string getMessage() {
      return "Thats it for today! :-)";
   }
};

class Square : public RegularShape, public Misc {
// Inheritance! Rectangle will inherit from the RegularShape and Misc class.
// Just like functions with similar signature (differing only by default para-
// meters), there can also be ambiguity, in this case only with the function
// name, and its for functions that have the same name in the parent classes,
// even if they have a completely different signature. So, inheritance can't
// be done from two parents that have members (public, private or protected)
// that share the names.
    public:
        Square(int l=DEFAULT_LENGTH) : RegularShape(4, l) {
           // Even if the parent constructor is called and some stuff is done
           // within it like assigning variables, if something is done here
           // modifying these variables, the changes in here will happen after
           // whatever happens in the parent constructor, overwriting them.
        }
        // Whats this? The constructor from Square will instead call the const-
        // ructor of one of the parent classes! In this case RegularShape, with
        // the (possibly) given side length, and a fixed number of sides, four!
        // You could set up different constructor signatures so that with one
        // it constructs based on a parent class, and with another, it builds
        // by using another parent's class constructor, or with another, a con-
        // structor that belongs to this very class.
        double getArea() {
           return length * length;
        }
        // The parent RegularShape already had declared the getArea function,
        // and it has the same signature than this one, so whats the deal? This
        // is just another shape of polymorphism, and its overriding polymor-
        // hism. Before we saw OVERLOADING, and it was according to signatures,
        // declaring several slightly different functions (with the same name)
        // that were called depending on the parameters used. In this case even
        // with the same signature, this can be done because this is OVERRIDING
        // which is redefining an already existing function in a parent class.
        // The behavior of the method in the parent class is overriden by this.
};

int main() {
    vector< RegularShape > shapeList;
    forRange(3, 10) {
    // 'index' will be the iterator
       RegularShape rs(index);
       shapeList.push_back(rs);
    }
    cout << "Regular Polygons from 3 sides to 9 sides will be created.\n";
    cout << "All their sides will have length 1m so we can compare.\n";
    cout << "Their number of sides and areas are as follows:\n";
    forEach(shapeList) {
       // 'index' will be the iterator
       RegularShape rs = shapeList[index];
       cout << "Number of Sides: " << rs.getSides() << "\n"
            << "Area: " << rs.getArea() << "m^2\n";
    }
    cout << "A square with side-length of 5 will be created now.\n";
    Square sq(5);
    // A square with side-length of 5 will be created
    cout << "The area of this square is: " << sq.getArea() << "m^2" << endl;
    cout << sq.getMessage() << endl;
    // This is a method that its neither in Square, nor in RegularShape, but
    // its in the Misc class, another class where Square inherits from!
    return 0;
    // Its good practice to use return values, since these programs may be exe-
    // cuted by other programs (like, using system calls) and they will return
    // a value which will be useful to know the exiting status of a program.
    // 0 usually means that it exited sucesfully.
}