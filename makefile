all: ls stat mv diff rm cp cat

ls: FileManager.cpp myls.cpp FileManager.h 
	g++ -o ls.out FileManager.cpp myls.cpp

stat: FileManager.cpp mystat.cpp FileManager.h
	g++ -o stat.out FileManager.cpp mystat.cpp

mv: FileManager.cpp mymv.cpp FileManager.h
	g++ -o mv.out FileManager.cpp mymv.cpp

diff: FileManager.cpp mydiff.cpp FileManager.h
	g++ -o diff.out FileManager.cpp mydiff.cpp

rm: FileManager.cpp myrm.cpp FileManager.h
	g++ -o rm.out FileManager.cpp myrm.cpp

cp: FileManager.cpp mycp.cpp FileManager.h
	g++ -o cp.out FileManager.cpp mycp.cpp

cat: FileManager.cpp mycat.cpp FileManager.h
	g++ -o cat.out FileManager.cpp mycat.cpp

clean: 
	rm *.out
