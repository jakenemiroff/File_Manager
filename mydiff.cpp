/*  Author: Jake Nemiroff

    Thursday, October 3rd, 2019

    This function is used to perform actions on a file in a filesystem
    in the same way the `diff` keyword would act on a file

*/

#include "FileManager.h"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 3) {
        
        cerr << "Incorrect number of arguments enterred" << endl;
        
        return -1;  //return -1 on failure
    }

    //create filenames with the command line arguments passed in
    string firstFileName = argv[1];
    string secondFileName = argv[2];

    //create filemanager objects with the filenames
    FileManager firstFileManager(firstFileName);
    FileManager secondFileManager(secondFileName);

    //call the compare method to find the difference between the two files
    firstFileManager.compare(secondFileManager);

    return 0; //return 0 on success
}
