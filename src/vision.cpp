#include "vision.hpp"

std::vector<unsigned char>
encoding (Mat img) {
    /*  
        bool cv::imencode	(	const String & 	ext,
                                InputArray 	img,
                                std::vector< uchar > & 	buf,
                                const std::vector< int > & 	params = std::vector< int >() 
                            )
        Parameters
            ext	    File extension that defines the output format.
            img	    Image to be written.
            buf	    Output buffer resized to fit the compressed image.
            params	Format-specific parameters. See cv::imwrite and cv::ImwriteFlags.
    */

    std::vector<uchar> buf;
	std::vector<int> params;
	params.push_back (IMWRITE_JPEG_QUALITY);
	params.push_back (95);
    imencode (".jpeg", img, buf, params);

    return buf;
}

std::vector<unsigned char>
ImageProcessing (const int& width, const int& height) {
    VideoCapture cap(0);
    ASSERT (cap.isOpened() == true);
    cap.set(CAP_PROP_FRAME_WIDTH, width);
    cap.set(CAP_PROP_FRAME_HEIGHT, height);
    
    Mat imgRGB;

    time_t timeObj = time(NULL);
    while (true) {
        struct  tm* tm = localtime(&timeObj);
        if (tm->tm_sec % 4 == 0) { // 모든 클라이언트가 동일한 시간에 촬영하기 위함
            cap >> imgRGB;
            break;
        }
    }
    
    return encoding (imgRGB);
}
