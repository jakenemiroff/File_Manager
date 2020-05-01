/*  Author: Jake Nemiroff

    Thursday, October 3rd, 2019

    This function is used to perform actions on a file in a filesystem
    in the same way the `rm` keyword would act on a file

*/

#include "FileManager.h"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc < 2) {
        
        cerr << "invalid amount of arguments" << endl;
        
        return -1;  //return -1 on failure
    }

    //for each filename passed in as command line arguments
    for (int i = 1; i < argc; i++) {    

        //store argument as filename
        string fileName = argv[i];

        //create filemanager objects with the given filename
        FileManager fm(fileName);

        //remove the file
        fm.remove();
    }

    return 0;   //return 0 on success
}
