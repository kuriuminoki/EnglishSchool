#include "SettingDrawer.h"
#include "Setting.h"
#include "Teacher.h"


SettingDrawer::SettingDrawer(const Setting* setting) {
	m_setting = setting;
}

void SettingDrawer::draw(int handX, int handY) {
	m_setting->draw(handX, handY);
}