TARGET = client.out
TARGET_DEBUG = client_debug.out
TARGET_DEBUG_NOCAM = client_debug_nocam.out

clean:
	rm -f *.o
	rm -f *.out

all: $(TARGET)

debug: $(TARGET_DEBUG)

debug_nocam: $(TARGET_DEBUG_NOCAM)

$(TARGET):
	g++ -std=c++11 -w src/main.cpp src/vision.cpp src/socket.cpp `pkg-config --cflags --libs opencv4` -o $(TARGET)

$(TARGET_DEBUG):
	g++ -std=c++11 -DDEBUG -w src/main.cpp src/vision.cpp src/socket.cpp `pkg-config --cflags --libs opencv4` -o $(TARGET_DEBUG)

$(TARGET_DEBUG_NOCAM):
	g++ -std=c++11 -DDEBUG -DDEBUG_NOCAM -w src/main.cpp src/vision.cpp src/socket.cpp `pkg-config --cflags --libs opencv4` -o $(TARGET_DEBUG_NOCAM)