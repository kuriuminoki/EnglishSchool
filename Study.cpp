#include "Button.h"
#include "Control.h"
#include "Define.h"
#include "Study.h"
#include "Teacher.h"
#include "Timer.h"
#include "Vocabulary.h"
#include "DxLib.h"

#include <sstream>

using namespace std;


/*
* ���K
*/
Study::Study(int font, Teacher* teacher_p) {
	m_font = font;
	m_teacher_p = teacher_p;
	m_state = STUDY_MODE::SELECT_MODE;
	m_wordTestStudy = new WordTestStudy(m_teacher_p);
	m_finishButton= new Button("�I��", 1650, 50, 200, 100, GRAY, WHITE, m_font, BLACK);
	m_wordTestButton = new Button("�S�P��e�X�g", 100, 300, 400, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_onlyImportantTestButton = new Button("�d�v��̂݃e�X�g", 550, 300, 400, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
}

Study::~Study() {
	delete m_wordTestStudy;
	delete m_finishButton;
	delete m_wordTestButton;
	delete m_onlyImportantTestButton;
}

bool Study::play(int handX, int handY) {

	if (m_state == STUDY_MODE::SELECT_MODE) {
		if (leftClick() == 1) {
			if (m_wordTestButton->overlap(handX, handY)) {
				m_state = STUDY_MODE::WORD_TEST;
			}
			else if (m_onlyImportantTestButton->overlap(handX, handY)) {
				m_state = STUDY_MODE::WORD_TEST_IMPORTANT;
				m_wordTestStudy->init(true);
			}
		}
	}
	else {
		if (leftClick() == 1 && m_finishButton->overlap(handX, handY)) {
			m_state = STUDY_MODE::SELECT_MODE;
			m_wordTestStudy->init(false);
		}
		switch (m_state) {
		case WORD_TEST:
			m_wordTestStudy->play(handX, handY, false);
			break;
		case WORD_TEST_IMPORTANT:
			m_wordTestStudy->play(handX, handY, true);
			break;
		}
	}

	return false;

}

void Study::draw(int handX, int handY) const {
	if (m_state == STUDY_MODE::SELECT_MODE) {
		m_wordTestButton->draw(handX, handY);
		m_onlyImportantTestButton->draw(handX, handY);
	}
	else {
		m_finishButton->draw(handX, handY);
		switch (m_state) {
		case WORD_TEST:
		case WORD_TEST_IMPORTANT:
			m_wordTestStudy->draw(handX, handY);
			break;
		}
	}
}


/*
* �P��e�X�g�i���K�j
*/
WordTestStudy::WordTestStudy(Teacher* teacher_p) {
	m_teacher_p = teacher_p;
	m_vocabulary = new Vocabulary("data/vocabulary/vocabulary.csv");
	m_vocabulary->shuffle();
	m_font = CreateFontToHandle(NULL, 40, 3);
	m_answerButton = new Button("���𔭕\", 100, 750, 200, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_nextButton = new Button("����", 400, 750, 200, 100, BLUE, BLUE, m_font, BLACK);
	m_importantButton = new Button("�v����", 700, 750, 200, 100, LIGHT_RED, RED, m_font, BLACK);
	m_removeButton = new Button("�폜", 1150, 750, 150, 100, GRAY, WHITE, m_font, BLACK);
	m_nextButton->changeFlag(false, BLUE);
	m_stopWatch = new StopWatch();
}

WordTestStudy::~WordTestStudy() {
	m_vocabulary->write();
	delete m_vocabulary;
	DeleteFontToHandle(m_font);
	delete m_answerButton;
	delete m_nextButton;
	delete m_importantButton;
	delete m_removeButton;
	delete m_stopWatch;
}

bool WordTestStudy::play(int handX, int handY, bool onlyImportant) {
	m_stopWatch->count();
	if (leftClick() == 1) {
		if (m_answerButton->overlap(handX, handY)) {
			m_nextButton->changeFlag(true, LIGHT_BLUE);
			m_teacher_p->setText(2, 120, EMOTE::NORMAL, true);
		}
		if (m_nextButton->overlap(handX, handY)) {
			m_vocabulary->goNextWord(onlyImportant);
			m_nextButton->changeFlag(false, BLUE);
			m_teacher_p->setText(1, 120, EMOTE::NORMAL, true);
		}
		if (m_importantButton->overlap(handX, handY)) {
			m_vocabulary->setImportantFlag(!m_vocabulary->getWord().importantFlag);
			if (m_vocabulary->getWord().importantFlag){ m_teacher_p->setText(3, 120, EMOTE::ANGRY, true); }
			else{ m_teacher_p->setText(4, 120, EMOTE::SMILE, true); }
		}
		if (m_removeButton->overlap(handX, handY)) {
			m_vocabulary->removeWord();
		}
	}
	return false;
}

void WordTestStudy::init(bool onlyImportant) {
	m_nextButton->changeFlag(false, BLUE);
	m_vocabulary->write();
	m_vocabulary->init();
	m_vocabulary->shuffle();
	if (onlyImportant) {
		m_vocabulary->setFirstImportantWord();
	}
	m_stopWatch->init();
}

void WordTestStudy::draw(int handX, int handY) const {
	DrawStringToHandle(600, 250, getTimeString(m_stopWatch->getCnt()).c_str(), WHITE, m_font);
	Word word = m_vocabulary->getWord();
	if (word.importantFlag) {
		DrawStringToHandle(100, 350, "�v���ӁI�I", RED, m_font);
	}
	DrawStringToHandle(100, 430, word.english.c_str(), WHITE, m_font);
	if (m_nextButton->getFlag()) {
		DrawStringToHandle(100, 500, word.japanese.c_str(), LIGHT_BLUE, m_font);
	}
	if (word.example != "") {
		DrawStringToHandle(120, 600, ("usage: " + word.example).c_str(), WHITE, m_font);
	}
	m_answerButton->draw(handX, handY);
	m_importantButton->draw(handX, handY);
	m_nextButton->draw(handX, handY);
	m_removeButton->draw(handX, handY);
	ostringstream oss;
	oss << "���P�ꐔ�F" << m_vocabulary->getIndex() + 1 << "/" << m_vocabulary->getWordSum() << ", �v���ӒP��F" << m_vocabulary->getImportantWordSum() << "��";
	DrawStringToHandle(100, 900, oss.str().c_str(), WHITE, m_font);
}

