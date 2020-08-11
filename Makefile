all:
	g++ -std=c++11 `pkg-config --cflags --libs opencv4` `pkg-config --cflags --libs libcurl` `pkg-config --cflags --libs jsoncpp` src/date.cpp src/http_request.cpp src/image.cpp src/main.cpp -o main

clean:
	rm -f main
