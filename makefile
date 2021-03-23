CC=`pkg-config --cflags --libs opencv`

DEPS = IO.h OpticalFlow.h BGSubtraction.h mymain.h

#all: IO.o BGSubtraction.o OpticalFlow.o 
#	g++ mymain.cpp -o main -pthread -std=c++11 $(CC)
all: 
	g++ IO.o BGSubtraction.o OpticalFlow.o mymain.o -o main -pthread $(CC) 

IO.o: IO.cpp 
	g++ -o IO.o IO.cpp -pthread -std=c++11 $(CC)

BGSubtraction.o: BGSubtraction.cpp 
	g++ -o BGSubtraction.o BGSubtraction.cpp -pthread -std=c++11 $(CC)

OpticalFlow.o: OpticalFlow.cpp 
	g++ -o OpticalFlow.o OpticalFlow.cpp -pthread -std=c++11 $(CC)

mymain.o: mymain.cpp
	g++ -o mymain.o mymain.cpp -pthread -std=c++11 $(CC)

clean:
	rm -f main images/cropped* images/transformed* first 