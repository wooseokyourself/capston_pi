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
        struct protocol data = ImageProcessing ();
        SendBuffer (data);
        sleep (10);
    }
    return 0;
}
