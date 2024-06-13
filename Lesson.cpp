#include "Lesson.h"
#include "Button.h"
#include "Control.h"
#include "Define.h"
#include "Game.h"
#include "Study.h"
#include "Teacher.h"
#include "Timer.h"

#include <string>

using namespace std;


Lesson::Lesson(int font, Teacher* teacher_p, Stats* stats_p, Stats* dailyStats_p) {

	m_font = font;
	m_teacher_p = teacher_p;
	m_stats_p = stats_p;
	m_dailyStats_p = dailyStats_p;

	m_state = LESSON_NAME::SELECT_LESSON;

	m_stopWatch = new StopWatch();

	m_wordTestStudy = new WordTestStudy(m_teacher_p);
	m_speakingPractice = new SpeakingPractice(m_teacher_p);

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
	delete m_speakingPractice;
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
					m_wordTestStudy->init(false);
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
					m_speakingPractice->init(false);
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
			m_stats_p->setWordTestCnt(m_stats_p->getWordTestCnt() + 1);
			m_dailyStats_p->setWordTestCnt(m_dailyStats_p->getWordTestCnt() + 1);
			break;
		case WORD_TEST_IMPORTANT:	// 重要語テスト
			m_wordTestStudy->play(handX, handY, true);
			m_stats_p->setOnlyImportantTestCnt(m_stats_p->getOnlyImportantTestCnt() + 1);
			m_dailyStats_p->setOnlyImportantTestCnt(m_dailyStats_p->getOnlyImportantTestCnt() + 1);
			break;
		case DIARY:					// 日記
			m_stats_p->setDiaryCnt(m_stats_p->getDiaryCnt() + 1);
			m_dailyStats_p->setDiaryCnt(m_dailyStats_p->getDiaryCnt() + 1);
			break;
		case RADIO_REVIEW:			// ラジオ英会話復習
			m_stats_p->setRadioReviewCnt(m_stats_p->getRadioReviewCnt() + 1);
			m_dailyStats_p->setRadioReviewCnt(m_dailyStats_p->getRadioReviewCnt() + 1);
			break;
		case GRAMMAR_STUDY:			// 文法
			m_stats_p->setGrammarStudyCnt(m_stats_p->getGrammarStudyCnt() + 1);
			m_dailyStats_p->setGrammarStudyCnt(m_dailyStats_p->getGrammarStudyCnt() + 1);
			break;
		case BREAK_TIME:			// 休憩
			m_stats_p->setBreakTimeCnt(m_stats_p->getBreakTimeCnt() + 1);
			m_dailyStats_p->setBreakTimeCnt(m_dailyStats_p->getBreakTimeCnt() + 1);
			break;
		case FREE_STUDY:			// 自習
			m_stats_p->setFreeStudyCnt(m_stats_p->getFreeStudyCnt() + 1);
			m_dailyStats_p->setFreeStudyCnt(m_dailyStats_p->getFreeStudyCnt() + 1);
			break;
		case LONG_TEXT_STUDY:		// 長文問題
			m_stats_p->setLongTextStudyCnt(m_stats_p->getLongTextStudyCnt() + 1);
			m_dailyStats_p->setLongTextStudyCnt(m_dailyStats_p->getLongTextStudyCnt() + 1);
			break;
		case MORNING_REVIEW:		// 朝の振り返り
			m_stats_p->setMorningReviewCnt(m_stats_p->getMorningReviewCnt() + 1);
			m_dailyStats_p->setMorningReviewCnt(m_dailyStats_p->getMorningReviewCnt() + 1);
			break;
		case RADIO:					// ラジオ英会話
			m_stats_p->setRadioCnt(m_stats_p->getRadioCnt() + 1);
			m_dailyStats_p->setRadioCnt(m_dailyStats_p->getRadioCnt() + 1);
			break;
		case SPEAKING_STUDY:		// 音読練習
			m_speakingPractice->play(handX, handY, false);
			m_stats_p->setSpeakingStudyCnt(m_stats_p->getSpeakingStudyCnt() + 1);
			m_dailyStats_p->setSpeakingStudyCnt(m_dailyStats_p->getSpeakingStudyCnt() + 1);
			break;
		case EVENING_REVIEW:		// 夜の振り返り
			m_stats_p->setEveningReviewCnt(m_stats_p->getEveningReviewCnt() + 1);
			m_dailyStats_p->setEveningReviewCnt(m_dailyStats_p->getEveningReviewCnt() + 1);
			break;
	}
	if (m_state != LESSON_NAME::SELECT_LESSON) {
		if (leftClick() == 1 && m_finishButton->overlap(handX, handY)) {
			m_state = LESSON_NAME::SELECT_LESSON;
			m_wordTestStudy->init(false);
			m_speakingPractice->init(false);
		}
		m_teacher_p->addExp(1);
	}
	return false;
}

