all: hw5

hw5: mainTerm.o
ifeq (${OS}, Windows_NT)
	g++ -o hw5 mainTerm.o -lgtest
else
	g++ -o hw5 mainTerm.o -lgtest -lpthread
endif
		
mainTerm.o: parser.h
	g++ -std=gnu++0x -c mainTerm.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe hw5
else
	rm -f *.o *.exe hw5
endif
	
stat:
	wc *.h *.cpp
