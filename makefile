all: hw2

hw2: mainTerm.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 mainTerm.o -lgtest
else
	g++ -o hw2 mainTerm.o -lgtest -lpthread
endif
		
mainTerm.o: mainTerm.cpp utTerm.h term.h
	g++ -std=gnu++0x -c mainTerm.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe hw2
else
	rm -f *.o *.exe hw2
endif
	
stat:
	wc *.h *.cpp
