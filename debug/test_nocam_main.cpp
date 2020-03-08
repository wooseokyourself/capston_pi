#include <string>

#include "../src/protocol.hpp"
#include "../src/socket.hpp"
#include "../src/vision.hpp"

int main (void) {
    struct protocol data = debug_encoding ();
    SendBuffer (data);
	return 0;
}