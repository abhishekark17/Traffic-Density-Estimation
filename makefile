CC=`pkg-config --cflags --libs opencv`

DEPS = IO.hpp OpticalFlow.hpp BGSubtraction.hpp MethodOne.hpp MethodTwo.hpp SubTask2.hpp mymain.hpp

#all: IO.o BGSubtraction.o OpticalFlow.o 
#	g++ mymain.cpp -o main -pthread -std=c++11 $(CC)
all: 
	g++ IO.cpp BGSubtraction.cpp OpticalFlow.cpp SubTask2.cpp MethodTwo.cpp mymain.cpp -o main -pthread $(CC)
#	g++ -c IO.cpp BGSubtraction.cpp OpticalFlow.cpp MethodTwo.cpp -pthread $(CC)

clean:
	rm -f main images/cropped* images/transformed* first *.o