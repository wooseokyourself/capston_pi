#include <string>

#include "data.hpp"
#include "socket.hpp"
#include "vision.hpp"

int
main (void) {
    while (true) {
        struct protocol data = ImageProcessing ();
        SendBuffer (data);
    }
    return 0;
}
