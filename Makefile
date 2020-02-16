CC = g++
CFLAGS = -g -Wall
OBJS = main.o socket.o vision.o
CV_CONFIG = 'pkg-config opencv --cflags --libs'

TARGET = client.out

all: $(TARGET)

debug_encoding: $(TARGET)
debug_encoding: DEBUG_ENCODING = -DDEBUG_ENCODING

clean:
	rm -f *.o
	rm -f $(TARGET)


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: protocol.hpp socket.hpp vision.hpp main.cpp
	$(CC) -c $(DEBUG_ENCODING) -o main.o main.cpp

socket.o: protocol.hpp socket.hpp socket.cpp
	$(CC) -c -o socket.o socket.cpp

vision.o: protocol.hpp vision.hpp vision.cpp
	$(CC) -c $(DEBUG_ENCODING) -o vision.o vision.cpp $(CV_CONFIG)
