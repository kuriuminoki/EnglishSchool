#ifndef TEACHER_DRAWER_H_INCLUDED
#define TEACHER_DRAWER_H_INCLUDED

#include <string>

class Teacher;

class TeacherDrawer {
private:

	const Teacher* m_teacher;

	// フォント（テキスト）
	int m_textHandle;
	const int TEXT_SIZE = 50;

	// 一行に表示する文字数
	const int MAX_TEXT_LEN = 48;

	int m_font;

public:
	TeacherDrawer(const Teacher* teacher);
	~TeacherDrawer();

	void draw();

	void drawText(int x, int y, int height, const std::string text, int color, int font);
};

#endif