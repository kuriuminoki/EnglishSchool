#include "Button.h"
#include "Control.h"
#include "Define.h"
#include "Study.h"
#include "Teacher.h"
#include "Vocabulary.h"
#include "DxLib.h"

#include <sstream>

using namespace std;


/*
* 自習
*/
Study::Study(int font, Teacher* teacher_p) {
	m_font = font;
	m_teacher_p = teacher_p;
	m_state = STUDY_MODE::SELECT_MODE;
	m_wordTestStudy = new WordTestStudy(m_teacher_p);
	m_wordAddStudy = new WordAddStudy();
	m_finishButton= new Button("終了", 1650, 50, 200, 100, GRAY, WHITE, m_font, BLACK);
	m_wordTestButton = new Button("単語テスト", 100, 300, 200, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_wordAddButton = new Button("単語追加", 350, 300, 200, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
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
* 単語テスト（自習）
*/
WordTestStudy::WordTestStudy(Teacher* teacher_p) {
	m_teacher_p = teacher_p;
	m_vocabulary = new Vocabulary("data/vocabulary/vocabulary.csv");
	m_vocabulary->shuffle();
	m_font = CreateFontToHandle(NULL, 40, 3);
	m_answerButton = new Button("正解発表", 100, 750, 200, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_nextButton = new Button("次へ", 400, 750, 200, 100, BLUE, BLUE, m_font, BLACK);
	m_importantButton = new Button("要注意", 700, 750, 200, 100, LIGHT_RED, RED, m_font, BLACK);
	m_removeButton = new Button("削除", 1150, 750, 150, 100, GRAY, WHITE, m_font, BLACK);
	m_nextButton->changeFlag(false, BLUE);
}

WordTestStudy::~WordTestStudy() {
	m_vocabulary->write();
	delete m_vocabulary;
	DeleteFontToHandle(m_font);
}

bool WordTestStudy::play(int handX, int handY) {
	if (leftClick() == 1) {
		if (m_answerButton->overlap(handX, handY)) {
			m_nextButton->changeFlag(true, LIGHT_BLUE);
			m_teacher_p->setText(2, 120, EMOTE::NORMAL, true);
		}
		if (m_nextButton->overlap(handX, handY)) {
			m_vocabulary->goNextWord();
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

void WordTestStudy::init() {
	m_nextButton->changeFlag(false, BLUE);
	m_vocabulary->write();
	m_vocabulary->init();
	m_vocabulary->shuffle();
}

void WordTestStudy::draw(int handX, int handY) const {
	Word word = m_vocabulary->getWord();
	if (word.importantFlag) {
		DrawStringToHandle(100, 300, "要注意！！", RED, m_font);
	}
	DrawStringToHandle(100, 400, word.english.c_str(), WHITE, m_font);
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
	oss << "総単語数：" << m_vocabulary->getIndex() + 1 << "/" << m_vocabulary->getWordSum() << ", 要注意単語：" << m_vocabulary->getImportantWordSum() << "個";
	DrawStringToHandle(100, 900, oss.str().c_str(), WHITE, m_font);
}


/*
* 単語追加
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