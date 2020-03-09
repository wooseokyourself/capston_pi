#include "vision.hpp"

std::vector<unsigned char>
encoding (Mat img) {
printf ("encoding..\n");
    vector<uchar> buf; // 인코딩된 이미지의 버퍼를 저장
    vector<int> params;
    params.push_back (IMWRITE_JPEG_QUALITY);
	params.push_back (95);
    imencode (".jpeg", img, buf, params);

    std::vector<unsigned char> vec;
    vec.assign (buf.begin(), buf.end());

    return data;
}

std::vector<unsigned char>
ImageProcessing () {
    VideoCapture cap(0);
    ASSERT (cap.isOpened() == true);

    Mat img;

    /* 사진 촬영 */
    cap >> img;

    return encoding (img);
}


#ifdef DEBUG_NOCAM
std::vector<unsigned char>
debug_encoding () {
    Mat sample_prev = imread("../debug/encoding/sample_prev.jpeg", IMREAD_COLOR);
    Mat sample_curr = imread("../debug/encoding/sample_curr.jpeg", IMREAD_COLOR);
    uint32_t diffVal = 100;
    return encoding (sample_prev, sample_curr, diffVal);
}
#endif
