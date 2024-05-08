#ifndef GAME_DRAWER_H_INCLUDED
#define GAME_DRAWER_H_INCLUDED


class Game;
class LessonDrawer;
class SettingDrawer;
class StudyDrawer;
class TeacherDrawer;


class GameDrawer {
private:

	const Game* m_game_p;

	TeacherDrawer* m_teacherDrawer;

	StudyDrawer* m_studyDrawer;

	LessonDrawer* m_lessonDrawer;

	SettingDrawer* m_settingDrawer;

	// çïî¬âÊëú
	int m_kokuban;

	bool m_dispTeacher;

public:

	GameDrawer(const Game* game);
	~GameDrawer();

	void draw();

};

#endif