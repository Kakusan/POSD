all: hw7

hw7: mainTerm.o
ifeq (${OS}, Windows_NT)
	g++ -o hw7 mainTerm.o -lgtest
else
	g++ -o hw7 mainTerm.o -lgtest -lpthread
endif
		
mainTerm.o: utIterator.h
	g++ -std=gnu++0x -c mainTerm.cpp 

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe hw7
else
	rm -f *.o *.exe hw7
endif
	
stat:
	wc *.h *.cpp
