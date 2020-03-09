#ifndef VISION
#define VISION

#include <cstdio>
#include <cassert>
#include <unistd.h>

#include <vector>

#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#define ASSERT assert

using namespace cv;

std::vector<unsigned char>
encoding (Mat img);

std::vector<unsigned char>
ImageProcessing ();

#endif
