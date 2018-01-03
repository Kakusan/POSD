all: hw8

hw8: mainTerm.o
ifeq (${OS}, Windows_NT)
	g++ -o hw8 mainTerm.o -lgtest
else
	g++ -o hw8 mainTerm.o -lgtest -lpthread
endif
		
mainTerm.o: utExpression.h
	g++ -std=gnu++0x -c mainTerm.cpp 

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe hw8
else
	rm -f *.o *.exe hw8
endif
	
stat:
	wc *.h *.cpp
