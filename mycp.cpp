/*  Author: Jake Nemiroff

    Thursday, October 3rd, 2019

    This function is used to perform actions on a file in a filesystem
    in the same way the `cp` keyword would act on a file

*/

#include "FileManager.h"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 3) {
        
        cerr << "invalid number of arguments" << endl;
        
        return -1;  //return -1 on failure
    }

    string fileName = argv[1];

    string destinationFile = argv[2];

    FileManager fm(fileName);

    if (strcmp(fm.getTypeString().c_str(), "directory") == 0) {
        
        cerr << "copying directories not supported" << endl;
        
        return -1;  //return -1 on failure
    }

    ifstream inFileStream(fileName);

    //call dump function to copy contents of original file to destinationFile
    fm.dump(inFileStream, destinationFile);


    return 0;
}
