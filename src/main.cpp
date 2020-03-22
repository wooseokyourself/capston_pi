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

        // If server's socket isn't opened, then throw the present picture away
        // and capture a picture from the camera module again.
        // So there is no way to check whether the IP or PORT is wrong in this code.
        // If this program terminated abnormally, especially 'Makefile error 141',
        // doubt it.
        if ( ! SendBuffer (IP, PORT, vec) )
            continue;
        else
            sleep (10);
    }
    return 0;
}
