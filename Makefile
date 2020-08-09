all:
	g++ -I /usr/local/restclient-cpp/include -l restclient-cpp `pkg-config --cflags --libs jsoncpp` `pkg-config --cflags --libs opencv4` `pkg-config --cflags --libs libffi` -std=c++11 main.cpp -o main

clean:
	rm -f main