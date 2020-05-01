/*  Author: Jake Nemiroff

    Thursday, October 3rd, 2019

    This function is used to perform actions on a file or directory in a filesystem
    in the same way the `ls`, as well as adding the `-l` extension, keyword would act on files and directories

*/

#include "FileManager.h"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc == 1) {
        
        char cwd[255];  //give 255 characters for the directory path
        
        string directoryName = getcwd(cwd, sizeof(cwd));
        
        FileManager fm(directoryName);
        
        fm.expand(directoryName);

        //print out each file name in the current directory
        for (int i = 0; i < fm.getChildren().size(); i++) {
            
            cout << "file name: " << fm.getChildren().at(i).getName() << endl;
        }
    }

    else if (argc == 2 && strcmp(argv[1], "-l") == 0) {

        char cwd[255];

        string directoryName = getcwd(cwd, sizeof(cwd));

        FileManager fm(directoryName);

        fm.expand(directoryName);

        //if the user enters ls -l, print out stats associated with each file in the directory
        for (int i = 0; i < fm.getChildren().size(); i++) {
            
            cout << "file permissions: " << fm.getChildren().at(i).formatPermissions() << " ";
            cout << "file owner: " << fm.getChildren().at(i).getOwnerString() << " ";
            cout << "file group: " << fm.getChildren().at(i).getGroupString() << " ";
            cout << "file size: " << fm.getChildren().at(i).getSize() << " ";
            cout << "file access time: " << fm.getChildren().at(i).getAccessTime() << " ";
            cout << "file name: " << fm.getChildren().at(i).getName() << endl;        
        }
    }

    else if (argc == 2) {

        string fileName = argv[1];

        FileManager fm(fileName);

        //determine if the enterred file name is in fact a file or directory
        if (strcmp(fm.getTypeString().c_str(), "directory") != 0) {
            
            //if the file exists, print out it's name
            if (strcmp(fm.getName().c_str(), "") != 0) {
                
                cout << "file name: " << fm.getName() << endl;
            }
        }

        //otherwise, it is a directory
        else {
            
            fm.expand(fileName);

            for (int i = 0; i < fm.getChildren().size(); i++) {
                
                cout << "file name: " << fm.getChildren().at(i).getName() << endl;
            }
        }
    }

    //if the `-l` attribute is associated with a file or directory..
    else if (argc == 3 && strcmp(argv[1], "-l") == 0) {
        
        string fileName = argv[2];

        FileManager fm(fileName);

        //if the inputted filename is not a directory, print out stats associated with the given file
        if (strcmp(fm.getTypeString().c_str(), "directory") != 0) {
            
            if (strcmp(fm.getName().c_str(), "") != 0) {
                
                cout << "file permissions: " << fm.formatPermissions() << " ";
                cout << "file owner: " << fm.getOwnerString() << " ";
                cout << "file group: " << fm.getGroupString() << " ";
                cout << "file size: " << fm.getSize() << " ";
                cout << "file access time: " << fm.getAccessTime() << " ";
                cout << "file name: " << fm.getName() << endl;
            }
        }

        //otherwise the file is a directory, print out the stats associated with all files in that directory
        else {
            
            fm.expand(fileName);

            for (int i = 0; i < fm.getChildren().size(); i++) {
                
                if (strcmp(fm.getChildren().at(i).getName().c_str(), "") != 0) {
                    
                    cout << "file permissions: " << fm.getChildren().at(i).formatPermissions() << " ";
                    cout << "file owner: " << fm.getChildren().at(i).getOwnerString() << " ";
                    cout << "file group: " << fm.getChildren().at(i).getGroupString() << " ";
                    cout << "file size: " << fm.getChildren().at(i).getSize() << " ";
                    cout << "file access time: " << fm.getChildren().at(i).getAccessTime() << " ";
                    cout << "file name: " << fm.getChildren().at(i).getName() << endl;
                }
            }
        }
    }

    else {
        cerr << "invalid number of arguments entered" << endl;
        
        return -1;  //return -1 on failure
    }

    return 0;   //return 0 on success
    
}
