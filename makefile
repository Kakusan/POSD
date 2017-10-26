all: hw4

hw4: mainTerm.o
ifeq (${OS}, Windows_NT)
	g++ -o hw4 mainTerm.o -lgtest
else
	g++ -o hw4 mainTerm.o -lgtest -lpthread
endif
		
mainTerm.o: utList.h
	g++ -std=gnu++0x -c mainTerm.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe hw4
else
	rm -f *.o *.exe hw4
endif
	
stat:
	wc *.h *.cpp
