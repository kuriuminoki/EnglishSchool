#include "Button.h"
#include "Control.h"
#include "Define.h"
#include "Game.h"
#include "Lesson.h"
#include "Setting.h"
#include "Study.h"
#include "Teacher.h"
#include "Timer.h"

#include <ctime>
#include <sstream>

using namespace std;


string getDateStr() {
	time_t t = std::time(nullptr);
	struct tm now;
	localtime_s(&now, &t);
	ostringstream oss;
	oss << now.tm_year + 1900 << "-" << now.tm_mon + 1 << "-" << now.tm_mday + 1;
	return oss.str();
}


Game::Game() {
	// セーブデータ
	m_stats = new Stats("data/stats/savedata.dat");
	m_dateStr = getDateStr();
	m_dateStr = "data/stats/" + m_dateStr;
	m_dateStr += ".dat";
	m_dailyStats = new Stats(m_dateStr.c_str());

	// 教師
	m_teacher = new Teacher("トモチ");
	m_teacher->setRandomText();

	m_handX = 0;
	m_handY = 0;
	m_state = GAME_MODE::SELECT_MODE;
	m_font = CreateFontToHandle(NULL, 40, 3);
	m_selectMode = new SelectMode(m_font);
	m_lesson = new Lesson(m_font, m_teacher, m_stats, m_dailyStats);
	m_study = new Study(m_font, m_teacher);
	m_setting = new Setting();
	m_backButton = new Button("タイトルへ戻る", 50, 50, 300, 100, GRAY, WHITE, m_font, BLACK);
	m_stopWatch = new StopWatch();
}

Game::~Game() {
	DeleteFontToHandle(m_font);
	delete m_selectMode;
	delete m_lesson;
	delete m_study;
	delete m_setting;
	delete m_teacher;
	m_stats->setCnt(m_stopWatch->getCnt() + m_stats->getCnt());
	m_dailyStats->setCnt(m_stopWatch->getCnt() + m_dailyStats->getCnt());
	delete m_stopWatch;
	delete m_stats;
	delete m_dailyStats;
}

void Game::play() {

	m_stopWatch->count();

	GetMousePoint(&m_handX, &m_handY);

	m_teacher->play();

	switch (m_state) {
	case SELECT_MODE:
		m_state = m_selectMode->play(m_handX, m_handY);
		break;
	case LESSON_MODE:
		if (m_lesson->play(m_handX, m_handY)) {
			m_state = GAME_MODE::SELECT_MODE;
		}
		break;
	case STUDY_MODE:
		if (m_study->play(m_handX, m_handY)) {
			m_state = GAME_MODE::SELECT_MODE;
		}
		break;
	case SETTING_MODE:
		if (m_setting->play()) {
			m_state = GAME_MODE::SELECT_MODE;
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
	else {
		DrawStringToHandle(100, 850, ("今日の起動時間：" + getTimeString(m_stopWatch->getCnt() + m_dailyStats->getCnt())).c_str(), WHITE, m_font);
		DrawStringToHandle(100, 900, ("総起動時間：" + getTimeString(m_stopWatch->getCnt() + m_stats->getCnt())).c_str(), WHITE, m_font);
	}
	DrawStringToHandle(50, 1000, getTimeString(m_stopWatch->getCnt()).c_str(), WHITE, m_font);
}


/*
* 勉強の記録
*/
Stats::Stats(const char* path) {
	m_path = path;
	read();
}

Stats::~Stats() {
	write();
}

bool Stats::read() {
	FILE* intFp = nullptr;
	if (fopen_s(&intFp, m_path, "rb") != 0) {
		return false;
	}
	// Read
	fread(&m_cnt, sizeof(m_cnt), 1, intFp);
	fread(&m_wordTestCnt, sizeof(m_wordTestCnt), 1, intFp);
	fread(&m_onlyImportantTestCnt, sizeof(m_onlyImportantTestCnt), 1, intFp);
	fread(&m_diaryCnt, sizeof(m_diaryCnt), 1, intFp);
	fread(&m_radioReviewCnt, sizeof(m_radioReviewCnt), 1, intFp);
	fread(&m_grammarStudyCnt, sizeof(m_grammarStudyCnt), 1, intFp);
	fread(&m_breakTimeCnt, sizeof(m_breakTimeCnt), 1, intFp);
	fread(&m_freeStudyCnt, sizeof(m_freeStudyCnt), 1, intFp);
	fread(&m_longTextStudyCnt, sizeof(m_longTextStudyCnt), 1, intFp);
	fread(&m_morningReviewCnt, sizeof(m_morningReviewCnt), 1, intFp);
	fread(&m_radioCnt, sizeof(m_radioCnt), 1, intFp);
	fread(&m_speakingStudyCnt, sizeof(m_speakingStudyCnt), 1, intFp);
	fread(&m_eveningReviewCnt, sizeof(m_eveningReviewCnt), 1, intFp);
	fclose(intFp);
	return true;
}

bool Stats::write() {
	FILE* intFp = nullptr;
	if (fopen_s(&intFp, m_path, "wb") != 0) {
		return false;
	}
	fwrite(&m_cnt, sizeof(m_cnt), 1, intFp);
	fwrite(&m_wordTestCnt, sizeof(m_wordTestCnt), 1, intFp);
	fwrite(&m_onlyImportantTestCnt, sizeof(m_onlyImportantTestCnt), 1, intFp);
	fwrite(&m_diaryCnt, sizeof(m_diaryCnt), 1, intFp);
	fwrite(&m_radioReviewCnt, sizeof(m_radioReviewCnt), 1, intFp);
	fwrite(&m_grammarStudyCnt, sizeof(m_grammarStudyCnt), 1, intFp);
	fwrite(&m_breakTimeCnt, sizeof(m_breakTimeCnt), 1, intFp);
	fwrite(&m_freeStudyCnt, sizeof(m_freeStudyCnt), 1, intFp);
	fwrite(&m_longTextStudyCnt, sizeof(m_longTextStudyCnt), 1, intFp);
	fwrite(&m_morningReviewCnt, sizeof(m_morningReviewCnt), 1, intFp);
	fwrite(&m_radioCnt, sizeof(m_radioCnt), 1, intFp);
	fwrite(&m_speakingStudyCnt, sizeof(m_speakingStudyCnt), 1, intFp);
	fwrite(&m_eveningReviewCnt, sizeof(m_eveningReviewCnt), 1, intFp);
	fclose(intFp);
	return true;
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