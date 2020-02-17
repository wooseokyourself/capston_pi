#ifndef VISION
#define VISION

#include <cstdio>
#include <ctime>
#include <cstring>
#include <cassert>

#include <iostream>
#include <vector>
#include <unistd.h>
#include <vector>

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include "protocol.hpp"

#define ASSERT assert

using namespace std;
using namespace cv;

struct protocol
encoding (Mat prevImg, Mat currImg, uint32_t diffVal);

struct protocol
ImageProcessing ();

#ifdef DEBUG_ENCODING
struct protocol
debug_encoding ();
#endif

#endif
