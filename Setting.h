#ifndef SETTING_H_INCLUDED
#define SETTING_H_INCLUDED

class Button;
class Teacher;

class Setting {
private:

	int m_font;

	Teacher* m_teacher_p;

	Button* m_changeTeacherButton;
	Button* m_changeClothButton;

public:
	Setting(int font, Teacher* teacher_p);
	~Setting();

	// I—¹‚Étrue‚ğ•Ô‚·
	bool play(int handX, int handY);
	void draw(int handX, int handY) const;
};

#endif