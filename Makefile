TARGET = client.out

all: $(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)

$(TARGET):
	g++ -DDEBUG -DDEBUG_NOCAM src/main.cpp src/vision.cpp src/socket.cpp `pkg-config --cflags --libs opencv4` -o $(TARGET)
