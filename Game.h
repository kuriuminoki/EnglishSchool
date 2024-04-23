#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED


class Lesson;
class Study;
class SelectMode;
class Setting;


enum GAME_MODE {
	SELECT_MODE,	// モード選択画面
	LESSON_MODE,	// 授業モード
	STUDY_MODE,		// 自習モード
	SETTING_MODE	// セッティングモード
};


class Game {
private:

	// 今プレイ中のモード
	GAME_MODE m_state;

	// 各モード
	SelectMode* m_selectMode;
	Lesson* m_lesson;
	Study* m_study;
	Setting* m_setting;

public:

	Game();

	~Game();

	// ゲッタ
	inline const GAME_MODE getState() const { return m_state; }
	inline const SelectMode* getSelectMode() const { return m_selectMode; }
	inline const Lesson* getLesson() const { return m_lesson; }
	inline const Study* getStudy() const { return m_study; }
	inline const Setting* getSetting() const { return m_setting; }

	void play();

};


/*
* モード選択画面
*/ 
class SelectMode {
private:

public:
	SelectMode();
	~SelectMode();
	GAME_MODE play();
};

#endif