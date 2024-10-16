#ifndef STUDY_H_INCLUDED
#define STUDY_H_INCLUDED


class Button;
class Vocabulary;
class SpeakingSet;
class WordTestStudy;
class SpeakingPractice;
class Teacher;
class StopWatch;


/*
* �}�E�X�z�C�[���Ńt�H���g�T�C�Y�𒲐�����N���X
*/
class DynamicFont {
private:

	const int MAX_SIZE = 100;
	const int MIN_SIZE = 1;

	const int MAX_THICK = 100;
	const int MIN_THICK = 1;

	// �t�H���g�T�C�Y
	int m_size;

	// �t�H���g�̑���
	int m_thick;

	// �t�H���g
	int m_font;

public:

	DynamicFont(int size, int thick);

	~DynamicFont();

	void changeFont(int mouseWheel);

	int getFont() const { return m_font; }

private:
	void createFont(int size, int thick);

};


class Study {
private:

	enum STUDY_MODE {
		SELECT_MODE,			// �I�����
		WORD_TEST,				// �P��e�X�g
		WORD_TEST_IMPORTANT,	// �d�v��̂݃e�X�g
		SPEAKING_PRACTICE,				// ���Ǘ��K
		SPEAKING_PRACTICE_IMPORTANT		// �d�v���̂ݗ��K
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

	// �I������true��Ԃ�
	bool play(int handX, int handY, int mouseWheel);

	void draw(int handX, int handY) const;
};


/*
* �P��e�X�g
*/
class WordTestStudy {
private:

	Vocabulary* m_vocabulary;

	int m_font;
	int m_miniFont;
	DynamicFont* m_dynamicFont;

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

	bool play(int handX, int handY, int mouseWheel, bool onlyImportant);
	void init(bool onlyImportant);
	void end();
	void draw(int handX, int handY) const;
};


/*
* ���Ǘ��K
*/
class SpeakingPractice {
private:

	SpeakingSet* m_speakingSets;

	int m_font;
	int m_sentenceFont;
	DynamicFont* m_dynamicFont;

	enum HIDE_STATE {
		NO_HIDE,
		EN_HIDE,
		EN_HINT_HIDE
	};

	// 0:�S�\�� 1:�p���B�� 2:�p���{�q���g�B��
	HIDE_STATE m_hideState;

	Button* m_repeatButton;
	Button* m_importantButton;
	Button* m_answerButton;
	Button* m_nextButton;

	Teacher* m_teacher_p;

	StopWatch* m_stopWatch;

public:
	SpeakingPractice(Teacher* teacher_p);
	~SpeakingPractice();

	bool play(int handX, int handY, int mouseWheel, bool onlyImportant);
	void init(bool onlyImportant);
	void end();
	void draw(int handX, int handY) const;
};

#endif