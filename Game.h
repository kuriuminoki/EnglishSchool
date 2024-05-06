#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <string>

class Button;
class Lesson;
class Study;
class SelectMode;
class Setting;
class Teacher;
class Stats;
class StopWatch;


enum GAME_MODE {
	SELECT_MODE,	// モード選択画面
	LESSON_MODE,	// 授業モード
	STUDY_MODE,		// 自習モード
	SETTING_MODE	// セッティングモード
};


class Game {
private:

	int m_handX, m_handY;

	// 今プレイ中のモード
	GAME_MODE m_state;

	// 各モード
	SelectMode* m_selectMode;
	Lesson* m_lesson;
	Study* m_study;
	Setting* m_setting;

	int m_font;

	std::string m_dateStr;

	// モード選択画面へ戻るボタン
	Button* m_backButton;

	// 教師
	Teacher* m_teacher;

	StopWatch* m_stopWatch;

	Stats* m_stats;
	Stats* m_dailyStats;

public:

	Game();

	~Game();

	// ゲッタ
	inline const int getHandX() const { return m_handX; }
	inline const int getHandY() const { return m_handY; }
	inline const GAME_MODE getState() const { return m_state; }
	inline const SelectMode* getSelectMode() const { return m_selectMode; }
	inline const Lesson* getLesson() const { return m_lesson; }
	inline const Study* getStudy() const { return m_study; }
	inline const Setting* getSetting() const { return m_setting; }
	inline const Teacher* getTeacher() const { return m_teacher; }

	void play();

	void draw() const;

};


// 勉強の記録
class Stats {
private:

	const char* m_path;

	// 総プレイ時間
	long long int m_cnt;

	// 各レッスンの時間
	long long int m_wordTestCnt;
	long long int m_onlyImportantTestCnt;
	long long int m_diaryCnt;
	long long int m_radioReviewCnt;
	long long int m_grammarStudyCnt;
	long long int m_breakTimeCnt;
	long long int m_freeStudyCnt;
	long long int m_longTextStudyCnt;
	long long int m_morningReviewCnt;
	long long int m_radioCnt;
	long long int m_speakingStudyCnt;
	long long int m_eveningReviewCnt;

public:

	Stats(const char* path);
	~Stats();

	bool read();
	bool write();

	inline long long int getCnt() const { return m_cnt; }
	inline void setCnt(long long int cnt) { m_cnt = cnt; }

	inline long long int getWordTestCnt() const { return m_wordTestCnt; }
	inline void setWordTestCnt(long long int cnt) { m_wordTestCnt = cnt; }
	inline long long int getOnlyImportantTestCnt() const { return m_onlyImportantTestCnt; }
	inline void setOnlyImportantTestCnt(long long int cnt) { m_onlyImportantTestCnt = cnt; }
	inline long long int getDiaryCnt() const { return m_diaryCnt; }
	inline void setDiaryCnt(long long int cnt) { m_diaryCnt = cnt; }
	inline long long int getRadioReviewCnt() const { return m_radioReviewCnt; }
	inline void setRadioReviewCnt(long long int cnt) { m_radioReviewCnt = cnt; }
	inline long long int getGrammarStudyCnt() const { return m_grammarStudyCnt; }
	inline void setGrammarStudyCnt(long long int cnt) { m_grammarStudyCnt = cnt; }
	inline long long int getBreakTimeCnt() const { return m_breakTimeCnt; }
	inline void setBreakTimeCnt(long long int cnt) { m_breakTimeCnt = cnt; }
	inline long long int getFreeStudyCnt() const { return m_freeStudyCnt; }
	inline void setFreeStudyCnt(long long int cnt) { m_freeStudyCnt = cnt; }
	inline long long int getLongTextStudyCnt() const { return m_longTextStudyCnt; }
	inline void setLongTextStudyCnt(long long int cnt) { m_longTextStudyCnt = cnt; }
	inline long long int getMorningReviewCnt() const { return m_morningReviewCnt; }
	inline void setMorningReviewCnt(long long int cnt) { m_morningReviewCnt = cnt; }
	inline long long int getRadioCnt() const { return m_radioCnt; }
	inline void setRadioCnt(long long int cnt) { m_radioCnt = cnt; }
	inline long long int getSpeakingStudyCnt() const { return m_speakingStudyCnt; }
	inline void setSpeakingStudyCnt(long long int cnt) { m_speakingStudyCnt = cnt; }
	inline long long int getEveningReviewCnt() const { return m_eveningReviewCnt; }
	inline void setEveningReviewCnt(long long int cnt) { m_eveningReviewCnt = cnt; }
};


/*
* モード選択画面
*/ 
class SelectMode {
private:

	int m_font;
	Button* m_lessonButton;
	Button* m_studyButton;
	Button* m_settingButton;

public:
	SelectMode(int font);
	~SelectMode();
	GAME_MODE play(int handX, int handY);
	void draw(int handX, int handY) const;
};

#endif