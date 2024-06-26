#include "Control.h"
#include "Define.h"
#include "Game.h"
#include "GameDrawer.h"
#include "LessonDrawer.h"
#include "SettingDrawer.h"
#include "StudyDrawer.h"
#include "TeacherDrawer.h"

#include "DxLib.h"


GameDrawer::GameDrawer(const Game* game) {
	m_dispTeacher = true;
	m_game_p = game;
	m_studyDrawer = new StudyDrawer(nullptr);
	m_lessonDrawer = new LessonDrawer(nullptr);
	m_teacherDrawer = new TeacherDrawer(m_game_p->getTeacher());
	m_settingDrawer = new SettingDrawer(m_game_p->getSetting());
	m_kokuban = LoadGraph("picture/kokuban.png");
}

GameDrawer::~GameDrawer() {
	delete m_studyDrawer;
	delete m_lessonDrawer;
	delete m_teacherDrawer;
	delete m_settingDrawer;
	DeleteGraph(m_kokuban);
}

void GameDrawer::draw() {

	if ((controlLeftShift() > 0 || controlRightShift() > 0) && rightClick() == 1) {
		m_dispTeacher = !m_dispTeacher;
	}

	if (m_dispTeacher) {
		DrawBox(0, 0, GAME_WIDE, GAME_HEIGHT, HAIKEI_BROWN, TRUE);
	}

	DrawExtendGraph(20, 200, 1400, 1000, m_kokuban, TRUE);

	if (m_dispTeacher) {
		m_teacherDrawer->draw();
	}

	m_game_p->draw();

	int handX = m_game_p->getHandX();
	int handY = m_game_p->getHandY();

	GAME_MODE state = m_game_p->getState();
	switch (state) {
	case SELECT_MODE:
		m_game_p->getSelectMode()->draw(handX, handY);
		break;
	case LESSON_MODE:
		m_lessonDrawer->setLesson(m_game_p->getLesson());
		m_lessonDrawer->draw(handX, handY);
		break;
	case STUDY_MODE:
		m_studyDrawer->setStudy(m_game_p->getStudy());
		m_studyDrawer->draw(handX, handY);
		break;
	case SETTING_MODE:
		m_settingDrawer->draw(handX, handY);
		break;
	}

}