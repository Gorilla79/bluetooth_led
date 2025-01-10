#include <Adafruit_GFX.h>
#include <P3RGB64x32MatrixPanel.h>
#include <string>

// LED Matrix 설정
P3RGB64x32MatrixPanel matrix(25, 26, 27, 21, 22, 0, 15, 32, 33, 12, 5, 23, 4);

// 입력 관련 변수 선언
#define MAX_INPUT_LENGTH 20  // 입력 문자열의 최대 길이
char InputString[MAX_INPUT_LENGTH]; // 입력 데이터를 저장할 배열
int inputIndex = 0; // 현재 입력의 인덱스

// GAME START 이미지 데이터
const uint16_t gameStartImage[28][28] = {
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x4444, 0x0000, 0x4444, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x4444, 0x0000, 0x4444, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x4444, 0x0000, 0x4444, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, // 데이터 생략
};

// YOU LOSE 이미지 데이터
const uint16_t youLoseImage[28][28] = {
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x4444, 0x4444, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x4444, 0x4444, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x4444, 0x4444, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x8410, 0x4444, 0x4444, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x8410, 0x4444, 0x4444, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x8410, 0x4444, 0x4444, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x4444, 0x4444, 0x4444, 0x0000, 0x0000, 0x0000},
    {0x0000, 0xFFFF, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x4444, 0xFFFF, 0x0000, 0x4444, 0x0000, 0x0000},
    {0xFFFF, 0x0000, 0x8410, 0x0000, 0x8410, 0x8410, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x8410, 0x8410, 0x0000, 0x8410, 0x0000, 0xFFFF, 0x4444, 0x0000, 0x0000},
    {0xFFFF, 0x0000, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x4444, 0x0000, 0x4444, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000},
    {0x0000, 0xFFFF, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x4444, 0x0000, 0x4444, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x4444, 0x0000, 0x4444, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000} // 데이터 생략
};

// YOU WINS 이미지 데이터
const uint16_t youWinsImage[28][28] = {
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x4444, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x4444, 0x0000, 0x4444, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0xFFFF, 0x0000, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x4444, 0x0000, 0x4444, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0xFFFF, 0x0000, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x4444, 0x0000, 0x4444, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0xFFFF, 0x0000, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0xFFFF, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x8410, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000} // 데이터 생략
};

// 텍스트 출력 함수
void drawText(const char* text, int startX, int startY, int textSize, uint16_t color) {
    matrix.setTextColor(color); // 텍스트 색상 설정
    matrix.setTextSize(textSize);
    int x = startX;
    int y = startY;

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == ' ') {
            x += 6 * textSize; // 간격 조정
        } else {
            matrix.setCursor(x, y);
            matrix.print(text[i]);
            x += 6 * textSize; // 다음 문자 위치
        }
    }
}

// 이미지를 출력하는 함수
void drawImage(const uint16_t image[28][28]) {
    int panelWidth = 64;  // LED 패널 너비
    int panelHeight = 32; // LED 패널 높이
    int imageWidth = 28;  // 이미지 너비
    int imageHeight = 28; // 이미지 높이

    int offsetX = panelWidth - imageWidth;  // X축 시작 위치
    int offsetY = panelHeight - imageHeight; // Y축 시작 위치

    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < imageWidth; x++) {
            uint16_t color = image[y][x];
            matrix.drawPixel(offsetX + x, offsetY + y, color);
        }
    }
}

// 테두리를 출력하는 함수
void drawBorder(uint16_t borderColor) {
    for (int x = 0; x < 64; x++) {
        matrix.drawPixel(x, 0, borderColor);   // 상단
        matrix.drawPixel(x, 31, borderColor); // 하단
    }

    for (int y = 0; y < 32; y++) {
        matrix.drawPixel(0, y, borderColor);   // 좌측
        matrix.drawPixel(63, y, borderColor); // 우측
    }
}

// "GAME START" 코드 실행
void executeGameStartCode() {
    matrix.fillScreen(0); // 화면 지우기
    drawText("GAME", 5, 7, 1, matrix.colorHSV(255, 255, 255));  // 흰색 텍스트
    drawText("START", 5, 15, 1, matrix.colorHSV(255, 255, 255));
    drawImage(gameStartImage);
    delay(5000);
}

// "YOU LOSE" 코드 실행
void executeYouLoseCode() {
    matrix.fillScreen(0); // 화면 지우기
    drawText("YOU", 5, 7, 1, matrix.colorHSV(0, 255, 255));  // 빨간색 텍스트
    drawText("LOSE!", 5, 15, 1, matrix.colorHSV(0, 255, 255));
    drawImage(youLoseImage);
    drawBorder(0xF800); // 빨간색 테두리
    delay(5000);
}

// "YOU WINS" 코드 실행
void executeYouWinsCode() {
    matrix.fillScreen(0); // 화면 지우기
    drawText("YOU", 5, 7, 1, matrix.colorHSV(120, 255, 255));  // 초록색 텍스트
    drawText("WINS!", 5, 15, 1, matrix.colorHSV(120, 255, 255));
    drawImage(youWinsImage);
    drawBorder(0x07E0); // 초록색 테두리
    delay(5000);
}

void setup() {
    // Serial 통신 초기화
    Serial.begin(115200);

    // LED Matrix 초기화
    matrix.begin();
    matrix.fillScreen(0); // 화면 초기화
}

void loop() {
    // Serial 데이터 수신 확인
    if (Serial.available()) {
        char c = Serial.read();

        if (c == '\n') {
            InputString[inputIndex] = '\0'; // 입력값 종료

            // 입력값에 따라 함수 호출
            if (strcmp(InputString, "1") == 0) {
                executeGameStartCode();
            } else if (strcmp(InputString, "2") == 0) {
                executeYouLoseCode();
            } else if (strcmp(InputString, "3") == 0) {
                executeYouWinsCode();
            } else {
                Serial.println("Invalid Input!");
            }

            inputIndex = 0; // 입력 버퍼 초기화
        } else if (inputIndex < MAX_INPUT_LENGTH - 1) {
            InputString[inputIndex++] = c;
        } else {
            Serial.println("Input too long!");
            inputIndex = 0;
        }
    }

    delay(1);
}
