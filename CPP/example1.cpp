#include <iostream>
using namespace std;

int main(){
    int a = 5;
    // a is an integer with a value of 5
    int *b = &a;
    // b is an integer pointer that will be assigned a's pointer
    // &: ampersand operator, or the reference operator in case
    // of variables, will return this variable's address.
    // Each variable, besides its content, has an address, which
    // points in whcih position of memory this variable is.
    cout << "b value is: " << b << endl;
    // This will be a's address in memory, which may vary between
    // executions of the program.
    cout << "a value is: " << a << endl;
    // This is the value given to a, which will always be the same
    cout << "*b value is: " << *b << endl;
    // Applying the * operator to a pointer will dereference it and
    // obtain the value its pointing to, which will always be the same
    cout << "&a value is: " << &a << endl;
    // This is again applying the reference operator to a for getting
    // its address in memory, which may vary between executions.
    cout << "&b value is: " << &b << endl;
    // This will get the address to b.. which is a completely new
    // thing, b contains an address, but there's an address to b too!

    // Regarding pointers:
    // These values, or memory addresses, may be increased or decreased
    // by '1' with the ++ or -- operators, but this doesn't mean they'll
    // be moved to the next neighbor positions in memory, instead they'll
    // be moved by the size of whatever the pointer is pointing at, so:
    //
    // char: moved 1 byte
    // short: moved 2 bytes
    // int: moved 4 bytes
    // long: moved 8 bytes
    cout << "The size in bytes of char is: " << sizeof(char) << endl;
    cout << "The size in bytes of short is: " << sizeof(short) << endl;
    cout << "The size in bytes of int is: " << sizeof(int) << endl;
    cout << "The size in bytes of long is: " << sizeof(long) << endl;
    cout << "------------------------------" << endl;
    cout << "The size in byres of float is: " << sizeof(float) << endl;
    cout << "The size in bytes of double is: " << sizeof(double) << endl;
    // Thus, increasing or decreasing a pointer with the ++/-- operators
    // will move them on memory based on the size of their pointing types.

    // Regarding operation precedence:
    cout << *b++ << endl;
    // Increment pointer, and dereference unincremented address,
    // so it will print 5 (a's value) regularly, but the pointer
    // has been permanently affected (incremented).
    cout << *b << endl;
    // Now if we dereference b, we won't get 5 (a's value) because
    // the pointer was increased in the last line.
    cout << *b-- << endl;
    // This will also decrease the pointer, but dereference the
    // undecreased pointer, printing the same value as before.
    b++; // Lets increase the pointer again...
    cout << *--b << endl;
    // Now, this will decrease and dereference the decreased pointer!
    // so it will print again 5 (a's value).
}