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

#include "protocol.hpp"

#define ASSERT assert

using namespace std;
using namespace cv;

struct protocol
encoding (Mat img);

struct protocol
ImageProcessing ();

#ifdef DEBUG_NOCAM
struct protocol
debug_encoding ();
#endif

#endif
