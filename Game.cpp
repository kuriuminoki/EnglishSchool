#include "Button.h"
#include "Control.h"
#include "Define.h"
#include "Game.h"
#include "Lesson.h"
#include "Setting.h"
#include "Study.h"
#include "Teacher.h"


Game::Game() {
	m_teacher = new Teacher("トモチ");
	m_teacher->setRandomText();
	m_handX = 0;
	m_handY = 0;
	m_state = GAME_MODE::SELECT_MODE;
	m_font = CreateFontToHandle(NULL, 40, 3);
	m_selectMode = new SelectMode(m_font);
	m_lesson = new Lesson();
	m_study = new Study(m_font, m_teacher);
	m_setting = new Setting();
	m_backButton = new Button("タイトルへ戻る", 50, 50, 300, 100, GRAY, WHITE, m_font, BLACK);
}

Game::~Game() {
	DeleteFontToHandle(m_font);
	delete m_selectMode;
	delete m_lesson;
	delete m_study;
	delete m_setting;
	delete m_teacher;
}

void Game::play() {

	GetMousePoint(&m_handX, &m_handY);

	m_teacher->play();

	switch (m_state) {
	case SELECT_MODE:
		m_state = m_selectMode->play(m_handX, m_handY);
		break;
	case LESSON_MODE:
		if (m_lesson->play()) {
			m_state = SELECT_MODE;
		}
		break;
	case STUDY_MODE:
		if (m_study->play(m_handX, m_handY)) {
			m_state = SELECT_MODE;
		}
		break;
	case SETTING_MODE:
		if (m_setting->play()) {
			m_state = SELECT_MODE;
		}
		break;
	}

	// タイトルへ戻る
	if (leftClick() == 1) {
		if (m_state != GAME_MODE::SELECT_MODE && m_backButton->overlap(m_handX, m_handY)) {
			m_state = GAME_MODE::SELECT_MODE;
			m_teacher->setRandomText();
		}
	}
}

void Game::draw() const {
	if (m_state != GAME_MODE::SELECT_MODE) {
		m_backButton->draw(m_handX, m_handY);
	}
}


/*
* モード選択画面
*/
SelectMode::SelectMode(int font) {
	m_font = font;
	m_lessonButton = new Button("授業", 100, 300, 300, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_studyButton = new Button("自習", 450, 300, 300, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_settingButton = new Button("設定", 800, 300, 300, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
}

SelectMode::~SelectMode() {
	delete m_lessonButton;
	delete m_studyButton;
	delete m_settingButton;
}

GAME_MODE SelectMode::play(int handX, int handY) {

	// ボタンを押下してモード決定
	if (leftClick() == 1) {
		if (m_lessonButton->overlap(handX, handY)) {
			return GAME_MODE::LESSON_MODE;
		}
		if (m_studyButton->overlap(handX, handY)) {
			return GAME_MODE::STUDY_MODE;
		}
		if (m_settingButton->overlap(handX, handY)) {
			return GAME_MODE::SETTING_MODE;
		}
	}

	return GAME_MODE::SELECT_MODE;
}

void SelectMode::draw(int handX, int handY) const {
	m_lessonButton->draw(handX, handY);
	m_studyButton->draw(handX, handY);
	m_settingButton->draw(handX, handY);
}