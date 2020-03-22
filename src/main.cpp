#include "socket.hpp"
#include "vision.hpp"

int
main (int argc, char* argv[]) {
    if (argc != 3) {
        printf ("<IP address> <PORT>\n");
        return 0;
    }
    char* IP = argv[1];
    unsigned short PORT = (unsigned short) strtoul(argv[2], NULL, 0);
    while (true) {
        std::vector<unsigned char> vec = ImageProcessing ();
        // If server's socket isn't opened, then throw present picture away.
        if ( ! SendBuffer (IP, PORT, vec) )
            continue;
        else
            sleep (10);
    }
    return 0;
}
