#include "LessonDrawer.h"
#include "Lesson.h"


LessonDrawer::LessonDrawer(const Lesson* lesson) {
	m_lesson_p = lesson;
}

LessonDrawer::~LessonDrawer() {

}

void LessonDrawer::draw(int handX, int handY) {
	if (m_lesson_p != nullptr) {
		m_lesson_p->draw(handX, handY);
	}
}