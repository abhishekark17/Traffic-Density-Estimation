all:
	g++ initial.cpp -o initial -pthread -std=c++11 `pkg-config --cflags --libs opencv`
	g++ workingMain.cpp -o main -pthread -std=c++11 `pkg-config --cflags --libs opencv`

clean:
	rm -f main initial images/cropped* images/transformed*
