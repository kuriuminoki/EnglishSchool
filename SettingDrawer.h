#ifndef SETTING_DRAWER_H_INCLUDED
#define SETTING_DRAWER_H_INCLUDED

class Setting;
class Teacher;

class SettingDrawer {
private:

	const Setting* m_setting;

public:
	SettingDrawer(const Setting* setting);

	void draw(int handX, int handY);
};

#endif