#include <string>

#include "socket.hpp"
#include "vision.hpp"

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
