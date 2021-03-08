all: first
	g++ bSubtraction.cpp -o main -pthread -std=c++11 `pkg-config --cflags --libs opencv`

first:
	g++ 2019CS50768_2019CS10458_ass1_part1.cpp -o first -pthread -std=c++11 `pkg-config --cflags --libs opencv`

clean:
	rm -f main images/cropped* images/transformed* first
