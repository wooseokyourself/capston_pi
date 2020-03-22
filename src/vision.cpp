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
ImageProcessing () {
    VideoCapture cap(0);
    ASSERT (cap.isOpened() == true);
    
    Mat imgRGB;
    cap >> imgRGB;
    
    return encoding (imgRGB);
}
