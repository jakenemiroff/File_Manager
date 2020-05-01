/*  Author: Jake Nemiroff

    Thursday, October 3rd, 2019

    This function is used to perform actions on a file in a filesystem
    in the same way the `mv` keyword would act on a file or directory

*/

#include "FileManager.h"

using namespace std;

int main(int argc, char** argv) {

    if (argc != 3) {
        
        cerr << "invalid number of arguments" << endl;
        
        return -1;  //return -1 on failure
    }

    string oldName = argv[1];
    string newName = argv[2];

    FileManager fm(oldName);

    ifstream inFileStream(oldName);

    //move file to new location by means of calling dump (to create a copy of the file) and then removing the original
    fm.dump(inFileStream, newName);

    fm.remove();

    return 0;
}
