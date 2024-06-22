#ifndef STUDY_H_INCLUDED
#define STUDY_H_INCLUDED


class Button;
class Vocabulary;
class SpeakingSet;
class WordTestStudy;
class SpeakingPractice;
class Teacher;
class StopWatch;


class Study {
private:

	enum STUDY_MODE {
		SELECT_MODE,			// 選択画面
		WORD_TEST,				// 単語テスト
		WORD_TEST_IMPORTANT,	// 重要語のみテスト
		SPEAKING_PRACTICE,				// 音読練習
		SPEAKING_PRACTICE_IMPORTANT		// 重要文のみ練習
	};

	STUDY_MODE m_state;

	WordTestStudy* m_wordTestStudy;

	SpeakingPractice* m_speakingPractiace;

	Button* m_finishButton;
	Button* m_wordTestButton;
	Button* m_onlyImportantTestButton;
	Button* m_speakingPracticeButton;
	Button* m_onlyImportantspeakingPracticeButton;

	int m_font;

	Teacher* m_teacher_p;

public:
	Study(int font, Teacher* teacher_p);
	~Study();

	// 終了時にtrueを返す
	bool play(int handX, int handY);

	void draw(int handX, int handY) const;
};


/*
* 単語テスト
*/
class WordTestStudy {
private:

	Vocabulary* m_vocabulary;

	int m_font;
	int m_miniFont;

	Button* m_answerButton;
	Button* m_importantButton;
	Button* m_nextButton;
	Button* m_prevButton;
	Button* m_removeButton;

	Teacher* m_teacher_p;

	StopWatch* m_stopWatch;

public:
	WordTestStudy(Teacher* teacher_p);
	~WordTestStudy();

	bool play(int handX, int handY, bool onlyImportant);
	void init(bool onlyImportant);
	void end();
	void draw(int handX, int handY) const;
};


/*
* 音読練習
*/
class SpeakingPractice {
private:

	SpeakingSet* m_speakingSets;

	int m_font;
	int m_sentenceFont;

	Button* m_repeatButton;
	Button* m_importantButton;
	Button* m_nextButton;

	Teacher* m_teacher_p;

	StopWatch* m_stopWatch;

public:
	SpeakingPractice(Teacher* teacher_p);
	~SpeakingPractice();

	bool play(int handX, int handY, bool onlyImportant);
	void init(bool onlyImportant);
	void end();
	void draw(int handX, int handY) const;
};

#endif