void Lesson::draw(int handX, int handY) const {
	if (m_state != LESSON_NAME::SELECT_LESSON) {
		m_finishButton->draw(handX, handY);
	}
	string lessonName = "";
	string dateName = "今日：";
	const Stats* stats = m_dailyStats_p;
	if (rightClick() > 1) {
		dateName = "累計：";
		stats = m_stats_p;
	}
	switch (m_state) {
	case SELECT_LESSON:			// レッスン選択画面
		DrawFormatString(100, 280, WHITE, (dateName + getTimeString(stats->getWordTestCnt())).c_str());
		DrawFormatString(500, 280, WHITE, (dateName + getTimeString(stats->getOnlyImportantTestCnt())).c_str());
		DrawFormatString(900, 280, WHITE, (dateName + getTimeString(stats->getDiaryCnt())).c_str());
		DrawFormatString(100, 430, WHITE, (dateName + getTimeString(stats->getRadioReviewCnt())).c_str());
		DrawFormatString(500, 430, WHITE, (dateName + getTimeString(stats->getGrammarStudyCnt())).c_str());
		DrawFormatString(900, 430, WHITE, (dateName + getTimeString(stats->getBreakTimeCnt())).c_str());
		DrawFormatString(100, 580, WHITE, (dateName + getTimeString(stats->getFreeStudyCnt())).c_str());
		DrawFormatString(500, 580, WHITE, (dateName + getTimeString(stats->getLongTextStudyCnt())).c_str());
		DrawFormatString(900, 580, WHITE, (dateName + getTimeString(stats->getMorningReviewCnt())).c_str());
		DrawFormatString(100, 730, WHITE, (dateName + getTimeString(stats->getRadioCnt())).c_str());
		DrawFormatString(500, 730, WHITE, (dateName + getTimeString(stats->getSpeakingStudyCnt())).c_str());
		DrawFormatString(900, 730, WHITE, (dateName + getTimeString(stats->getEveningReviewCnt())).c_str());
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
		lessonName = "全単語テストの時間 15m";
		m_wordTestStudy->draw(handX, handY);
		break;
	case WORD_TEST_IMPORTANT:	// 重要語テスト
		lessonName = "重要語テストの時間 15m";
		m_wordTestStudy->draw(handX, handY);
		break;
	case DIARY:					// 日記
		lessonName = "日記勉強の時間 10m";
		break;
	case RADIO_REVIEW:			// ラジオ英会話復習
		lessonName = "ラジオ英会話復習の時間 5m";
		break;
	case GRAMMAR_STUDY:			// 文法
		lessonName = "文法勉強の時間 10m";
		break;
	case BREAK_TIME:			// 休憩
		lessonName = "休憩時間 10m";
		break;
	case FREE_STUDY:			// 自習
		lessonName = "自習時間 30m";
		break;
	case LONG_TEXT_STUDY:		// 長文問題
		lessonName = "長文問題で勉強する時間 15m";
		break;
	case MORNING_REVIEW:		// 朝の振り返り
		lessonName = "朝の振り返り 10m";
		break;
	case RADIO:					// ラジオ英会話
		lessonName = "ラジオ英会話の時間 20m";
		break;
	case SPEAKING_STUDY:		// 音読練習
		m_speakingPractice->draw(handX, handY);
		lessonName = "音読練習強の時間 20m";
		break;
	case EVENING_REVIEW:		// 夜の振り返り
		lessonName = "夜の振り返りの時間 20m";
		break;
	}
	DrawStringToHandle(100, 250, lessonName.c_str(), WHITE, m_font);
	if (m_state != LESSON_NAME::SELECT_LESSON
		&& m_state != LESSON_NAME::WORD_TEST && m_state != LESSON_NAME::WORD_TEST_IMPORTANT
		&& m_state != LESSON_NAME::SPEAKING_STUDY) {
		DrawStringToHandle(550, 550, getTimeString(m_stopWatch->getCnt()).c_str(), WHITE, m_font);
	}
}