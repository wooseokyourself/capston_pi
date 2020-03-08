#include "vision.hpp"

struct protocol
encoding (Mat img) {
    vector<uchar> buf; // 인코딩된 이미지의 버퍼를 저장
    vector<int> params;
    params.push_back (IMWRITE_JPEG_QUALITY);
	params.push_back (95);
    imencode (".jpeg", img, buf, params);

    struct protocol data;
    data.bufSize = buf.size();
    data.buf.assign (buf.begin(), buf.end());

    return data;
}

struct protocol
ImageProcessing () {
    VideoCapture cap(0);
    ASSERT (cap.isOpened() == true);

    Mat img;

    /* 사진 촬영 */
    cap >> img;

    return encoding (img);
}


#ifdef DEBUG_NOCAM
struct protocol
debug_encoding () {
    Mat sample_prev = imread("../debug/encoding/sample_prev.jpeg", IMREAD_COLOR);
    Mat sample_curr = imread("../debug/encoding/sample_curr.jpeg", IMREAD_COLOR);
    uint32_t diffVal = 100;
    return encoding (sample_prev, sample_curr, diffVal);
}
#endif
