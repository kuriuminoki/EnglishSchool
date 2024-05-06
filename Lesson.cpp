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

	m_finishButton = new Button("I—¹", 1650, 50, 200, 100, GRAY, WHITE, m_font, BLACK);
	m_wordTestButton = new Button("‘S’PŒêƒeƒXƒg", 100, 300, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_onlyImportantTestButton = new Button("d—vŒê‚Ì‚ÝƒeƒXƒg", 500, 300, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_diaryButton = new Button("“ú‹L", 900, 300, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_radioReviewButton = new Button("ƒ‰ƒWƒI•œK", 100, 450, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_grammarStudyButton = new Button("•¶–@•×‹­", 500, 450, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_breakTimeButton = new Button("‹xŒe", 900, 450, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_freeStudyButton = new Button("Ž©K", 100, 600, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_longTextStudyButton = new Button("’·•¶–â‘è", 500, 600, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_morningReviewButton = new Button("’©‚ÌU‚è•Ô‚è", 900, 600, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_radioButton = new Button("ƒ‰ƒWƒI‰p‰ï˜b", 100, 750, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_speakingStudyButton = new Button("‰¹“Ç—ûK", 500, 750, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_eveningReviewButton = new Button("–é‚ÌU‚è•Ô‚è", 900, 750, 350, 100, LIGHT_BLUE, BLUE, m_font, BLACK);

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
		case SELECT_LESSON:			// ƒŒƒbƒXƒ“‘I‘ð‰æ–Ê
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
			// ƒŒƒbƒXƒ“ŠJŽn
			if (m_state != LESSON_NAME::SELECT_LESSON) {
				m_stopWatch->init();
			}
			break;
		case WORD_TEST:				// ’PŒêƒeƒXƒg
			m_wordTestStudy->play(handX, handY, false);
			break;
		case WORD_TEST_IMPORTANT:	// d—vŒêƒeƒXƒg
			m_wordTestStudy->play(handX, handY, true);
			break;
		case DIARY:					// “ú‹L
			break;
		case RADIO_REVIEW:			// ƒ‰ƒWƒI‰p‰ï˜b•œK
			break;
		case GRAMMAR_STUDY:			// •¶–@
			break;
		case BREAK_TIME:			// ‹xŒe
			break;
		case FREE_STUDY:			// Ž©K
			break;
		case LONG_TEXT_STUDY:		// ’·•¶–â‘è
			break;
		case MORNING_REVIEW:		// ’©‚ÌU‚è•Ô‚è
			break;
		case RADIO:					// ƒ‰ƒWƒI‰p‰ï˜b
			break;
		case SPEAKING_STUDY:		// ‰¹“Ç—ûK
			break;
		case EVENING_REVIEW:		// –é‚ÌU‚è•Ô‚è
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
	case SELECT_LESSON:			// ƒŒƒbƒXƒ“‘I‘ð‰æ–Ê
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
	case WORD_TEST:				// ’PŒêƒeƒXƒg
	case WORD_TEST_IMPORTANT:	// d—vŒêƒeƒXƒg
		m_wordTestStudy->draw(handX, handY);
		break;
	case DIARY:					// “ú‹L
		lessonName = "“ú‹L•×‹­‚ÌŽžŠÔ";
		break;
	case RADIO_REVIEW:			// ƒ‰ƒWƒI‰p‰ï˜b•œK
		lessonName = "ƒ‰ƒWƒI‰p‰ï˜b•œK‚ÌŽžŠÔ";
		break;
	case GRAMMAR_STUDY:			// •¶–@
		lessonName = "•¶–@•×‹­‚ÌŽžŠÔ";
		break;
	case BREAK_TIME:			// ‹xŒe
		lessonName = "‹xŒeŽžŠÔ";
		break;
	case FREE_STUDY:			// Ž©K
		lessonName = "Ž©KŽžŠÔ";
		break;
	case LONG_TEXT_STUDY:		// ’·•¶–â‘è
		lessonName = "’·•¶–â‘è‚Å•×‹­‚·‚é‚ÌŽžŠÔ";
		break;
	case MORNING_REVIEW:		// ’©‚ÌU‚è•Ô‚è
		lessonName = "’©‚ÌU‚è•Ô‚è";
		break;
	case RADIO:					// ƒ‰ƒWƒI‰p‰ï˜b
		lessonName = "ƒ‰ƒWƒI‰p‰ï˜b‚ÌŽžŠÔ";
		break;
	case SPEAKING_STUDY:		// ‰¹“Ç—ûK
		lessonName = "‰¹“Ç—ûK‹­‚ÌŽžŠÔ";
		break;
	case EVENING_REVIEW:		// –é‚ÌU‚è•Ô‚è
		lessonName = "–é‚ÌU‚è•Ô‚è‚ÌŽžŠÔ";
		break;
	}
	if (m_state != LESSON_NAME::SELECT_LESSON && m_state != LESSON_NAME::WORD_TEST && m_state != LESSON_NAME::WORD_TEST_IMPORTANT) {
		DrawStringToHandle(100, 300, lessonName.c_str(), WHITE, m_font);
		DrawStringToHandle(550, 550, getTimeString(m_stopWatch->getCnt()).c_str(), WHITE, m_font);
	}
}