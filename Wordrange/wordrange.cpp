#include <iostream>
#include "AVL.h"
#include <stack>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector> 
#include <algorithm>
#include <sstream>
#include <cstring>
using namespace std;


int main(int argc, char** argv)
{
  if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./treewrapper <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    ifstream input; // stream for input file
    ofstream output; // stream for output file

    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file

    string command; // to store the next command and operation
    char *com, *valstr, *op; // for using with strtok, strtol
    string val; // the value from the command

    AVL myAVL; // initializing the linked list
        

    while(getline(input,command)) // get next line of input, store as repeat
    {
        if (command.length() == 0) // command is empty
            continue;
        com = strdup(command.c_str()); // annoying, first copy string into a "C-style" string
        op = strtok(com, " \t"); //tokenize command on whitespace, first token is operation

        valstr = strtok(NULL, " \t"); // next token is value, as string (check out documentation on strtok, to understand the parsing)
       val = valstr;

         
        if(strcmp(op,"i") == 0) // insert into list
        {
//             output << "Insert ";
//             output << val << endl;
            myAVL.insert(val);
        }
        if(strcmp(op,"d") == 0) // delete from list
        {
            cout << "Delete " << val << endl;
            free(myAVL.deleteKey(val)); // delete the value, and free the memory
        }
        if(strcmp(op,"f") == 0) // delete from list
        {
            string message;
            if(myAVL.find(val)) // yes, val is found in AVL
                message = " found";
            else
                message = " not found";
            cout << val + message << endl;
            output << val + message << endl;
        }
        if(strcmp(op,"r") == 0) // determine the range, given a min and max
        {
          valstr = strtok(NULL, " \t"); // next token is value, as string (check out documentation on strtok, to understand the parsing)
          string val2 = valstr;
          output << myAVL.range(val, val2) << endl;
//           cout << val << val2;
        }
   }
}