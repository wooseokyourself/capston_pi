TARGET = client.out
TARGET_DEBUG = client_debug.out
TARGET_DEBUG_NOCAM = client_debug_nocam.out

update:
	git add .
	git commit -m "update"
	git push -u mac master

clean:
	rm -f *.o
	rm -f *.out

all: $(TARGET)

$(TARGET):
	g++ -std=c++11 -w src/main.cpp src/vision.cpp src/socket.cpp `pkg-config --cflags --libs opencv4` -o $(TARGET)
