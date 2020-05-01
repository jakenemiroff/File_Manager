#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <utility>
#include <pwd.h>
#include <grp.h>
#include <time.h>


class FileManager {
    

    public:
        FileManager(std::string name);
        ~FileManager();
        int dump(std::ifstream &inStream, std::string destination);
        int rename(std::string name);
        int remove();
        int compare(FileManager secondFile);
        int expand(std::string directoryName);

        std::string getName();
        mode_t getType();
        std::string getTypeString();
        off_t getSize();
        uid_t getOwner();
        std::string getOwnerString();
        gid_t getGroup();
        std::string getGroupString();
        mode_t getPermissions();
        char* getAccessTime();
        char* getModificationTime();
        char* getStatusChangeTime();
        blksize_t getBlockSize();
        std::vector<FileManager> getChildren();
        int getErrorNumber();

        void setName(std::string newName);
        void setType(mode_t newType);
        void setSize(off_t newSize);
        void setOwner(uid_t newOwner);
        void setGroup(gid_t newGroup);
        void setPermissions(mode_t newPermissions);
        void setAccessTime(char* newTime);
        void setModificationTime(char* newTime);
        void setStatusChangeTime(char* newTime);
        void setBlockSize(blksize_t newSize);
        void setErrorNumber(int newErrorNumber);

        std::string formatPermissions();
        void resetAttributes();

    private:
        std::string name;
        std::pair <mode_t, std::string> type;
        off_t size;
        std::pair <uid_t, std::string> owner;
        std::pair <gid_t, std::string> group;
        mode_t permissions;
        char* accessTime;
        char* modificationTime;
        char* statusChangeTime;
        blksize_t blockSize;
        std::vector<FileManager> children;
        int errorNumber;
};

#endif
