#include <string>
#include <unistd.h>

#include "socket.hpp"
#include "vision.hpp"

/*
    DEBUG_MODE
        DEBUG_MODE
*/

int
main (void) {
    while (true) {
        std::vector<unsigned char> vec = ImageProcessing ();
        SendBuffer (vec);
        sleep (10);
    }
    return 0;
}
