/*  Author: Jake Nemiroff

    Thursday, October 3rd, 2019

    This function is used to perform actions on a file in a filesystem
    in the same way the `stat` keyword would act on a file

*/

#include "FileManager.h"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 2) {
        
        cerr << "invalid number of arguments" << endl;
        
        return -1;  //return -1 on failure
    }

    //create a filename with the command line argument provided
    string fileName = argv[1];

    //create a filemanager object with the given filename
    FileManager fm(fileName);

    //print out all information about the filemanager object
    cout << "file name: " << fm.getName() << endl;
    cout << "file type: " << fm.getTypeString() << endl;
    cout << "file size: " << fm.getSize() << endl;
    cout << "file owner: " << fm.getOwnerString() << endl;
    cout << "file group: " << fm.getGroupString() << endl;
    cout << "file permissions: " << fm.formatPermissions() << endl;
    cout << "file access time: " << fm.getAccessTime() << endl;
    cout << "file modification time: " << fm.getModificationTime() << endl;
    cout << "file status change time: " << fm.getStatusChangeTime() << endl;
    cout << "file block size: " << fm.getBlockSize() << endl;

    return 0;   //return 0 on success
}
