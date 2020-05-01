# FileManager
The purpose of this project was to gain experience experience with C++ and create a FileManager class along with creating utilities for manipulating files on a linux based file system


mymv:

Renames a file or directory with name oldname to use newname instead, where oldname and newname do not have any path information.  (They’re both in the current directory.)

mymv pathname1/oldname pathname2/newname

Renames a file or directory as above, but changes the directory it is located in.



mycp:

mycp oldname newname

Copies a file (not a directory) with name oldname to a new copy newname, where oldname and newname do not have any path information.  (They’re both in the current directory.)

mymv pathname1/oldname pathname2/newname

Copies a file (again not a directory) as above, but to a different directory.  

 

myls

Will display the contents of the current directory.

myls filename

Will display the file’s name if the file exists (the file in this case is not a directory).

myls directoryname

Will list the contents of the directory dirname.

myls will also support ls -l in order to print files in a long listing format.
 

mycat

mycat filename1 filename2 ...

Will dump the contents of all files given as parameters to the terminal.

 

myrm

myrm filename1 filename2 ...

Will remove the files given as parameters.

 

mydiff

mydiff filename1 filename2

Will compare the contents of filename1 and filename2 and report whether they are the same or different.

 

mystat

mystat filename

Will output all of the information on the named file filename to the terminal.
