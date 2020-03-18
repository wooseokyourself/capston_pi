#include "socket.hpp"
#include "vision.hpp"

int
main (int argc, char* argv[]) {
    if (argc != 3) {
        printf ("./client.out <IP address> <PORT>\n");
        return 0;
    }
    IP = argv[1];
    PORT = (unsigned short) strtoul(argv[2], NULL, 0);
    while (true) {
        std::vector<unsigned char> vec = ImageProcessing ();
        SendBuffer (vec);
        sleep (10);
    }
    return 0;
}
