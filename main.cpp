#include "common.hpp"
#include "http_request.hpp"
#include "image.hpp"

// g++ -I /usr/local/restclient-cpp/include -l restclient-cpp `pkg-config --cflags --libs jsoncpp` `pkg-config --cflags --libs opencv4` `pkg-config --cflags --libs libffi` -std=c++11 main.cpp -o main

string URL_GET_SETTING = "58.237.17.126:10051/api/admin/setting";
string URL_POST_ROI_IMAGE = "58.237.17.126:10051/api/admin/roi-image";
string URL_POST_IMAGE = "58.237.17.126:10051/api/basic/image-info";

int main(void) {
    pair<int, int> size = get_setting(URL_GET_SETTING);
    string b64encoded = takePicture(size.first, size.second);
    
    pair<int, Date> idAndDate = post_roi_image(URL_POST_ROI_IMAGE, b64encoded);
    int cameraID = idAndDate.first;
    Date nextCaptureTime = idAndDate.second;

    while (true) {
        if (nextCaptureTime <= Date()) {
            string b64encoded = takePicture(size.first, size.second);
            nextCaptureTime = post_image(URL_POST_IMAGE, b64encoded, nextCaptureTime, cameraID);
        }
    }

    return 0;
}