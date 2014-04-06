#include <sys/types.h> // Data types, specially useful for pid_t and pthread_t if used
#include <sys/wait.h>  // Declarations for waiting, like, waiting for a certain pid
#include <unistd.h>    // Standard symbolic constants and types, execs, fork, dups, etc
#include <stdlib.h>    // Standard library definitions, exit, type conv, memory allocs  
#include <iostream>    // Standard C++ input/output
#include <fstream>     // File stream options
#include <sstream>     // String stream options
#include <fcntl.h>     // File control options
#include <stdio.h>     // Standard buffered I/O
#include <vector>      // Vector and related ops

#define DEBUG cout << __FILE__ << " : " << __LINE__ << endl

// sys/types.h -> http://pubs.opengroup.org/onlinepubs/009696699/basedefs/sys/types.h.html
// sys/wait.h  -> http://pubs.opengroup.org/onlinepubs/009696699/basedefs/sys/wait.h.html
// unistd.h    -> http://pubs.opengroup.org/onlinepubs/009696699/basedefs/unistd.h.html
// stdlib.h    -> http://pubs.opengroup.org/onlinepubs/009696699/basedefs/stdlib.h.html
// fcntl.h     -> http://pubs.opengroup.org/onlinepubs/009696699/basedefs/fcntl.h.html
// stdio.h     -> http://pubs.opengroup.org/onlinepubs/009696699/basedefs/stdio.h.html

using namespace std;

struct Inputs {
    vector<string> inputs;
    // A vector of strings containing inputs
    int size(); // Declaration of a function
    void push_back(string s); // Another one!
    void clear(); // This is basically a struct
    // ..that works pretty much as a vector, but
    // ..works as an example for operator over-
    // ..riding and the definition of functions!
    string & operator [] (int i) {
        return this->inputs[i];
    }
    // This is so after having a 'Input input'
    // ..one could call a member of it by wri-
    // ..ting 'input[i]' and getting its ref-
    // ..erence just like directly accessing
    // ..the 'inputs' vector of strings.
};

int Inputs::size() {
    return this->inputs.size();
    // Definition of the size function in the
    // ..user defined 'Inputs' struct.
}

void Inputs::push_back(string s) {
    this->inputs.push_back(s);
}

void Inputs::clear(){
    this->inputs.clear();
}

// This program will have several 'exiting' codes, such as:
//  0: terminated successfully.
// ------ if the program encounters an 'exception' ------
//  1: was not run with zero arguments.
// -1: pipes could not be created.
// -2: program could not be forked.
// -3: standard I/O failed to be redirected.
// -4: secondary program failed [to run|while running].

void error(int val){
    cerr << "Error: ";
    switch(val){
    case  1: cerr << "this program can't be run with any parameters." << endl;
    case -1: cerr << "pipes could not be created." << endl;
    case -2: cerr << "program could not be forked." << endl;
    case -3: cerr << "standard I/O could not be redirected." << endl;
    case -4: cerr << "secondary program could not be run." << endl;
    default: return;
    }
    exit(val);
}

