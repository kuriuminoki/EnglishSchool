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

	m_game_p->draw();

	int handX = m_game_p->getHandX();
	int handY = m_game_p->getHandY();

	GAME_MODE state = m_game_p->getState();
	switch (state) {
	case SELECT_MODE:
		m_game_p->getSelectMode()->draw(handX, handY);
		break;
	case LESSON_MODE:

		break;
	case STUDY_MODE:

		break;
	case SETTING_MODE:

		break;
	}

}