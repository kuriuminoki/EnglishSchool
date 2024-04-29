#include "Button.h"
#include "Control.h"
#include "Define.h"
#include "Study.h"
#include "Vocabulary.h"
#include "DxLib.h"

#include <sstream>

using namespace std;


/*
* ���K
*/
Study::Study(int font) {
	m_font = font;
	m_state = STUDY_MODE::SELECT_MODE;
	m_wordTestStudy = new WordTestStudy();
	m_wordAddStudy = new WordAddStudy();
	m_finishButton= new Button("�I��", 1650, 50, 200, 100, GRAY, WHITE, m_font, BLACK);
	m_wordTestButton = new Button("�P��e�X�g", 50, 300, 200, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_wordAddButton = new Button("�P��ǉ�", 300, 300, 200, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
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
			m_wordTestStudy->init();
		}
		switch (m_state) {
		case WORD_TEST:
			m_wordTestStudy->play(handX, handY);
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
			m_wordTestStudy->draw(handX, handY);
			break;
		case WORD_ADD:
			m_wordAddStudy->draw();
			break;
		}
	}
}


/*
* �P��e�X�g�i���K�j
*/
WordTestStudy::WordTestStudy() {
	m_vocabulary = new Vocabulary("data/vocabulary/vocabulary.csv");
	m_vocabulary->shuffle();
	m_font = CreateFontToHandle(NULL, 40, 3);
	m_answerButton = new Button("���𔭕\", 100, 750, 200, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_nextButton = new Button("����", 400, 750, 200, 100, BLUE, BLUE, m_font, BLACK);
	m_importantButton = new Button("�v����", 700, 750, 200, 100, LIGHT_RED, RED, m_font, BLACK);
	m_removeButton = new Button("�폜", 1700, 750, 150, 100, GRAY, WHITE, m_font, BLACK);
	m_nextButton->changeFlag(false, BLUE);
}

WordTestStudy::~WordTestStudy() {
	delete m_vocabulary;
	DeleteFontToHandle(m_font);
}

bool WordTestStudy::play(int handX, int handY) {
	if (leftClick() == 1) {
		if (m_answerButton->overlap(handX, handY)) {
			m_nextButton->changeFlag(true, LIGHT_BLUE);
		}
		if (m_nextButton->overlap(handX, handY)) {
			m_vocabulary->goNextWord();
			m_nextButton->changeFlag(false, BLUE);
		}
		if (m_importantButton->overlap(handX, handY)) {
			m_vocabulary->setImportantFlag(!m_vocabulary->getWord().importantFlag);
		}
		if (m_removeButton->overlap(handX, handY)) {
			m_vocabulary->removeWord();
		}
	}
	return false;
}

void WordTestStudy::init() {
	m_vocabulary->init();
	m_vocabulary->shuffle();
}

void WordTestStudy::draw(int handX, int handY) const {
	Word word = m_vocabulary->getWord();
	if (word.importantFlag) {
		DrawStringToHandle(100, 300, "�v���ӁI�I", RED, m_font);
	}
	DrawStringToHandle(100, 400, word.english.c_str(), WHITE, m_font);
	if (m_nextButton->getFlag()) {
		DrawStringToHandle(100, 500, word.japanese.c_str(), BLUE, m_font);
	}
	DrawStringToHandle(150, 600, ("��F" + word.example).c_str(), WHITE, m_font);
	m_answerButton->draw(handX, handY);
	m_importantButton->draw(handX, handY);
	m_nextButton->draw(handX, handY);
	m_removeButton->draw(handX, handY);
	ostringstream oss;
	oss << "���P�ꐔ�F" << m_vocabulary->getIndex() + 1 << "/" << m_vocabulary->getWordSum() << ", �v���ӒP��F" << m_vocabulary->getImportantWordSum() << "��";
	DrawStringToHandle(100, 950, oss.str().c_str(), WHITE, m_font);
}


/*
* �P��ǉ�
*/
WordAddStudy::WordAddStudy() {
	m_vocabulary = new Vocabulary("data/vocabulary/vocabulary.csv");
}

WordAddStudy::~WordAddStudy() {
	delete m_vocabulary;
}

bool WordAddStudy::play() {
	return false;
}

void WordAddStudy::draw() {

}