int main(int argc, char *argv[]) {
    if(argc != 1){
        error(1);
    }
    int pip1[2];
    int pip2[2];
    // Pair of pipes for communication between the main (parent) process
    // ..and the first children, which will run a program on its own.
    int pip3[2];
    int pip4[2];
    // Pair of pipes for communication between the main (parent) process
    // ..and the second children, which will run a program on its own.
    if ((pipe(pip1) < 0) || (pipe(pip2) < 0) ||
        (pipe(pip3) < 0) || (pipe(pip4) < 0)){
        // If creating either pipe fails, then the program will terminate
        error(-1);
    }
    // pipe(..) creates the reading and writing ends of a pipe
    // a pipe is a mechanism for process intercommunication
    // ..this makes the elements of the arrays into file descriptors
    // pipes only work in one direction, so for having one process give
    // ..input to another process, and then get the other process output
    // ..into the first process, one needs to have two pipes.
    pid_t pid1, pid2;
    if((pid1 = fork()) < (pid_t) 0){
        // If forking the program fails, the program will terminate
        error(-2);
    }
    // fork will create a child process, which will have 0 as the pid
    // ..which will help identifying between them as child or parent
    // Both parent and child share the state of the program up to here.
    if(pid1 == (pid_t) 0){    
        // ---- Code to run if its the first children!!! ---- //
        close(pip4[0]);
        close(pip4[1]);
        close(pip3[0]);
        close(pip3[1]);
        // These pipes are of no concern whatsoever to this children
        // ..as these are related to the other (second) children
        close(pip1[1]);
        close(pip2[0]);
        // Ends related to the parent
        // Close then the unused ends of the pipe
        if((dup2(pip1[0], 0) < 0) || (dup2(pip2[1], 1) < 0)){
            // Redirect standard input and output
            // dup2(pip1[0], 0) ... 0 - STDIN
            // dup2(pip2[1], 1) ... 1 - STDOUT (2 - STDERR)
            // If redirecting the standard I/O fails the program will terminate
            error(-3);
        }
        // At some point whatever the child outputs, will be the input
        // ..in the father process, the father will do stuff until it
        // ..needs this children input, so at some point it will wait
        // ..for some sort of signal sent from the children indicating
        // ..it has already finished doing something it was doing.
        // Now that output has been redirected, run the secondary program
        if(execl("./prog", "prog", (char *) 0) < 0){
            // If running the secondary program fails the program will terminate
            error(-4);
        }
        // execl: path, arguments (including program name), null finisher.
        // This executed program will have pip1[0] as STDIN, pip2[1] as STDOUT
        // Some say NULL instead of (char *) 0 creates undefined behavior
        close(pip1[0]);
        close(pip2[1]);
        // As MJ once said.. kind of, 'Remember to always close pipes'
    }
    else{ 
        if((pid2 = fork()) < (pid_t) 0){
            // If forking the program again fails, the program will terminate
            error(-2);
        }
        if(pid2 == (pid_t) 0){
            // ---- Code to run if its the second children!!! ---- //
            close(pip1[0]);
            close(pip1[1]);
            close(pip2[0]);
            close(pip2[1]);
            // These pipes are of no concern whatsoever to this children
            // ..as these are related to the other children
            close(pip3[1]);
            close(pip4[0]);
            // Ends related to the parent
            if((dup2(pip3[0], 0) < 0) || (dup2(pip4[1], 1) < 0)){
                // Redirect standard input and output
                // dup2(pip3[0], 0) ... 0 - STDIN
                // dup2(pip4[1], 1) ... 1 - STDOUT (2 - STDERR)
                // If redirecting the standard I/O fails the program will terminate
                error(-3);
            }
            // Now that output has been redirected, run the secondary program
            if(execl("./prog", "prog", (char *) 0) < 0){
                // If running the secondary program fails, the program will terminate
                error(-4);
            }
            close(pip3[0]);
            close(pip4[1]);
            // As MJ once said.. kind of, 'Remember to always close pipes'
        }
        else {
            // ---- Code to run if its the parent!!! ---- //
            close(pip1[0]);
            close(pip2[1]);
            // Unused ends related to the first children
            close(pip3[0]);
            close(pip4[1]);
            // Unused ends related to the second children
            // Close then the unused pipes of the pipe
            ostringstream stream1;
               // An output string stream which will contain all the input that is
               // ..going to be passed to the program that will be executed.
            int status1;
            // Passed to the wait function
            string response1 = "";
            // Where the responses from the programs the children will run
            // ..are going to be storaged for later use in the parent process.
            string increment_step = "2";
            string times_increased = "1742";
            // Parameters of the program to be executed
            FILE *sysin1  = fdopen(pip1[1], "w");
            FILE *sysout1 = fdopen(pip2[0], "r");
            // Open FILEs to read/write in pipes, this will go to the 1st children
            // fdopen associates streams with file descriptors
            Inputs inputs1;
            // This is a structure which will contain inputs, just for the example
            inputs1.push_back(increment_step);
            inputs1.push_back(times_increased);
            for(int i = 0; i < 10; i++) {
                ostringstream ss;
                // A string stream to put things into for 'output'
                // ..its the counterpart of stringstream which gets
                // ..stuff from inside a string like a input stream.
                ss << i;
                // This is kind of an easy way to convert numbers into strings
                inputs1.push_back(ss.str());
            }
            for(int i = 0; i < inputs1.size(); ++i){
                stream1 << inputs1[i] << "\n";
            }
            fprintf(sysin1, (stream1.str()).c_str());
            // 'prints' the string storaged in stream1 (input stream) into the file 
            // ..which uses the pipe that the child process will use as standard
            // ..input for the program it will run.
            fclose(sysin1);
            // Close the file because it no longer needs any manipulation
            // Now, do the same for the 2nd children, which will have a little
            // ..different input, but not that much different that is.

            // ---- PREPARATION OF INPUT AGAIN, FOR THE SECOND CHILDREN ---- //
            ostringstream stream2;
            int status2;
            string response2 = "";
            increment_step = "3";
            times_increased = "721";
            FILE *sysin2  = fdopen(pip3[1], "w");
            FILE *sysout2 = fdopen(pip4[0], "r");
            Inputs inputs2;
            inputs2.push_back(increment_step);
            inputs2.push_back(times_increased);
            for(int i = 0; i < 10; i++) {
                ostringstream ss;
                ss << i;
                inputs2.push_back(ss.str());
            } 
            for(int i = 0; i < inputs2.size(); ++i){
                stream2 << inputs2[i] << "\n";
            }
            fprintf(sysin2, (stream2.str()).c_str());
            fclose(sysin2);
            // --- END OF SECOND CHILDREN INPUT PREPARATION --- //

            waitpid(pid1, &status1, 0);
            waitpid(pid2, &status2, 0);
            // This will make the parent wait for both children to finish
            char c;
            while((c = fgetc(sysout1)) != EOF){
                response1 += c;
            }
            fclose(sysout1);
            close(pip1[1]);
            close(pip2[0]);
            // Read the response from the first children char by char, and
            // ..then close the file descriptor related to the output and
            // ..the pipes used to communicate with the first children
            while((c = fgetc(sysout2)) != EOF){
               response2 += c;
            }
            fclose(sysout2);
            close(pip3[1]);
            close(pip4[0]);
            // Read the response from the second children char by char, and
            // ..then close the file descriptor related to the output and
            // ..the pipes used to communicate with the second children
            stringstream ss1(response1);
            stringstream ss2(response2);
            // Make a stringstream of both responses, the results of both
            // ..programs ran by the child processes are stored in two single
            // ..huge strings, and stringstreams could be constructed from 
            // ..those very strings to extract individual results separated
            // ..by whitespaces, tabs or line breaks.
            vector<int> res1;
            vector<int> res2;
            // Where the individual results, extracted from the outputs are
            // ..going to be stored for doing stuff with them later.
            int res;
            cout << "The output from the first child is:" << endl;
            while(ss1 >> res){
                res1.push_back(res);
                cout << res << endl;
            }
            cout << "The output from the second child is:" << endl;
            while(ss2 >> res){
                res2.push_back(res);
                cout << res << endl;
            }
            cout << "The combined output from both children is:" << endl;
            for(int i = 0; i < min(res1.size(), res2.size()); ++i){
                cout << res1[i] + res2[i] << endl;
            }
        }
    }
    // The program successfully terminated!!!
    exit(0);
}