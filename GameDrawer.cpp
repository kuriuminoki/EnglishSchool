#include "Define.h"
#include "Game.h"
#include "GameDrawer.h"

#include "DxLib.h"


GameDrawer::GameDrawer(const Game* game) {
	m_game_p = game;
}

GameDrawer::~GameDrawer() {
	
}

void GameDrawer::draw() {
	GAME_MODE state = m_game_p->getState();
	DrawFormatString(100, 100, WHITE, "GameDrawer: state=%d", state);
}