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


/*  파이카메라로 이벤트를 감지하고, 그 이벤트를 촬영하여 .jpeg 파일로 저장한뒤 저장된 파일명을 리턴 */
string ImageProcessing () {
    string fileName;
    
    //  작성
    
    return fileName;
}
