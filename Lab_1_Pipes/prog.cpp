#include <iostream>
#include <numeric>
#include <fstream>
#include <climits>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <queue>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <deque>
#include <vector>
#include <string>
#include <cstdlib>
#include <cassert>
#include <sstream>
#include <iterator>
#include <algorithm>  

using namespace std;

int main(int argc, char *argv[]){
    // This program will be run by the 'lab_1_pipes' program, or could be
    // ..run on its own. It receives first a couple of values, such as:
    // increment_step: a value to be added to a certain list of numbers
    // times_incremented: the times that value will be added to the list
    // Then, values are read until the 'end of input', each time a value
    // ..being read, being added the increment_step, by the amount that
    // ..times_incremented has defined. This is just a toy program to use
    // ..for showing how another program can run a program from within it,
    // ..and how that program could redirect this own program's I/O sources.    
    int value;
    vector <int> values;
    int increment_step;
    int times_incremented;
    cin >> increment_step;
    cin >> times_incremented;
    while(cin >> value){
        for(int i = 0; i < times_incremented; ++i){
            value += increment_step;
        }
        values.push_back(value);
    }
    for(int i = 0; i < values.size(); ++i){
        cout << values[i] << endl;
    }
    return 0;
    // This program will be called twice from the parent, but with different
    // ..inputs. The goal is to have the program running twice separatedly and
    // ..then after both instances of this program have ended running, doing 
    // ..stuff with both outputs, in this case, simply adding the values this
    // ..program returns as its output. This is to show how concurrent progra-
    // ..mming could help doing calculations in different programs and then
    // ..doing some nice stuff with their outputs, like adding them together.
}