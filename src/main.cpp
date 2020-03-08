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
#ifdef DEBUG_NOCAM
    struct protocol data = debug_encoding ();
    SendBuffer (data);
	return 0;
#endif

#ifdef DIFF_BASE
    while (true) {
        struct protocol data = ImageProcessing ();
        SendBuffer (data);
    }
    return 0;
#else
    while (true) {
        if (waitKey(10000) == -1) {
            struct protocol data = ImageProcessing ();
        }
        else {
            break;
        }
    }
    return 0;
#endif
}
