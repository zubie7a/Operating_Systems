#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

string intToString(int i) {
    stringstream ss;
    ss << i;
    // Put the int i into the stringstream.
    return ss.str();
    // Return the contents of the stringstream!
}

int stringToInt(string s) {
    int i;
    stringstream ss;
    ss << s;
    // Put the string s into the stringstream
    ss >> i;
    // Read something from the stringstream into i, C++ will assume its an int.
    return i;
}

int main(){
    cout << "#### C++ style ####" << endl;
    // C++s style is easier but.. slower, or, not as crafty.
    string stuff;
    // Declaring a string is as simple as this.
    cout << "Write a word: ";
    // Printing is as simple as this.
    cin >> stuff;
    // Reading a string is as simple as this. No 'buffer' limits. cin will read
    // up to a 'whitespace' character, which could be tab, space, or newline.
    cout << "The read word was: " << stuff << endl << "\n";
    // endl or "\n" will put a newline.
    cout << "Write some stuff and then press enter: ";
    getchar();
    // Mind that doing cins before a getline has its precautions, since cin wo-
    // n't get newlines, but getline will, so if new lines aren't caught before
    // getline and a previous cin had ended reading a 'line', then the getline
    // will only get the \n finishing that line.
    getline(cin, stuff);
    // This will read a whole line and terminate it at \n
    // ...
    // cin and cout are input and output streams related to standard input and
    // standard output, but the user can create streams too, 'input' streams
    // using strings as sources, and 'output' streams to put strings into.
    cout << "The whole line inputted was: " << stuff <<  "\n" << endl;
    // Now, lets proceed to file input and output
    ifstream inf("example3IN.txt");
    // Lets create an input file (if) stream using a file name (relative path)
    cout << "The contents of the read file are: " << endl;
    while(inf >> stuff) {
        cout << stuff << endl;
    }
    cout << endl;
    // Lets print another newline just.. because.
    ofstream outf("example3OUT.txt");
    // Lets create an output file (of) stream using a file name (relative path)
    for(int k = 0; k < 7; k++) {
        outf << k + 1 << " ";
    }
    outf << endl;
    cout << "You can't see it here in standard output but a file was written!"
         << endl << "It contains the numbers from 1 to 7." << endl << endl;
    string s = "7 8 9 10 11 12 13 14";
    stringstream ss(s);
    // We'll now use the string s as a source to feed the stringstream ss. Inp-
    // out and output streams can be thought of as simply text streams with the
    // types being assigned either by user specification (C) or by type of var-
    // iable read inference (C++).
    cout << "Lets print the numbers from 7 to 14." << endl;
    while(ss >> stuff) {
    // This advances the cursor of the stream until 'end of file / stream'
    // Nonetheless, even if the end is reached, when querying afterwards for
    // the contents of ss they'll appear intact.
        cout << stuff << " ";
    }
    cout << endl << endl;
    ss.clear();
    // get rid of the contents of ss.
    ss << "Hi there! This is new content";
    // Stuff could be also put into the stringstream.
    // Now lets see what's inside the stringstream
    cout << "Contents of the stringstream: " << ss.str() << endl;
    // A good use of streams can be converting between types like from a number
    // to a string and viceversa.
    int z = 721;
    s = intToString(z);
    string res = "Now that the number " + s +
                 " is a string, it can be appended!";
    cout << res << endl << endl;
    // Also remember that getline(x, s) function. s is the place where the read
    // line will be put, but x, which usually is seen as cin, can be any input
    // stream, be it from a file, or from a string!
    return 0;
    // Its good practice to use return values, since these programs may be exe-
    // cuted by other programs (like, using system calls) and they will return
    // a value which will be useful to know the exiting status of a program.
    // 0 usually means that it exited sucesfully.
}