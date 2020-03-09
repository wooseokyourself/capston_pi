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

    std::vector<uchar> buf; // 인코딩된 이미지의 버퍼를 저장
	std::vector<int> params;
	params.push_back (IMWRITE_JPEG_QUALITY);
	params.push_back (95);
    imencode (".jpeg", img, buf, params);

    return buf;
}

/*
    파이카메라로 이벤트를 감지하고, 그 이벤트를 촬영하여
    .jpeg 파일로 저장한뒤 저장된 파일명을 리턴
*/

std::vector<unsigned char>
ImageProcessing () {
    VideoCapture cap(0);
    ASSERT (cap.isOpened() == true);
    
    Mat imgRGB;
    
    /*  사진 촬영 및 그레이스케일 변환 */
    cap >> imgRGB;
    
    return encoding (imgRGB);
}
