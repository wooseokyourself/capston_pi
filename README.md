# Introduction
This directory contains client-side of OpenCV DNN YOLOv3 Project developed by 21500740@handong.edu, and is **freely available under the [Beerware license](https://github.com/wooseokyourself/capstone_pi/blob/master/LICENSE).**

# Description
This https://github.com/wooseokyourself/capstone_pi repo contains code for capturing a picture through a camera and sending it through C's socket API. The code works on Linux.   
You can also see [Server code here](https://github.com/wooseokyourself/capstone_xu4).

# Test Environment and Requirements
#### *This program is designed to run Raspberry Pi (armv7l).*
#### *All requirements below have not been tested in other versions.*
* Linux raspberrypi 4.19.97-v7+
* gcc/g++ 8.3.0
* Makefile
* OpenCV 4.2.0 with contrib (Actually contrib is unnecessary.)

#### *OpenCV Build Options in Test Environment*

~~~
General configuration for OpenCV 4.2.0 =====================================
  Version control:               unknown

  Extra modules:
    Location (extra):            /home/pi/opencv-package/opencv_contrib/modules
    Version control (extra):     unknown

  Platform:
    Timestamp:                   2020-02-16T08:29:01Z
    Host:                        Linux 4.19.97-v7+ armv7l
    CMake:                       3.13.4
    CMake generator:             Unix Makefiles
    CMake build tool:            /usr/bin/make
    Configuration:               RELEASE

  CPU/HW features:
    Baseline:                    VFPV3 NEON
      requested:                 DETECT
      required:                  VFPV3 NEON

  C/C++:
    Built as dynamic libs?:      YES
    C++ Compiler:                /usr/bin/c++  (ver 8.3.0)
    C++ flags (Release):         -fsigned-char -W -Wall -Werror=return-type -Werror=non-virtual-dtor -Werror=address -Werror=sequence-point -Wformat -Werror=format-security -Wmissing-declarations -Wundef -Winit-self -Wpointer-arith -Wshadow -Wsign-promo -Wuninitialized -Winit-self -Wsuggest-override -Wno-delete-non-virtual-dtor -Wno-comment -Wimplicit-fallthrough=3 -Wno-strict-overflow -fdiagnostics-show-option -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections  -mfpu=neon -fvisibility=hidden -fvisibility-inlines-hidden -fopenmp -O3 -DNDEBUG  -DNDEBUG
    C++ flags (Debug):           -fsigned-char -W -Wall -Werror=return-type -Werror=non-virtual-dtor -Werror=address -Werror=sequence-point -Wformat -Werror=format-security -Wmissing-declarations -Wundef -Winit-self -Wpointer-arith -Wshadow -Wsign-promo -Wuninitialized -Winit-self -Wsuggest-override -Wno-delete-non-virtual-dtor -Wno-comment -Wimplicit-fallthrough=3 -Wno-strict-overflow -fdiagnostics-show-option -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections  -mfpu=neon -fvisibility=hidden -fvisibility-inlines-hidden -fopenmp -g  -O0 -DDEBUG -D_DEBUG
    C Compiler:                  /usr/bin/cc
    C flags (Release):           -fsigned-char -W -Wall -Werror=return-type -Werror=non-virtual-dtor -Werror=address -Werror=sequence-point -Wformat -Werror=format-security -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Winit-self -Wpointer-arith -Wshadow -Wuninitialized -Winit-self -Wno-comment -Wimplicit-fallthrough=3 -Wno-strict-overflow -fdiagnostics-show-option -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections  -mfpu=neon -fvisibility=hidden -fopenmp -O3 -DNDEBUG  -DNDEBUG
    C flags (Debug):             -fsigned-char -W -Wall -Werror=return-type -Werror=non-virtual-dtor -Werror=address -Werror=sequence-point -Wformat -Werror=format-security -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Winit-self -Wpointer-arith -Wshadow -Wuninitialized -Winit-self -Wno-comment -Wimplicit-fallthrough=3 -Wno-strict-overflow -fdiagnostics-show-option -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections  -mfpu=neon -fvisibility=hidden -fopenmp -g  -O0 -DDEBUG -D_DEBUG
    Linker flags (Release):      -Wl,--gc-sections
    Linker flags (Debug):        -Wl,--gc-sections
    ccache:                      NO
    Precompiled headers:         NO
    Extra dependencies:          atomic dl m pthread rt
    3rdparty dependencies:

  OpenCV modules:
    To be built:                 aruco bgsegm bioinspired calib3d ccalib core datasets dnn dnn_objdetect dnn_superres dpm face features2d flann freetype fuzzy gapi hfs highgui img_hash imgcodecs imgproc line_descriptor ml objdetect optflow phase_unwrapping photo plot python2 python3 quality reg rgbd saliency shape stereo stitching structured_light superres surface_matching text tracking ts video videoio videostab xfeatures2d ximgproc xobjdetect xphoto
    Disabled:                    world
    Disabled by dependency:      -
    Unavailable:                 cnn_3dobj cudaarithm cudabgsegm cudacodec cudafeatures2d cudafilters cudaimgproc cudalegacy cudaobjdetect cudaoptflow cudastereo cudawarping cudev cvv hdf java js matlab ovis sfm viz
    Applications:                perf_tests apps
    Documentation:               NO
    Non-free algorithms:         YES

  GUI:
    GTK+:                        YES (ver 3.24.5)
      GThread :                  YES (ver 2.58.3)
      GtkGlExt:                  NO

  Media I/O:
    ZLib:                        /usr/lib/arm-linux-gnueabihf/libz.so (ver 1.2.11)
    JPEG:                        /usr/lib/arm-linux-gnueabihf/libjpeg.so (ver 62)
    WEBP:                        build (ver encoder: 0x020e)
    PNG:                         /usr/lib/arm-linux-gnueabihf/libpng.so (ver 1.6.36)
    TIFF:                        build (ver 42 - 4.0.10)
    JPEG 2000:                   /usr/lib/arm-linux-gnueabihf/libjasper.so (ver 1.900.1)
    OpenEXR:                     build (ver 2.3.0)
    HDR:                         YES
    SUNRASTER:                   YES
    PXM:                         YES
    PFM:                         YES

  Video I/O:
    DC1394:                      YES (2.2.5)
    FFMPEG:                      YES
      avcodec:                   YES (58.35.100)
      avformat:                  YES (58.20.100)
      avutil:                    YES (56.22.100)
      swscale:                   YES (5.3.100)
      avresample:                NO
    GStreamer:                   NO
    v4l/v4l2:                    YES (linux/videodev2.h)

  Parallel framework:            TBB (ver 2020.0 interface 11100)

  Trace:                         YES (with Intel ITT)

  Other third-party libraries:
    Lapack:                      NO
    Custom HAL:                  YES (carotene (ver 0.0.1))
    Protobuf:                    build (3.5.1)

  OpenCL:                        YES (no extra features)
    Include path:                /home/pi/opencv-package/opencv/3rdparty/include/opencl/1.2
    Link libraries:              Dynamic load

  Python 2:
    Interpreter:                 /usr/bin/python2.7 (ver 2.7.16)
    Libraries:                   /usr/lib/arm-linux-gnueabihf/libpython2.7.so (ver 2.7.16)
    numpy:                       /usr/lib/python2.7/dist-packages/numpy/core/include (ver 1.16.2)
    install path:                lib/python2.7/dist-packages/cv2/python-2.7

  Python 3:
    Interpreter:                 /usr/bin/python3 (ver 3.7.3)
    Libraries:                   /usr/lib/arm-linux-gnueabihf/libpython3.7m.so (ver 3.7.3)
    numpy:                       /usr/lib/python3/dist-packages/numpy/core/include (ver 1.16.2)
    install path:                lib/python3.7/dist-packages/cv2/python-3.7

  Python (for build):            /usr/bin/python2.7

  Java:
    ant:                         NO
    JNI:                         NO
    Java wrappers:               NO
    Java tests:                  NO

  Install to:                    /usr/local
-----------------------------------------------------------------
~~~
   
   
   
# Application Protocol
    std::vector<unsigned char>
> Encoded form of cv::Mat. There is a process of encoding cv::Mat in this program.
   
# Install

### Compile
    make all
   
# Run

### Run
    make run
> 'make run' will ask you the value of $(IP) and $(PORT). 
   
# Others

### Remove *.out
    make clean


   
# Example Result of Web (index.php)

## from Raspi camera (Release ver.)
![result 1](https://user-images.githubusercontent.com/49421142/77255814-91d4b600-6cad-11ea-9ee9-6d7c47b7027b.JPG)
![result 3](https://user-images.githubusercontent.com/49421142/77255816-95683d00-6cad-11ea-8f11-21a13eff36ba.JPG)
![result 2](https://user-images.githubusercontent.com/49421142/77255815-94371000-6cad-11ea-9fb3-8651462a395c.JPG)

## from test image (Debugging ver.)
![result 4](https://user-images.githubusercontent.com/49421142/77255817-96996a00-6cad-11ea-9a56-aacc81d4889f.JPG)
![result 5](https://user-images.githubusercontent.com/49421142/77255821-98632d80-6cad-11ea-85e8-13ec533ee69e.JPG)
![result 6](https://user-images.githubusercontent.com/49421142/77255822-9ac58780-6cad-11ea-9b11-a4bf53ba78d5.JPG)
![result 7](https://user-images.githubusercontent.com/49421142/77255824-9bf6b480-6cad-11ea-9a36-721638835bf9.JPG)
