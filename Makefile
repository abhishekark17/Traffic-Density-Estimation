CC=`pkg-config --cflags --libs opencv`

all: first
	g++ bSubtraction.cpp -o main -pthread -std=c++11 $(CC)

first:
	g++ 2019CS50768_2019CS10458_ass1_part1.cpp -o first -pthread -std=c++11 $(CC)

clean:
	rm -f main images/cropped* images/transformed* first 
