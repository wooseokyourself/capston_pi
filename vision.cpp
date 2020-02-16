#include "vision.hpp"

static int PHOTO_CYCLE = 20000; // 2 secs
static int THOLD = 50;
static int COUNT = 5;           // COUNT * PHOTO_CYCLE 동안 이벤트가 감지되지 않으면 이미지 전송

/*
    prevRGB, currRGB를 imencode()하여 버퍼에 쓴 뒤
    두 바이트를 각각 data.currBuf, data.prevBuf 에 저장.
*/
struct protocol
encodig (Mat prevImg, Mat currImg, uint32_t diffVal) {
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

    vector<uchar> prevBuf, currBuf; // 인코딩된 이미지의 버퍼를 저장
    imencode (".jpeg", prevImg, prevBuf, IMWRITE_JPEG_QUALITY);
    imencode (".jpeg", currImg, currBuf, IMWRITE_JPEG_QUALITY);

    size_t imgBufSize = prevBuf.size(); // 이미지의 버퍼사이즈
    
    ASSERT (imgBufSize <= PROTO_BUFSIZE);

    struct protocol data;
    /*  
        버퍼를 가리키는 포인터가 아닌 버퍼의 값을 소켓으로 전송하기 위해(깊은 복사),
        imencode를 통해 쓰여진 버퍼의 사이즈를 size_t 자료형으로 저장하고,
        그 버퍼를 각각 data.prevBuf, data.currBuf에 쓴 뒤 (memmove)
        이후 쓰고 남은 data.prevBuf, data.currBuf를 0으로 쓴다. (memset)

        void* memmove (void* sga, const void* pga, size_t num)
        Parameters
            sga     복사된 데이터가 입력될 시작점을 가리키는 포인터
            pga     복사할 데이터의 시작점을 가리키는 포인터
            num     복사할 바이트의 수

        void* memset (void* ptr, int value, size_t num)
        Parameters
            ptr     값을 채울 메모리의 시작주소
            value   채울 값
            num     value로 채울 바이트 수
    */
    data.bufSize = imgBufSize;
    /* // protocol 의 버퍼를 vector<uchar>로 할 경우, 굳이 이하와 같은 것을 하지 않고 그냥 vector<uchar>를 복사하면 된다.
    memmove (&data.prevBuf, &prevBuf, imgBufSize);
    memset ( (&data.prevBuf + imgBufSize), 0, (sizeof(size_t) - imgBufSize) ); // 버퍼의 남은 공간을 0으로 채우기
    memmove (&data.currBuf, &currBuf, imgBufSize);
    memset ( (&data.currBuf + imgBufSize), 0, (sizeof(size_t) - imgBufSize) );
    */
    data.prevBuf.assign (prevBuf.begin(), prevBuf.end());
    data.currBuf.assign (currBuf.begin(), currBuf.end());
    data.diffValue = diffVal;
    return data;

    /*
        이후 struct protocol을 보내기 위해선,
        먼저 sizeof(struct protocol) 을 통해 구조체의 크기를 안 뒤,
        그 크기를 보내고 이후 서버에서 그 크기만큼을 읽어야 한다.
    */
}

/*
    파이카메라로 이벤트를 감지하고, 그 이벤트를 촬영하여
    .jpeg 파일로 저장한뒤 저장된 파일명을 리턴
*/

struct protocol
ImageProcessing () {
    VideoCapture cap(0);
    if (!cap.isOpened())
        cout << "카메라를 열 수 없습니다." << endl;
    
    clock_t timeStart, timeEnd, elapsedTime;
    uint32_t diffVal;
    Mat prevRGB, prevGRAY;
    Mat currRGB, currGRAY;
    
    /*  사진 촬영 및 그레이스케일 변환 */
    cap >> currRGB.currImg;
    cvtColor(currRGB, currGRAY, COLOR_RGB2GRAY);
    
    int rows = currGRAY.rows, cols = currGRAY.cols;
    
    for (int i=0; i<COUNT; i++) {
        diffVal = 0;
        
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
                uint32_t diffPixel = abs(prevPtr[col] - currPtr[col]);
                diffVal += (diffVal * diffVal);
            }
        }
        diffVal = diffVal / (rows * cols);
        cout << "이전 사진과의 차이값: " << diffVal << endl; // debug
        
        /*  이미지에 변화가 있다면 현재 data를 리턴 */
        if (THOLD < diffVal) {
            return encoding (prevRGB, currRGB, diffVal);
        }

        timeEnd = clock();
        elapsedTime = (timeEnd - timeStart) / 10; // 1/1000 sec
        
        if (elapsedTime < PHOTO_CYCLE) {
            usleep(PHOTO_CYCLE*100 - elapsedTime); // usleep(microseconds)
        }
        
        /*  COUNT * PHOTO_CYCLE 동안 이미지에 변화가 없다면 마지막 data를 리턴 */
        if ( i+1 == COUNT ) {
            return encoding (prevRGB, currRGB, diffVal);
        }
    }
}

#ifdef DEBUG_ENCODING
struct protocol
debug_encoding () {
    Mat sample_prev = imread("debug/encoding/sample_prev.jpeg", IMREAD_COLOR);
    Mat sample_curr = imread("debug/encoding/sample_curr.jpeg", IMREAD_COLOR);
    uint32_t diffVal = 100;
    return encoding (sample_prev, sample_curr, diffVal);
}
#endif