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
#ifdef DEBUG
    struct protocol data = debug_encoding ();
    SendBuffer (data);
	return 0;
#endif

    while (true) {
        struct protocol data = ImageProcessing ();
        SendBuffer (data);
    }
    return 0;
}
