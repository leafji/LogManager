main.o:main.cpp CSVParse.h CSVParse.cpp NodeManagerment.h NodeManagerment.cpp 
	g++ -g -std=c++11 main.cpp CSVParse.cpp NodeManagerment.cpp -o main.o
clean:
	rm -rf main main.o
