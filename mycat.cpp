/*  Author: Jake Nemiroff

    Thursday, October 3rd, 2019

    This function is used to perform actions on a file in a filesystem
    in the same way the `cat` keyword would act on a file

*/

#include "FileManager.h"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc < 2) {
        
        cerr << "invalid number of arguments" << endl;
        
        return -1;
    }

    //loop through arguments given, and write contents to the command line
    for (int i = 1; i < argc; i++) {
        
        string fileName = argv[i];
        FileManager fm(fileName);
        ifstream inFileStream(fileName);

        if (inFileStream.is_open()) {
            
            cout << inFileStream.rdbuf() << endl;
        }
    }
    return 0;
}
