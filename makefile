all: hw6

hw6: mainTerm.o
ifeq (${OS}, Windows_NT)
	g++ -o hw6 mainTerm.o -lgtest
else
	g++ -o hw6 mainTerm.o -lgtest -lpthread
endif
		
mainTerm.o: parser.h
	g++ -std=gnu++0x -c mainTerm.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe hw6
else
	rm -f *.o *.exe hw6
endif
	
stat:
	wc *.h *.cpp
