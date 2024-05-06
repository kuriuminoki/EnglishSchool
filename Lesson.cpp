#include "Lesson.h"
#include "Button.h"
#include "Control.h"
#include "Define.h"
#include "Study.h"
#include "Teacher.h"
#include "Timer.h"

#include <string>

using namespace std;


Lesson::Lesson(int font, Teacher* teacher_p) {

	m_font = font;
	m_teacher_p = teacher_p;

	m_state = LESSON_NAME::SELECT_LESSON;

	m_stopWatch = new StopWatch();

	m_wordTestStudy = new WordTestStudy(m_teacher_p);

	m_finishButton = new Button("終了", 1650, 50, 200, 100, GRAY, WHITE, m_font, BLACK);
	m_wordTestButton = new Button("全単語テスト", 100, 300, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_onlyImportantTestButton = new Button("重要語のみテスト", 500, 300, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_diaryButton = new Button("日記", 900, 300, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_radioReviewButton = new Button("ラジオ復習", 100, 450, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_grammarStudyButton = new Button("文法勉強", 500, 450, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_breakTimeButton = new Button("休憩", 900, 450, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_freeStudyButton = new Button("自習", 100, 600, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_longTextStudyButton = new Button("長文問題", 500, 600, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_morningReviewButton = new Button("朝の振り返り", 900, 600, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_radioButton = new Button("ラジオ英会話", 100, 750, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_speakingStudyButton = new Button("音読練習", 500, 750, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_eveningReviewButton = new Button("夜の振り返り", 900, 750, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);

}

Lesson::~Lesson() {
	delete m_stopWatch;
	delete m_wordTestStudy;
	delete m_finishButton;
	delete m_wordTestButton;
	delete m_onlyImportantTestButton;
	delete m_diaryButton;
	delete m_radioReviewButton;
	delete m_grammarStudyButton;
	delete m_breakTimeButton;
	delete m_freeStudyButton;
	delete m_longTextStudyButton;
	delete m_morningReviewButton;
	delete m_radioButton;
	delete m_speakingStudyButton;
	delete m_eveningReviewButton;
}

bool Lesson::play(int handX, int handY) {
	m_stopWatch->count();
	switch (m_state) {
		case SELECT_LESSON:			// レッスン選択画面
			if (leftClick() == 1) {
				if (m_wordTestButton->overlap(handX, handY)) {
					m_state = LESSON_NAME::WORD_TEST;
				}
				else if (m_onlyImportantTestButton->overlap(handX, handY)) {
					m_state = LESSON_NAME::WORD_TEST_IMPORTANT;
					m_wordTestStudy->init(true);
				}
				else if (m_diaryButton->overlap(handX, handY)) {
					m_state = LESSON_NAME::DIARY;
				}
				else if (m_radioReviewButton->overlap(handX, handY)) {
					m_state = LESSON_NAME::RADIO_REVIEW;
				}
				else if (m_grammarStudyButton->overlap(handX, handY)) {
					m_state = LESSON_NAME::GRAMMAR_STUDY;
				}
				else if (m_breakTimeButton->overlap(handX, handY)) {
					m_state = LESSON_NAME::BREAK_TIME;
				}
				else if (m_freeStudyButton->overlap(handX, handY)) {
					m_state = LESSON_NAME::FREE_STUDY;
				}
				else if (m_longTextStudyButton->overlap(handX, handY)) {
					m_state = LESSON_NAME::LONG_TEXT_STUDY;
				}
				else if (m_morningReviewButton->overlap(handX, handY)) {
					m_state = LESSON_NAME::MORNING_REVIEW;
				}
				else if (m_radioButton->overlap(handX, handY)) {
					m_state = LESSON_NAME::RADIO;
				}
				else if (m_speakingStudyButton->overlap(handX, handY)) {
					m_state = LESSON_NAME::SPEAKING_STUDY;
				}
				else if (m_eveningReviewButton->overlap(handX, handY)) {
					m_state = LESSON_NAME::EVENING_REVIEW;
				}
			}
			// レッスン開始
			if (m_state != LESSON_NAME::SELECT_LESSON) {
				m_stopWatch->init();
			}
			break;
		case WORD_TEST:				// 単語テスト
			m_wordTestStudy->play(handX, handY, false);
			break;
		case WORD_TEST_IMPORTANT:	// 重要語テスト
			m_wordTestStudy->play(handX, handY, true);
			break;
		case DIARY:					// 日記
			break;
		case RADIO_REVIEW:			// ラジオ英会話復習
			break;
		case GRAMMAR_STUDY:			// 文法
			break;
		case BREAK_TIME:			// 休憩
			break;
		case FREE_STUDY:			// 自習
			break;
		case LONG_TEXT_STUDY:		// 長文問題
			break;
		case MORNING_REVIEW:		// 朝の振り返り
			break;
		case RADIO:					// ラジオ英会話
			break;
		case SPEAKING_STUDY:		// 音読練習
			break;
		case EVENING_REVIEW:		// 夜の振り返り
			break;
	}
	if (m_state != LESSON_NAME::SELECT_LESSON) {
		if (leftClick() == 1 && m_finishButton->overlap(handX, handY)) {
			m_state = LESSON_NAME::SELECT_LESSON;
			m_wordTestStudy->init(false);
		}
	}
	return false;
}

void Lesson::draw(int handX, int handY) const {
	if (m_state != LESSON_NAME::SELECT_LESSON) {
		m_finishButton->draw(handX, handY);
	}
	string lessonName = "";
	switch (m_state) {
	case SELECT_LESSON:			// レッスン選択画面
		m_wordTestButton->draw(handX, handY);
		m_onlyImportantTestButton->draw(handX, handY);
		m_diaryButton->draw(handX, handY);
		m_radioReviewButton->draw(handX, handY);
		m_grammarStudyButton->draw(handX, handY);
		m_breakTimeButton->draw(handX, handY);
		m_freeStudyButton->draw(handX, handY);
		m_longTextStudyButton->draw(handX, handY);
		m_morningReviewButton->draw(handX, handY);
		m_radioButton->draw(handX, handY);
		m_speakingStudyButton->draw(handX, handY);
		m_eveningReviewButton->draw(handX, handY);
		break;
	case WORD_TEST:				// 単語テスト
	case WORD_TEST_IMPORTANT:	// 重要語テスト
		m_wordTestStudy->draw(handX, handY);
		break;
	case DIARY:					// 日記
		lessonName = "日記勉強の時間";
		break;
	case RADIO_REVIEW:			// ラジオ英会話復習
		lessonName = "ラジオ英会話復習の時間";
		break;
	case GRAMMAR_STUDY:			// 文法
		lessonName = "文法勉強の時間";
		break;
	case BREAK_TIME:			// 休憩
		lessonName = "休憩時間";
		break;
	case FREE_STUDY:			// 自習
		lessonName = "自習時間";
		break;
	case LONG_TEXT_STUDY:		// 長文問題
		lessonName = "長文問題で勉強するの時間";
		break;
	case MORNING_REVIEW:		// 朝の振り返り
		lessonName = "朝の振り返り";
		break;
	case RADIO:					// ラジオ英会話
		lessonName = "ラジオ英会話の時間";
		break;
	case SPEAKING_STUDY:		// 音読練習
		lessonName = "音読練習強の時間";
		break;
	case EVENING_REVIEW:		// 夜の振り返り
		lessonName = "夜の振り返りの時間";
		break;
	}
	if (m_state != LESSON_NAME::SELECT_LESSON && m_state != LESSON_NAME::WORD_TEST && m_state != LESSON_NAME::WORD_TEST_IMPORTANT) {
		DrawStringToHandle(100, 300, lessonName.c_str(), WHITE, m_font);
		DrawStringToHandle(550, 550, getTimeString(m_stopWatch->getCnt()).c_str(), WHITE, m_font);
	}
}