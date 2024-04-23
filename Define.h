#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#include "DxLib.h"

// �t���X�N���[���Ȃ�FALSE
static int WINDOW = TRUE;
// �}�E�X��\������Ȃ�FALSE
static int MOUSE_DISP = TRUE;

//��ʂ̑傫��
#define GAME_WIDE_MAX 3840
#define GAME_HEIGHT_MAX 2160
#define GAME_WIDE_MIN 640
#define GAME_HEIGHT_MIN 480
#define GAME_WIDE_DEFAULT 1920
#define GAME_HEIGHT_DEFAULT 1080
extern int GAME_WIDE;
extern int GAME_HEIGHT;

// �𑜓x�̔{��
void getGameEx(double& exX, double& exY);

// �𑜓x�ύX
void ChangeGameResolution();

#define GAME_COLOR_BIT_NUM 16

// DrawFormatString�֐��ŕ\������镶���̑傫����20���炢
#define DRAW_FORMAT_STRING_SIZE 20

//�F
const int BLACK = GetColor(0, 0, 0);
const int GRAY = GetColor(100, 100, 100);
const int GRAY2 = GetColor(200, 200, 200);
const int WHITE = GetColor(255, 255, 255);
const int RED = GetColor(255, 0, 0);
const int LIGHT_RED = GetColor(255, 100, 100);
const int BLUE = GetColor(0, 0, 255);
const int LIGHT_BLUE = GetColor(100, 100, 255);

#endif