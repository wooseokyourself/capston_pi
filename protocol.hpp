/*
    이 파일은 클라이언트, 서버와 항상 동기화되어있어야한다.
*/

#include <stdint.h>
#include <vector>

#define PROTO_BUFSIZE sizeof(uint64_t)
#define uchar unsigned char

using namespace std;

struct protocol {
    size_t bufSize;
    vector<uchar> prevBuf;
    vector<uchar> currBuf;
    uint32_t diffValue; // abs(prevImg - currImg)
};