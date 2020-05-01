/*  Author: Jake Nemiroff

    Thursday, October 3rd, 2019

    This class is used to create and manage filemanager objects
    which is used to recreate a few linux commands that affect files

*/

#include "FileManager.h"

using namespace std;

    /*  constructor for the class 
        create objects of type filemanager, initialize data members
        takes a file name as a aparameter
    */
    FileManager::FileManager(string fileName) {

        struct stat buf;

        int result;

        //if result returned from stat is 0, success, initialize data members properly
        result = ::stat(fileName.c_str(), &buf);  

        if (result == 0) {
            name = fileName;
            type.first = buf.st_mode;
            type.second = getTypeString();
            size = buf.st_size;
            owner.first = buf.st_uid;
            owner.second = getOwnerString();
            group.first = buf.st_gid;
            group.second = getGroupString();
            permissions = buf.st_mode;
            accessTime = ctime(&buf.st_atime);
            modificationTime = ctime(&buf.st_mtime);
            statusChangeTime = ctime(&buf.st_ctime);
            blockSize = buf.st_blksize;
            vector<FileManager> children;
            errorNumber = 0;
        }

        //otherwise, error returned from stat, initialize data members indicating the object should be deleted
        else {      
            name = "";
            type.first = 0;
            type.second = "";
            size = -1;
            owner.first = -1;
            owner.second = "";
            group.first = -1;
            group.second = "";
            permissions = -1;
            accessTime = NULL;
            modificationTime = NULL;
            statusChangeTime = NULL;
            blockSize = -1;
            vector<FileManager> children;
            errorNumber = -1;
        }
    }

    /*  destructor for the class
        takes no parameters, will clear memory allocated to filemanager object after use
    */
    FileManager::~FileManager() {

        //destructor can be empty because objects are created on the stack, not the heap
    }

    /*  dump function will read from a file and dump contents to destination
        takes an input stream as well as a destination file as parameters
    */
    int FileManager::dump(ifstream &inStream, string destinationFile) {

        //check if the file type is regular or not
        if (!S_ISREG(type.first)) {  
            
            errorNumber = ENOTSUP;
            
            cerr << "not a regular file" << endl;
            
            return -1;  //return -1 on failure
        }

        char*  buffer = new char[blockSize];    //allocate space for char array of size blocksize
        
        ofstream outStream(destinationFile, ios::out|ios::binary);

        //determine whether or not the input stream is open for reading
        if (!inStream) {
            
            errorNumber = errno;
            
            cerr << "could not read from file" << endl;
            
            return -1;  //return -1 on failure
        }
        
        inStream.read(buffer, blockSize);

        //determine whether or not the output stream is open for writing
        if (!outStream) {
            
            errorNumber = errno;
            
            cerr << "could not write to file" << endl;
            
            return -1;  //return -1 on failure
        }
        
        outStream.write(buffer, inStream.gcount());
        
        outStream.close();
        
        delete[] buffer;    //deallocate space given to buffer

        return 0;   //return 0 on success
    }

    //rename function will call the rename system call and store the return value in result
    int FileManager::rename(string newName) {

        int result;

        result = ::rename(name.c_str(), newName.c_str());

        //if the rename was successful, change the name of the filemanager object
        if (result == 0) {
            
            FileManager::setName(newName);
            
            return 0;   //return 0 on success
        }

        //otherwise set error number
        else {
            errorNumber = errno;
        }

        return -1;  //return -1 on failure
    }

    /*  remove function will call the unlink system call and store the return value in result
        it will take no parameters
    */
    int FileManager::remove() {

        int result;

        result = ::unlink(name.c_str());

        //if unlink successful call function resetAttributes 
        if (result == 0) {
            
            FileManager::resetAttributes();
            
            return 0;   //return 0 on success
        }

        //otherwise set error number
        else {
            errorNumber = errno;
        }
        return -1;  //return -1 on failure
    }

    /*  compare function will compare the contents of two filemanager objects
        it will take a second filemanager object as a parameter
    */
    int FileManager::compare(FileManager secondFile) {

        //create streams to read characters from each file
        ifstream originalFileIn(name);
        ifstream secondFileIn(secondFile.getName());

        //hold the contents read from each file in am array of size `blocksize`
        char * originalBuffer = new char [blockSize];
        char * secondBuffer = new char [secondFile.getBlockSize()];

        //could not read from first file, set error number
        if (!originalFileIn) {
            
            errorNumber = errno;
            
            return -1;  //return -1 on failure
        }
        //could not read from first file, set error number
        if (!secondFileIn) {
            
            secondFile.setErrorNumber(errno);
            
            return -1;  //return -1 on failure
        }

        //determine length of both files
        originalFileIn.seekg(0, ios::end);
        int originalFileLength = originalFileIn.tellg();
        originalFileIn.seekg(0, originalFileIn.beg);

        secondFileIn.seekg(0, ios::end);
        int secondFileLength = secondFileIn.tellg();
        secondFileIn.seekg(0, secondFileIn.beg);


        //if the files are of different length, they cannot be equal
        if (originalFileLength != secondFileLength) {
            
            cout << "Files entered are different" << endl;
            
            return -1;  //return -1 on failure
        }

        else {
            //read until the eof is reached
            while (!originalFileIn.eof() && !secondFileIn.eof()) {
                
                originalFileIn.read(originalBuffer, blockSize);
                secondFileIn.read(secondBuffer, secondFile.getBlockSize());

                if (strcmp(originalBuffer, secondBuffer) != 0) {
                    
                    cout << "Files entered are different" << endl;
                    
                    return -1; //return -1 on failure
                }
            }
        }

        //free up space allocated to the char arrays
        delete[] originalBuffer;
        delete[] secondBuffer;

        //close the files
        originalFileIn.close();
        secondFileIn.close();

        cout << "Files entered are the same" << endl;

        return 0;   //return 0 on success
    }

    /*  expand function to list the files contained in a given directory and add them to the vector `children`
        it will take the name of a directory as parameters
    */
    int FileManager::expand(string directoryName) {

        //if the file in question is not a directory, set error number and return
        if (!S_ISDIR(type.first)) {     
            
            errorNumber = ENOTSUP;
            
            return -1;
        }

        DIR *directory;
        struct dirent *directoryEntry;
        directory = opendir(directoryName.c_str());

        if (directory != NULL) {
            
            while ((directoryEntry = readdir(directory))) {
                
                //ignore hidden files and backups
                if (directoryEntry->d_name[0] != '.' && directoryEntry->d_name[strlen(directoryEntry->d_name) -1] != '~') {
                    
                    //concatenate so as to be able to find file in inside directory
                    FileManager fm(directoryName + "/" + directoryEntry->d_name);   
                    
                    fm.setName(directoryEntry->d_name);
                    
                    children.push_back(fm);     //add to vector
                }
            }
            closedir(directory);      
        }
        
        // could not open directory
        else {
            
            errorNumber = errno;
            
            return -1;
        }
        return 0;
    }

    //helper function to return the name of a filemanager object
    string FileManager::getName() {
        
        return name;
    }
    
    //helper function to return the type of a filemanager object
    mode_t FileManager::getType() {
        
        return type.first;
    }
    
    //helper function to return a string representation of the type of a filemanager object 
    string FileManager::getTypeString() {

        string fileType = "";

        if (S_ISREG(type.first)) {
            return "regular file";
        }

        else if (S_ISDIR(type.first)) {
            return "directory";
        }

        else if (S_ISCHR(type.first)) {
            return "character device";
        }
        
        else if (S_ISBLK(type.first)) {
            return "block device";
        }

        else if (S_ISFIFO(type.first)) {
            return "FIFO (named pipe)";
        }

        else if (S_ISLNK(type.first)) {
            return "symbolic link";
        }

        else if (S_ISSOCK(type.first)) {
            return "socket";
        }

        return fileType;

    }
    
    //helper function to return the size of a filemanager object
    off_t FileManager::getSize() {
        
        return size;
    }
    
    //helper function to return the owner of a filemanager object
    uid_t FileManager::getOwner() {
        
        return owner.first;
    }
    
    //helper function to return a string representation of the owner attribute of a filemanager object
    string FileManager::getOwnerString() {
        
        struct passwd *pw = getpwuid(owner.first);
        
        return pw->pw_name;
    }

    //helper function to return the group of a filemanager object
    gid_t FileManager::getGroup() {
        
        return group.first;
    }
    
    //helper function to return a string representation of the group attribute of a filemanager object
    string FileManager::getGroupString() {
        
        struct group *grp = getgrgid(group.first);
        
        return grp->gr_name;
    }

    //helper function to return the permissions of a filemanager object
    mode_t FileManager::getPermissions() {
        
        return permissions;
    }
    
    //helper function to return the access time of a filemanager object
    char * FileManager::getAccessTime() {
        
        accessTime[strcspn(accessTime, "\n")] = '\0';   //remove "\n" for formatting
        
        return accessTime;
    }
    
    //helper function to return the modification time of a filemanager object
    char * FileManager::getModificationTime() {
        
        modificationTime[strcspn(modificationTime, "\n")] = '\0';   //remove "\n" for formatting
        
        return modificationTime;
    }
    
    //helper function to return the status change time of a filemanager object
    char * FileManager::getStatusChangeTime() {
        
        statusChangeTime[strcspn(statusChangeTime, "\n")] = '\0';   //remove "\n" for formatting
        
        return statusChangeTime;
    }
    
    //helper function to return the blocksize of a filemanager object
    blksize_t FileManager::getBlockSize() {
        
        return blockSize;
    }
    
    //helper function to return the vector storing filemanager objects as children of a directory
    vector<FileManager> FileManager::getChildren() {
        
        return children;
    }
    
    //helper function to return the error number of a filemanager object
    int FileManager::getErrorNumber() {
        
        return errorNumber;
    }

    //helper function to set the name of a filemanager object
    void FileManager::setName(string newName) {
        
        name = newName;
    }

    //helper function to set the type of a filemanager object
    void FileManager::setType(mode_t newType) {
        
        type.first = newType;
    }

    //helper function to set the size of a filemanager object
    void FileManager::setSize(off_t newSize) {
        
        size = newSize;
    }

    //helper function to set the owner of a filemanager object
    void FileManager::setOwner(uid_t newOwner) {
        
        owner.first = newOwner;
    }

    //helper function to set the group of a filemanager object
    void FileManager::setGroup(gid_t newGroup) {
        
        group.first = newGroup;
    }

    //helper function to set the permissions of a filemanager object
    void FileManager::setPermissions(mode_t newPermissions) {
        
        permissions = newPermissions;
    }

    //helper function to set the access time of a filemanager object
    void FileManager::setAccessTime(char* newTime) {
        
        accessTime = newTime;
    }

    
    //helper function to set the modification time of a filemanager object
    void FileManager::setModificationTime(char* newTime) {
        
        modificationTime = newTime;
    }

    
    //helper function to set the status change time of a filemanager object
    void FileManager::setStatusChangeTime(char* newTime) { 
        
        statusChangeTime = newTime;
    }
    

    //helper function to set the block size of a filemanager object
    void FileManager::setBlockSize(blksize_t newBlockSize) {
        
        blockSize = newBlockSize;
    }
    

    //helper function to set the error number
    void FileManager::setErrorNumber(int newErrorNumber) {
        
        errorNumber = newErrorNumber;
    }

    //helper function to return and format permissions of a filemanager object
    string FileManager::formatPermissions() {

        string filePermissions = "";

        filePermissions = (S_ISDIR(type.first) ? "d": "-");
        
        filePermissions += ((type.first & S_IRUSR) ? "r": "-");
        
        filePermissions += ((type.first & S_IWUSR) ? "w": "-");
        
        filePermissions += ((type.first & S_IXUSR) ? "x": "-");
        
        filePermissions += ((type.first & S_IRGRP) ? "r": "-");
        
        filePermissions += ((type.first & S_IWGRP) ? "w": "-");
        
        filePermissions += ((type.first & S_IXGRP) ? "x": "-");
        
        filePermissions += ((type.first & S_IROTH) ? "r": "-");
        
        filePermissions += ((type.first & S_IWOTH) ? "w": "-");
        
        filePermissions += ((type.first & S_IXOTH) ? "x": "-");

        return filePermissions;
    }

    //helper function to reset all data members
    void FileManager::resetAttributes() {   
        
        this->setName("");
        this->setSize(0);
        this->setType(0);
        this->setOwner(0);
        this->setGroup(0);
        this->setPermissions(0);
        this->setAccessTime(NULL);
        this->setModificationTime(NULL);
        this->setStatusChangeTime(NULL);
        this->setBlockSize(0);
        children.clear();
        this->setErrorNumber(0);
    }
