#ifndef STUDY_H_INCLUDED
#define STUDY_H_INCLUDED


class Button;
class WordTestStudy;
class WordAddStudy;


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

public:
	Study(int font);
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

public:
	WordTestStudy();
	~WordTestStudy();

	bool play();
	void draw();
};


/*
* �P��ǉ�
*/
class WordAddStudy {
private:

public:
	WordAddStudy();
	~WordAddStudy();

	bool play();
	void draw();
};


#endif