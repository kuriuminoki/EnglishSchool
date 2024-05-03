#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED


class Button;
class Lesson;
class Study;
class SelectMode;
class Setting;
class Teacher;


enum GAME_MODE {
	SELECT_MODE,	// ���[�h�I�����
	LESSON_MODE,	// ���ƃ��[�h
	STUDY_MODE,		// ���K���[�h
	SETTING_MODE	// �Z�b�e�B���O���[�h
};


class Game {
private:

	int m_handX, m_handY;

	// ���v���C���̃��[�h
	GAME_MODE m_state;

	// �e���[�h
	SelectMode* m_selectMode;
	Lesson* m_lesson;
	Study* m_study;
	Setting* m_setting;

	int m_font;

	// ���[�h�I����ʂ֖߂�{�^��
	Button* m_backButton;

	// ���t
	Teacher* m_teacher;

public:

	Game();

	~Game();

	// �Q�b�^
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


/*
* ���[�h�I�����
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