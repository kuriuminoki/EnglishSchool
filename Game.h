#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED


class Lesson;
class Study;
class SelectMode;
class Setting;


enum GAME_MODE {
	SELECT_MODE,	// ���[�h�I�����
	LESSON_MODE,	// ���ƃ��[�h
	STUDY_MODE,		// ���K���[�h
	SETTING_MODE	// �Z�b�e�B���O���[�h
};


class Game {
private:

	// ���v���C���̃��[�h
	GAME_MODE m_state;

	// �e���[�h
	SelectMode* m_selectMode;
	Lesson* m_lesson;
	Study* m_study;
	Setting* m_setting;

public:

	Game();

	~Game();

	// �Q�b�^
	inline const GAME_MODE getState() const { return m_state; }
	inline const SelectMode* getSelectMode() const { return m_selectMode; }
	inline const Lesson* getLesson() const { return m_lesson; }
	inline const Study* getStudy() const { return m_study; }
	inline const Setting* getSetting() const { return m_setting; }

	void play();

};


/*
* ���[�h�I�����
*/ 
class SelectMode {
private:

public:
	SelectMode();
	~SelectMode();
	GAME_MODE play();
};

#endif