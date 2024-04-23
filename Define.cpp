#include "Define.h"

int GAME_WIDE = 1920;
int GAME_HEIGHT = 1080;


// �𑜓x�̔{��
void getGameEx(double& exX, double& exY) {
	exX = (double)GAME_WIDE / GAME_WIDE_DEFAULT;
	exY = (double)GAME_HEIGHT / GAME_HEIGHT_DEFAULT;
}

// �𑜓x�ύX
void ChangeGameResolution() {
	SetGraphMode(GAME_WIDE, GAME_HEIGHT, GAME_COLOR_BIT_NUM);
	InitGraph();
	InitSoundMem();
	InitFontToHandle();
	ChangeWindowMode(WINDOW), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	SetMouseDispFlag(MOUSE_DISP); //�}�E�X�\��
}