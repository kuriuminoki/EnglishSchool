#include "Button.h"
#include "Control.h"
#include "Define.h"
#include "Study.h"


/*
* 自習
*/
Study::Study(int font) {
	m_font = font;
	m_state = STUDY_MODE::SELECT_MODE;
	m_wordTestStudy = new WordTestStudy();
	m_wordAddStudy = new WordAddStudy();
	m_finishButton= new Button("終了", 1650, 50, 200, 100, GRAY, WHITE, m_font, BLACK);
	m_wordTestButton = new Button("単語テスト", 50, 300, 200, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_wordAddButton = new Button("単語追加", 300, 300, 200, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
}

Study::~Study() {
	delete m_wordTestStudy;
	delete m_wordAddStudy;
	delete m_finishButton;
	delete m_wordTestButton;
	delete m_wordAddButton;
}

bool Study::play(int handX, int handY) {

	if (m_state == STUDY_MODE::SELECT_MODE) {
		if (leftClick() == 1) {
			if (m_wordTestButton->overlap(handX, handY)) {
				m_state = STUDY_MODE::WORD_TEST;
			}
			else if (m_wordAddButton->overlap(handX, handY)) {
				m_state = STUDY_MODE::WORD_ADD;
			}
		}
	}
	else {
		if (leftClick() == 1 && m_finishButton->overlap(handX, handY)) {
			m_state = STUDY_MODE::SELECT_MODE;
		}
		switch (m_state) {
		case WORD_TEST:
			m_wordTestStudy->play();
			break;
		case WORD_ADD:
			m_wordAddStudy->play();
			break;
		}
	}

	return false;

}

void Study::draw(int handX, int handY) const {
	if (m_state == STUDY_MODE::SELECT_MODE) {
		m_wordTestButton->draw(handX, handY);
		m_wordAddButton->draw(handX, handY);
	}
	else {
		m_finishButton->draw(handX, handY);
		switch (m_state) {
		case WORD_TEST:
			m_wordTestStudy->draw();
			break;
		case WORD_ADD:
			m_wordAddStudy->draw();
			break;
		}
	}
}


/*
* 単語テスト（自習）
*/
WordTestStudy::WordTestStudy() {

}

WordTestStudy::~WordTestStudy() {

}

bool WordTestStudy::play() {
	return false;
}

void WordTestStudy::draw() {

}


/*
* 単語追加
*/
WordAddStudy::WordAddStudy() {

}

WordAddStudy::~WordAddStudy() {

}

bool WordAddStudy::play() {
	return false;
}

void WordAddStudy::draw() {

}