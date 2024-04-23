#include "Control.h"
#include "Game.h"
#include "Lesson.h"
#include "Setting.h"
#include "Study.h"


Game::Game() {
	m_state = GAME_MODE::SELECT_MODE;
	m_selectMode = new SelectMode();
	m_lesson = new Lesson();
	m_study = new Study();
	m_setting = new Setting();
}

Game::~Game() {
	delete m_selectMode;
	delete m_lesson;
	delete m_study;
	delete m_setting;
}

void Game::play() {
	switch (m_state) {
	case SELECT_MODE:
		m_state = m_selectMode->play();
		break;
	case LESSON_MODE:
		if (m_lesson->play()) {
			m_state = SELECT_MODE;
		}
		break;
	case STUDY_MODE:
		if (m_study->play()) {
			m_state = SELECT_MODE;
		}
		break;
	case SETTING_MODE:
		if (m_setting->play()) {
			m_state = SELECT_MODE;
		}
		break;
	}
}


/*
* ÉÇÅ[ÉhëIëâÊñ 
*/
SelectMode::SelectMode() {

}

SelectMode::~SelectMode() {

}

GAME_MODE SelectMode::play() {

	if (leftClick() == 1) {
		return GAME_MODE::LESSON_MODE;
	}

	return GAME_MODE::SELECT_MODE;
}