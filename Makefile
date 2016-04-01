main.o:main.cpp CSVParse.h CSVParse.cpp  
	g++ -g -std=c++11 main.cpp CSVParse.cpp  -o main.o
clean:
	rm -rf main main.o
