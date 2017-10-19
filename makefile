all: hw3

hw3: mainTerm.o
ifeq (${OS}, Windows_NT)
	g++ -o hw3 mainTerm.o -lgtest
else
	g++ -o hw3 mainTerm.o -lgtest -lpthread
endif
		
mainTerm.o: mainTerm.cpp utStruct.h utVariable.h
	g++ -std=gnu++0x -c mainTerm.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe hw3
else
	rm -f *.o *.exe hw3
endif
	
stat:
	wc *.h *.cpp
