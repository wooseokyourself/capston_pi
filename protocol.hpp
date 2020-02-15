/*
    이 파일은 클라이언트, 서버와 항상 동기화되어있어야한다.
*/

#include <stdint.h>

#define PROTO_BUFSIZE sizeof(uint64_t)

using namespace std;

struct protocol {
    size_t bufSize;
    size_t prevBuf;
    size_t currBuf;
    uint32_t diffValue; // abs(prevImg - currImg)
};