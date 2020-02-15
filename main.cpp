#include <string>

#include "data.hpp"
#include "socket.hpp"
#include "vision.hpp"

int
main (void) {
    while (true) {
        struct protocol data = ImageProcessing ();
        SendImage (data);
    }
    return 0;
}
