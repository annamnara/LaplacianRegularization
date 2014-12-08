rm -rf *.o
g++ -c *.cpp
g++ *.o -o hello
./hello params.conf
