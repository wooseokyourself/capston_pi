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
    // There is no way to check whether the IP or PORT is wrong in this code.
    // If this program terminated abnormally, especially 'Makefile error 141',
    // doubt it.
    int camId;
    printf ("Cam ID: ");
    scanf ("%d", &camId);
    std::vector<unsigned char> vec;
    SendBuffer (IP, PORT, vec, camId);
    return 0;
}
