all: hello

hello:  gcdriver.o gc.o su.o 
	g++  *.o  -o hello

gcdriver.o: lrdriver.cpp
	g++ -c lrdriver.cpp

gc.o: LaplacianReg.cpp
	g++ -c   LaplacianReg.cpp -o gc.o

su.o: StringUtilities.cpp
	g++ -c StringUtilities.cpp -o su.o


clean:
	rm -rf *o hello
