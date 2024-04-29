#ifndef STUDY_H_INCLUDED
#define STUDY_H_INCLUDED


class Button;
class WordTestStudy;
class WordAddStudy;


class Study {
private:

	enum STUDY_MODE {
		SELECT_MODE,	// 選択画面
		WORD_TEST,		// 単語テスト
		WORD_ADD		// 単語追加
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

	// 終了時にtrueを返す
	bool play(int handX, int handY);

	void draw(int handX, int handY) const;
};


/*
* 単語テスト
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
* 単語追加
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