#include "Button.h"
#include "Control.h"
#include "Define.h"
#include "Study.h"
#include "Teacher.h"
#include "Timer.h"
#include "Vocabulary.h"
#include "DxLib.h"

#include <algorithm>
#include <sstream>

using namespace std;


DynamicFont::DynamicFont(int size, int thick) {
	createFont(size, thick);
}

DynamicFont::~DynamicFont() {
	DeleteFontToHandle(m_font);
}

void DynamicFont::changeFont(int mouseWheel) {
	if (mouseWheel == 0) { return; }
	DeleteFontToHandle(m_font);
	if (mouseWheel > 0) {
		createFont(min(m_size + 1, MAX_SIZE), m_thick);
	}
	else {
		createFont(max(m_size - 1, MIN_SIZE), m_thick);
	}
}

void DynamicFont::createFont(int size, int thick) {
	m_size = size;
	m_thick = thick;
	m_font = CreateFontToHandle(NULL, m_size, m_thick);
}


/*
* 自習
*/
Study::Study(int font, Teacher* teacher_p) {
	m_font = font;
	m_teacher_p = teacher_p;
	m_state = STUDY_MODE::SELECT_MODE;
	m_wordTestStudy = new WordTestStudy(m_teacher_p);
	m_speakingPractiace = new SpeakingPractice(m_teacher_p);
	m_finishButton= new Button("終了", 1650, 50, 200, 100, GRAY, WHITE, m_font, BLACK);
	m_wordTestButton = new Button("全単語テスト", 100, 300, 400, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_onlyImportantTestButton = new Button("重要語のみテスト", 550, 300, 400, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_speakingPracticeButton = new Button("音読練習", 100, 450, 400, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_onlyImportantspeakingPracticeButton = new Button("重要文のみ音読", 550, 450, 400, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
}

Study::~Study() {
	delete m_wordTestStudy;
	delete m_speakingPractiace;
	delete m_finishButton;
	delete m_wordTestButton;
	delete m_onlyImportantTestButton;
}

bool Study::play(int handX, int handY, int mouseWheel) {

	if (m_state == STUDY_MODE::SELECT_MODE) {
		if (leftClick() == 1) {
			if (m_wordTestButton->overlap(handX, handY)) {
				m_state = STUDY_MODE::WORD_TEST;
				m_wordTestStudy->init(false);
			}
			else if (m_onlyImportantTestButton->overlap(handX, handY)) {
				m_state = STUDY_MODE::WORD_TEST_IMPORTANT;
				m_wordTestStudy->init(true);
			}
			else if (m_speakingPracticeButton->overlap(handX, handY)) {
				m_state = STUDY_MODE::SPEAKING_PRACTICE;
				m_speakingPractiace->init(false);
			}
			else if (m_onlyImportantspeakingPracticeButton->overlap(handX, handY)) {
				m_state = STUDY_MODE::SPEAKING_PRACTICE_IMPORTANT;
				m_speakingPractiace->init(true);
			}
		}
	}
	else {
		m_teacher_p->addExp(1);
		if (leftClick() == 1 && m_finishButton->overlap(handX, handY)) {
			m_state = STUDY_MODE::SELECT_MODE;
			m_wordTestStudy->end();
			m_speakingPractiace->end();
		}
		switch (m_state) {
		case WORD_TEST:
			m_wordTestStudy->play(handX, handY, mouseWheel, false);
			break;
		case WORD_TEST_IMPORTANT:
			m_wordTestStudy->play(handX, handY, mouseWheel, true);
			break;
		case SPEAKING_PRACTICE:
			m_speakingPractiace->play(handX, handY, mouseWheel, false);
			break;
		case SPEAKING_PRACTICE_IMPORTANT:
			m_speakingPractiace->play(handX, handY, mouseWheel, true);
			break;
		}
	}

	return false;

}

void Study::draw(int handX, int handY) const {
	if (m_state == STUDY_MODE::SELECT_MODE) {
		m_wordTestButton->draw(handX, handY);
		m_onlyImportantTestButton->draw(handX, handY);
		m_speakingPracticeButton->draw(handX, handY);
		m_onlyImportantspeakingPracticeButton->draw(handX, handY);
	}
	else {
		m_finishButton->draw(handX, handY);
		switch (m_state) {
		case WORD_TEST:
		case WORD_TEST_IMPORTANT:
			m_wordTestStudy->draw(handX, handY);
			break;
		case SPEAKING_PRACTICE:
		case SPEAKING_PRACTICE_IMPORTANT:
			m_speakingPractiace->draw(handX, handY);
			break;
		}
	}
}


/*
* 単語テスト（自習）
*/
WordTestStudy::WordTestStudy(Teacher* teacher_p) {
	m_teacher_p = teacher_p;
	m_vocabulary = nullptr;
	m_font = CreateFontToHandle(NULL, 40, 3);
	m_miniFont = CreateFontToHandle(NULL, 30, 5);
	m_dynamicFont = new DynamicFont(40, 3);
	m_answerButton = new Button("正解発表", 100, 750, 200, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_nextButton = new Button("次へ", 320, 750, 200, 100, BLUE, BLUE, m_font, BLACK);
	m_importantButton = new Button("要注意", 540, 750, 200, 100, LIGHT_RED, RED, m_font, BLACK);
	m_prevButton = new Button("戻る", 760, 750, 150, 100, BLUE, BLUE, m_font, BLACK);
	m_removeButton = new Button("長押しで削除", 1100, 750, 200, 100, GRAY, WHITE, m_miniFont, BLACK);
	m_nextButton->changeFlag(false, BLUE);
	m_stopWatch = new StopWatch();
}

WordTestStudy::~WordTestStudy() {
	if (m_vocabulary != nullptr) {
		m_vocabulary->write();
		delete m_vocabulary;
	}
	DeleteFontToHandle(m_font);
	DeleteFontToHandle(m_miniFont);
	delete m_answerButton;
	delete m_nextButton;
	delete m_importantButton;
	delete m_prevButton;
	delete m_removeButton;
	delete m_stopWatch;
}

bool WordTestStudy::play(int handX, int handY, int mouseWheel, bool onlyImportant) {

	m_stopWatch->count();

	if (m_vocabulary->getIndex() == m_vocabulary->getPrevIndex()) {
		m_prevButton->changeFlag(false, BLUE);
	}
	else {
		m_prevButton->changeFlag(true, LIGHT_BLUE);
	}
	m_dynamicFont->changeFont(mouseWheel);
	if (leftClick() == 1) {
		if (m_answerButton->overlap(handX, handY)) {
			m_nextButton->changeFlag(true, LIGHT_BLUE);
			m_teacher_p->setText(2, 120, EMOTE::NORMAL, true);
		}
		if (m_nextButton->overlap(handX, handY)) {
			m_vocabulary->goNextWord(onlyImportant);
			m_nextButton->changeFlag(false, BLUE);
			m_teacher_p->setText(1, 120, EMOTE::NORMAL, true);
			m_vocabulary->wordCount();
		}
		if (m_prevButton->overlap(handX, handY)) {
			m_vocabulary->goPrevWord();
			m_vocabulary->wordCount();
		}
		if (m_importantButton->overlap(handX, handY)) {
			m_vocabulary->setImportantFlag(!m_vocabulary->getWord().importantFlag);
			if (m_vocabulary->getWord().importantFlag){ m_teacher_p->setText(3, 120, EMOTE::ANGRY, true); }
			else{ m_teacher_p->setText(4, 120, EMOTE::SMILE, true); }
		}
	}

	if (leftClick() == 60) {
		if (m_removeButton->overlap(handX, handY)) {
			m_vocabulary->removeWord();
		}
	}

	return false;

}

void WordTestStudy::init(bool onlyImportant) {
	m_nextButton->changeFlag(false, BLUE);
	if (m_vocabulary != nullptr) {
		end();
	}
	m_vocabulary = new Vocabulary("data/vocabulary/vocabulary.csv");
	m_vocabulary->init();
	m_vocabulary->shuffle();
	if (onlyImportant) {
		m_vocabulary->setFirstImportantWord();
	}
	m_vocabulary->wordCount();
	m_stopWatch->init();
}

void WordTestStudy::end() {
	if (m_vocabulary != nullptr) {
		m_vocabulary->write();
		delete m_vocabulary;
		m_vocabulary = nullptr;
	}
}

void WordTestStudy::draw(int handX, int handY) const {
	DrawStringToHandle(600, 250, getTimeString(m_stopWatch->getCnt()).c_str(), WHITE, m_font);
	Word word = m_vocabulary->getWord();
	if (word.importantFlag) {
		DrawStringToHandle(100, 350, "要注意！！", RED, m_font);
	}
	DrawStringToHandle(100, 430, word.english.c_str(), WHITE, m_font);
	if (m_nextButton->getFlag()) {
		DrawStringToHandle(100, 500, word.japanese.c_str(), LIGHT_BLUE, m_font);
	}
	if (word.example != "") {
		DrawStringToHandle(120, 600, ("usage: " + word.example).c_str(), WHITE, m_dynamicFont->getFont());
	}
	m_answerButton->draw(handX, handY);
	m_importantButton->draw(handX, handY);
	m_nextButton->draw(handX, handY);
	m_prevButton->draw(handX, handY);
	m_removeButton->draw(handX, handY);
	ostringstream count;
	count << "総出題回数：" << word.count;
	DrawStringToHandle(120, 670, count.str().c_str(), WHITE, m_font);
	ostringstream oss;
	oss << "総単語数：" << m_vocabulary->getIndex() + 1 << "/" << m_vocabulary->getWordSum() << ", 要注意単語：" << m_vocabulary->getImportantWordSum() << "個";
	DrawStringToHandle(100, 900, oss.str().c_str(), WHITE, m_font);
}


/*
* 単語テスト（自習）
*/
SpeakingPractice::SpeakingPractice(Teacher* teacher_p) {
	m_hideState = HIDE_STATE::NO_HIDE;
	m_teacher_p = teacher_p;
	m_speakingSets = nullptr;
	m_font = CreateFontToHandle(NULL, 40, 3);
	m_sentenceFont = CreateFontToHandle(NULL, 30, 3);
	m_dynamicFont = new DynamicFont(30, 3);
	m_repeatButton = new Button("もう一度", 100, 750, 170, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_answerButton = new Button("英文隠し", 300, 750, 170, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_nextButton = new Button("次へ", 500, 750, 170, 100, BLUE, BLUE, m_font, BLACK);
	m_importantButton = new Button("要注意", 700, 750, 170, 100, LIGHT_RED, RED, m_font, BLACK);
	m_nextButton->changeFlag(false, BLUE);
	m_stopWatch = new StopWatch();
}

SpeakingPractice::~SpeakingPractice() {
	if (m_speakingSets != nullptr) {
		m_speakingSets->write();
		delete m_speakingSets;
	}
	DeleteFontToHandle(m_font);
	DeleteFontToHandle(m_sentenceFont);
	delete m_dynamicFont;
	delete m_repeatButton;
	delete m_answerButton;
	delete m_nextButton;
	delete m_importantButton;
	delete m_stopWatch;
}

bool SpeakingPractice::play(int handX, int handY, int mouseWheel, bool onlyImportant) {
	if (m_stopWatch->getCnt() == 0) {
		m_teacher_p->speaking(m_speakingSets->getSentence().english, 120, EMOTE::NORMAL, true);
	}
	m_stopWatch->count();
	if (m_speakingSets->speak()) {
		m_nextButton->changeFlag(true, LIGHT_BLUE);
	}
	m_dynamicFont->changeFont(mouseWheel);
	if (leftClick() == 1) {
		if (m_repeatButton->overlap(handX, handY)) {
			// もう一度
			m_nextButton->changeFlag(false, BLUE);
			m_speakingSets->setZeroNow();
			m_teacher_p->speaking(m_speakingSets->getSentence().english, 120, EMOTE::NORMAL, true);
		}
		if (m_answerButton->overlap(handX, handY)) {
			switch (m_hideState) {
			case NO_HIDE:
				m_hideState = EN_HIDE;
				break;
			case EN_HIDE:
				m_hideState = EN_HINT_HIDE;
				break;
			default:
				m_hideState = NO_HIDE;
				break;
			}
		}
		if (m_nextButton->overlap(handX, handY)) {
			m_speakingSets->goNextSentence(onlyImportant);
			m_nextButton->changeFlag(false, BLUE);
			m_teacher_p->speaking(m_speakingSets->getSentence().english, 120, EMOTE::NORMAL, true);
		}
		if (m_importantButton->overlap(handX, handY)) {
			m_speakingSets->setImportantFlag(!m_speakingSets->getSentence().importantFlag);
			if (m_speakingSets->getSentence().importantFlag) { m_teacher_p->setText(3, 120, EMOTE::ANGRY, true); }
			else { m_teacher_p->setText(4, 120, EMOTE::SMILE, true); }
		}
	}
	return false;
}

void SpeakingPractice::init(bool onlyImportant) {
	m_nextButton->changeFlag(false, BLUE);
	if (m_speakingSets != nullptr) {
		end();
	}
	m_speakingSets = new SpeakingSet("data/speaking/speaking.csv");
	m_speakingSets->init();
	m_speakingSets->shuffle();
	if (onlyImportant) {
		m_speakingSets->setFirstImportantSentence();
	}
	m_stopWatch->init();
}

void SpeakingPractice::end() {
	if (m_speakingSets != nullptr) {
		m_speakingSets->write();
		delete m_speakingSets;
		m_speakingSets = nullptr;
	}
}

void SpeakingPractice::draw(int handX, int handY) const {
	DrawStringToHandle(600, 250, getTimeString(m_stopWatch->getCnt()).c_str(), WHITE, m_font);
	Sentence sentence = m_speakingSets->getSentence();
	if (sentence.importantFlag) {
		DrawStringToHandle(100, 350, "要注意！！", RED, m_font);
	}
	if (m_hideState == NO_HIDE) {
		string disp = sentence.english.substr(0, m_speakingSets->getNow());
		DrawStringToHandle(100, 430, disp.c_str(), WHITE, m_dynamicFont->getFont());
	}
	DrawStringToHandle(100, 500, sentence.japanese.c_str(), LIGHT_BLUE, m_dynamicFont->getFont());
	if (m_hideState != EN_HINT_HIDE && sentence.appendix != "") {
		DrawStringToHandle(120, 600, ("ポイント：" + sentence.appendix).c_str(), WHITE, m_dynamicFont->getFont());
	}
	ostringstream count;
	count << "音読総数：" << sentence.count;
	DrawStringToHandle(950, 800, count.str().c_str(), WHITE, m_font);
	m_repeatButton->draw(handX, handY);
	m_importantButton->draw(handX, handY);
	m_answerButton->draw(handX, handY);
	m_nextButton->draw(handX, handY);
	ostringstream oss;
	oss << "総文章数：" << m_speakingSets->getIndex() + 1 << "/" << m_speakingSets->getSentenceSum() << ", 要注意文章：" << m_speakingSets->getImportantSentenceSum() << "個";
	DrawStringToHandle(100, 900, oss.str().c_str(), WHITE, m_font);
}