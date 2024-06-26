#include "Control.h"
#include "Define.h"
#include "Game.h"
#include "GameDrawer.h"


///////fpsの調整///////////////
static int mStartTime;
static int mCount;
static int debug = FALSE;
static float mFps;

bool Update() {
	if (mCount == 0) {
		mStartTime = GetNowCount();
	}
	if (mCount == FPS) {
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / (float)FPS);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

void Draw(int x, int y, int color) {
	DrawFormatString(0, 0, BLUE, "デバッグモード：%.1f FPS, 解像度：%d*%d", mFps, GAME_WIDE, GAME_HEIGHT);
}

void Wait() {
	int tookTime = GetNowCount() - mStartTime;
	int waitTime = mCount * 1000 / FPS - tookTime;
	if (waitTime > 0) {
		Sleep(waitTime);
	}
}

//////////メイン関数///////////////////////
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetWindowSizeChangeEnableFlag(TRUE);//windowサイズ変更可能
	SetUseDirectInputFlag(TRUE);
	SetGraphMode(GAME_WIDE, GAME_HEIGHT, GAME_COLOR_BIT_NUM);

	ChangeWindowMode(WINDOW), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	
	SetAlwaysRunFlag(TRUE);//画面を常にアクティブ

	// ウィンドウの名前
	SetMainWindowText("複製のHeart");

	////マウス関連////
	SetMouseDispFlag(MOUSE_DISP);//マウス表示
	//SetMousePoint(320, 240);//マウスカーソルの初期位置
	
	// 画像の拡大処理方式
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	//SetDrawMode(DX_DRAWMODE_NEAREST);
	SetFullScreenScalingMode(DX_DRAWMODE_NEAREST);

	Game* game = new Game();
	GameDrawer drawer(game);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		updateKey();
		mouseClick();

		/////メイン////
		game->play();
		drawer.draw();
		///////////////

		//FPS操作
		if (controlDebug() == TRUE) {
			if (debug == FALSE) { debug = TRUE; }
			else { debug = FALSE; }
		}
		Update();
		// デバッグ
		if (debug == TRUE) {
			Draw(0, 0, BLACK);
		}
		Wait();
		if (controlEsc() == TRUE) { 
			break;
		}
		//FPS操作ここまで
	}
	
	delete game;
	DxLib_End(); // DXライブラリ終了処理
	return 0;
}