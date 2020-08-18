#include "http_request.hpp"
#include "image.hpp"

// g++ -I /usr/local/restclient-cpp/include -l restclient-cpp `pkg-config --cflags --libs jsoncpp` `pkg-config --cflags --libs opencv4` `pkg-config --cflags --libs libffi` -std=c++11 main.cpp -o main

int main(void) {
    string URL;
    cout << "URL(xxx.xxx.xxx.xxx:pppp): ";
    cin >> URL;
    
    pair<int, int> size = get_setting(URL + "/api/admin/setting");
    string b64encoded = takePicture(size.first, size.second);
    
    pair<int, Date> idAndDate = post_roi_image(URL + "/api/admin/roi-image", b64encoded);
    int cameraID = idAndDate.first;
    Date nextCaptureTime = idAndDate.second;

    while (true) {
        if (nextCaptureTime <= Date()) {
            string b64encoded = takePicture(size.first, size.second);
            nextCaptureTime = post_image(URL + "/api/basic/image-info", b64encoded, nextCaptureTime, cameraID, size);
        }
    }

    return 0;
}
