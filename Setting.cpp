#include "Setting.h"
#include "Button.h"
#include "Control.h"
#include "Define.h"
#include "Teacher.h"


Setting::Setting(int font, Teacher* teacher_p) {
	m_font = font;
	m_teacher_p = teacher_p;
	m_changeTeacherButton = new Button("‹³t•ÏX", 100, 300, 400, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
	m_changeClothButton = new Button("•‘••ÏX", 100, 450, 400, 100, LIGHT_BLUE, BLUE, m_font, BLACK);
}

Setting::~Setting() {
	delete m_changeTeacherButton;
	delete m_changeClothButton;
}

bool Setting::play(int handX, int handY) {
	if (leftClick() == 1) {
		if (m_changeTeacherButton->overlap(handX, handY)) {
			m_teacher_p->setNextTeacher();
			m_teacher_p->setText(5, 120, EMOTE::NORMAL, true);
		}
		if (m_changeClothButton->overlap(handX, handY)) {
			m_teacher_p->setNextCloth();
			m_teacher_p->setText(6, 120, EMOTE::NORMAL, true);
		}
	}
	return false;
}

void Setting::draw(int handX, int handY) const {
	m_changeTeacherButton->draw(handX, handY);
	m_changeClothButton->draw(handX, handY);
}