#ifndef LESSON_H_INCLUDED
#define LESSON_H_INCLUDED

class Button;
class Stats;
class StopWatch;
class Teacher;
class WordTestStudy;
class SpeakingPractice;

enum LESSON_NAME {
	SELECT_LESSON,			// レッスン選択画面
	WORD_TEST,				// 単語テスト
	WORD_TEST_IMPORTANT,	// 重要語テスト
	DIARY,					// 日記
	RADIO_REVIEW,			// ラジオ英会話復習
	GRAMMAR_STUDY,			// 文法
	BREAK_TIME,				// 休憩
	FREE_STUDY,				// 自習
	LONG_TEXT_STUDY,		// 長文問題
	MORNING_REVIEW,			// 朝の振り返り
	RADIO,					// ラジオ英会話
	SPEAKING_STUDY,			// 音読練習
	EVENING_REVIEW			// 夜の振り返り
};

class Lesson {
private:

	LESSON_NAME m_state;

	StopWatch* m_stopWatch;

	WordTestStudy* m_wordTestStudy;
	SpeakingPractice* m_speakingPractice;

	Button* m_finishButton;
	Button* m_wordTestButton;
	Button* m_onlyImportantTestButton;
	Button* m_diaryButton;
	Button* m_radioReviewButton;
	Button* m_grammarStudyButton;
	Button* m_breakTimeButton;
	Button* m_freeStudyButton;
	Button* m_longTextStudyButton;
	Button* m_morningReviewButton;
	Button* m_radioButton;
	Button* m_speakingStudyButton;
	Button* m_eveningReviewButton;

	int m_font;

	Teacher* m_teacher_p;

	Stats* m_stats_p;
	Stats* m_dailyStats_p;

public:
	Lesson(int font, Teacher* teacher_p, Stats* stats_p, Stats* dailyStats_p);
	~Lesson();

	// 終了時にtrueを返す
	bool play(int handX, int handY);

	void draw(int handX, int handY) const;
};

#endif