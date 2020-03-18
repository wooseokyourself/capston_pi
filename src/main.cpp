#include "socket.hpp"
#include "vision.hpp"

int
main (int argc, char* argv[]) {
    if (argc != 3) {
        printf ("./client.out <IP address> <PORT>\n");
        return 0;
    }
    char* IP = argv[1];
    unsigned short PORT = (unsigned short) strtoul(argv[2], NULL, 0);
    while (true) {
        std::vector<unsigned char> vec = ImageProcessing ();
        SendBuffer (IP, PORT, vec);
        sleep (10);
    }
    return 0;
}
