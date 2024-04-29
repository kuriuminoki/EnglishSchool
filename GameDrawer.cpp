#include "Define.h"
#include "Game.h"
#include "GameDrawer.h"
#include "StudyDrawer.h"

#include "DxLib.h"


GameDrawer::GameDrawer(const Game* game) {
	m_game_p = game;
	m_studyDrawer = new StudyDrawer(m_game_p->getStudy());
}

GameDrawer::~GameDrawer() {
	delete m_studyDrawer;
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
		m_studyDrawer->draw(handX, handY);
		break;
	case SETTING_MODE:

		break;
	}

}