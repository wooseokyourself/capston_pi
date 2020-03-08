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
	g++ src/main.cpp src/vision.cpp src/socket.cpp `pkg-config --cflags --libs opencv4` -o $(TARGET)

$(TARGET_DEBUG):
	g++ -DDEBUG src/main.cpp src/vision.cpp src/socket.cpp `pkg-config --cflags --libs opencv4` -o $(TARGET_DEBUG)

$(TARGET_DEBUG_NOCAM):
	g++ -DDEBUG -DDEBUG_NOCAM src/main.cpp src/vision.cpp src/socket.cpp `pkg-config --cflags --libs opencv4` -o $(TARGET_DEBUG_NOCAM)