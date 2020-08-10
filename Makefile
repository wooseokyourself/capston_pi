all:
	g++ -std=c++11 `pkg-config --cflags --libs opencv4` `pkg-config --cflags --libs libcurl` src/jsoncpp/jsoncpp.cpp -Isrc/jsoncpp -DJSON_IS_AMALGAMATION src/date.cpp src/http_request.cpp src/image.cpp src/main.cpp -o main

clean:
	rm -f main
