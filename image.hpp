#ifndef IMAGE
#define IMAGE

#include <opencv2/opencv.hpp>

#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

static inline bool is_base64(unsigned char c);
string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
string base64_decode(string const& encoded_string);

string takePicture(const int width, const int height);

#endif