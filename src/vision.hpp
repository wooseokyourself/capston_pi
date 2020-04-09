#ifndef VISION
#define VISION

#include "common.hpp"

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#define ASSERT assert

using namespace cv;

std::vector<unsigned char>
encoding (Mat img);

std::vector<unsigned char>
ImageProcessing (const int& width, const int& height);

#endif
