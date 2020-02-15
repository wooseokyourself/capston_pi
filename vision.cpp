#include "vision.hpp"

using namespace std;
using namespace cv;

static int PHOTO_CYCLE = 20000; // 2 secs
static int THOLD = 50;
static int COUNT = 5;           // COUNT * PHOTO_CYCLE 동안 이벤트가 감지되지 않으면 이미지 전송

/*
    파이카메라로 이벤트를 감지하고, 그 이벤트를 촬영하여
    .jpeg 파일로 저장한뒤 저장된 파일명을 리턴
*/
string
ImageProcessing () {
    /* 이 디버깅용 이미지 정렬저장코드는 서버의 RecvImage() 에서 사용하기.
    static int imgCount;
    
    string fileName = to_string(imgCount);
    int nameLen = fileName.size();
    if (nameLen == 1)
        fileName = "000" + fileName + ".jpeg";
    else if (nameLen == 2)
        fileName = "00" + fileName + ".jpeg";
    else if (nameLen == 3)
        fileName = "0" + fileName + ".jpeg";
    else if (nameLen == 4)
        fileName = fileName + ".jpeg";
    else {
        imgCount = 0;
        fileName = "0000.jpeg";
    }
     */
    
    VideoCapture cap(0);
    if (!cap.isOpened())
        cout << "카메라를 열 수 없습니다." << endl;
    
    clock_t timeStart, timeEnd, elapsedTime;
    Mat prevRGB, prevGRAY;
    Mat currRGB, currGRAY;
    
    /*  사진 촬영 및 그레이스케일 변환 */
    cap >> currRGB;
    cvtColor(currRGB, currGRAY, COLOR_RGB2GRAY);
    
    int rows = currRGB.rows, cols = currRGB.cols;
    unsigned int imgDiffVal;
    
    for (int i=0; i<COUNT; i++) {
        imgDiffVal = 0;
        
        /*  clock(): 프로그램 시작으로부터 현재까지 경과한 시간 리턴 */
        timeStart = clock();
        
        prevRGB = currRGB.clone();
        prevGRAY = currGRAY.clone();
        
        /*  사진 촬영 및 그레이스케일 변환 */
        cap >> currRGB;
        cvtColor(currRGB, currGRAY, COLOR_RGB2GRAY);
        
        /*  차이값 비교 */
        for (int row = 0; row < rows; row++) {
            const uchar* currPtr = currGRAY.ptr<uchar>(row);
            const uchar* prevPtr = prevGRAY.ptr<uchar>(row);
            for (int col = 0; col < cols; col++) {
                unsigned int diffPixel = abs(prevPtr[col] - currPtr[col]);
                imgDiffVal += (diffPixel * diffPixel);
                // cout << diff << " --> " << diff * diff << ", " << thold_diff << endl;
            }
        }
        imgDiffVal = imgDiffVal / (rows * cols);
        cout << "이전 사진과의 차이값: " << imgDiffVal << endl;
        
        /*  이미지에 변화가 있다면 currRGB를 .jpeg 로 저장 */
        if (THOLD < imgDiffVal) {
            imwrite ("images/image.jpeg", currRGB);
            break;
        }

        timeEnd = clock();
        elapsedTime = (timeEnd - timeStart) / 10; // 1/1000 sec
        
        if (elapsedTime < PHOTO_CYCLE) {
            usleep(PHOTO_CYCLE*100 - elapsedTime); // usleep(microseconds)
        }
        
        /*  COUNT * PHOTO_CYCLE 동안 이미지에 변화가 없다면 currRGB를 .jpeg 로 저장 */
        if ( i+1 == COUNT ) {
            imwrite ("images/img.jpeg", currRGB);
            break;
        }
    }
    
    return "images/img.jpeg";
}
