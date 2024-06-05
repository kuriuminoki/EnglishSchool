#ifndef LESSON_H_INCLUDED
#define LESSON_H_INCLUDED

class Button;
class Stats;
class StopWatch;
class Teacher;
class WordTestStudy;
class SpeakingPractice;

enum LESSON_NAME {
	SELECT_LESSON,			// ���b�X���I�����
	WORD_TEST,				// �P��e�X�g
	WORD_TEST_IMPORTANT,	// �d�v��e�X�g
	DIARY,					// ���L
	RADIO_REVIEW,			// ���W�I�p��b���K
	GRAMMAR_STUDY,			// ���@
	BREAK_TIME,				// �x�e
	FREE_STUDY,				// ���K
	LONG_TEXT_STUDY,		// �������
	MORNING_REVIEW,			// ���̐U��Ԃ�
	RADIO,					// ���W�I�p��b
	SPEAKING_STUDY,			// ���Ǘ��K
	EVENING_REVIEW			// ��̐U��Ԃ�
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

	// �I������true��Ԃ�
	bool play(int handX, int handY);

	void draw(int handX, int handY) const;
};

#endif