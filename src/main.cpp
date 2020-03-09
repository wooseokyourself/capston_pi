#include <string>

#include "protocol.hpp"
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
        if (waitKey(10000) != -1) {
            break;
        }
    }
    return 0;
}
