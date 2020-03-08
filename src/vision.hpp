#ifndef VISION
#define VISION

#include <cstdio>
#include <ctime>
#include <cassert>
#include <string>

#include <vector>
#include <unistd.h>
#include <vector>

#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include "protocol.hpp"

#define ASSERT assert

using namespace std;
using namespace cv;

#ifdef DIFF_BASE
struct protocol
encoding (Mat prevImg, Mat currImg, uint32_t diffVal);

struct protocol
ImageProcessing ();
#else
struct protocol
encoding (Mat img);

struct protocol
ImageProcessing ();
#endif


#ifdef DEBUG_NOCAM
struct protocol
debug_encoding ();
#endif

#endif
