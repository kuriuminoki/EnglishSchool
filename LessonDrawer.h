#ifndef LESSON_DRAWER_H_INCLUDED
#define LESSON_DRAWER_H_INCLUDED

class Lesson;


class LessonDrawer {
private:

	const Lesson* m_lesson_p;

public:

	LessonDrawer(const Lesson* lesson);
	~LessonDrawer();

	void draw(int handX, int handY);

};

#endif