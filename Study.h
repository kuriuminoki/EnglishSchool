#ifndef STUDY_H_INCLUDED
#define STUDY_H_INCLUDED


class Button;
class Vocabulary;
class WordTestStudy;
class WordAddStudy;
class Teacher;


class Study {
private:

	enum STUDY_MODE {
		SELECT_MODE,	// �I�����
		WORD_TEST,		// �P��e�X�g
		WORD_ADD		// �P��ǉ�
	};

	STUDY_MODE m_state;

	WordTestStudy* m_wordTestStudy;
	WordAddStudy* m_wordAddStudy;

	Button* m_finishButton;
	Button* m_wordTestButton;
	Button* m_wordAddButton;

	int m_font;

	Teacher* m_teacher_p;

public:
	Study(int font, Teacher* teacher_p);
	~Study();

	// �I������true��Ԃ�
	bool play(int handX, int handY);

	void draw(int handX, int handY) const;
};


/*
* �P��e�X�g
*/
class WordTestStudy {
private:

	Vocabulary* m_vocabulary;

	int m_font;

	Button* m_answerButton;
	Button* m_importantButton;
	Button* m_nextButton;
	Button* m_removeButton;

	Teacher* m_teacher_p;

public:
	WordTestStudy(Teacher* teacher_p);
	~WordTestStudy();

	bool play(int handX, int handY);
	void init();
	void draw(int handX, int handY) const;
};


/*
* �P��ǉ�
*/
class WordAddStudy {
private:

	Vocabulary* m_vocabulary;

public:
	WordAddStudy();
	~WordAddStudy();

	bool play();
	void draw();
};


#endif