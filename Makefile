# Target
TARGET = .client.out

# compiler, flags, libs
CXX = g++
CXXFLAGS = -std=c++11
OPENCV = `pkg-config --cflags --libs opencv4`

# Sources
RELEASE_SRC = src/socket.cpp src/vision.cpp src/main.cpp

#-----------------------------------------------#

# Compile and Run: release version

all: $(TARGET)
	@echo "Compile is done! Run with 'make run'"

$(TARGET):
	$(CXX) $(CXXFLAGS) $(RELEASE_SRC) $(OPENCV) -o $(TARGET)

run:
	@echo "Enter the server's IP address and PORT number."
	@read -p "<IP address> <PORT>: " IP PORT; \
	./.client.out ${IP} ${PORT}

#-----------------------------------------------#

# Remove target file

clean:
	rm -f *.out
	rm -f .*.out

#-----------------------------------------------#

# for myself

update:
	git add .
	git commit -m "update"
	git push -u mac master

#-----------------------------------------------#