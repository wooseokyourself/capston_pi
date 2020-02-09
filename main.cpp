#include <string>

#include "socket.hpp"
#include "vision.hpp"

string ImageProcessing ();

int
main (void) {
    while (true) {
        string fileName = ImageProcessing ();
        SendImage (fileName);
    }
    return 0;
}
