#ifndef INCLUDED_BUTTON_H
#define INCLUDED_BUTTON_H


#include<string>


class Button {
private:

	bool m_flag = true;//�@�\���Ȃ��{�^����false

	std::string m_tag = ""; // �\������e�L�X�g

	int m_x, m_y; //�{�^���̈ʒu

	int m_wide, m_height; // �l�p�̍����ƕ�

	int m_color; //�l�p�̒��̐F

	int m_color2; //�}�E�X���d�Ȃ��Ă���Ƃ��Ɏg���F

	int m_font_color; //�����̐F

	int m_font; // �e�L�X�g�̃t�H���g

	int m_dx, m_dy; //������\��������W

	int m_graph_handle = -1; //�G

	int m_graph_ex; //�G�̊g�嗦

public:

	// �R���X�g���N�^
	Button(std::string, int x, int y, int wide, int height, int color, int color2, int font, int font_color);

	// �Q�b�^
	inline bool getFlag() const { return m_flag; }
	inline int getHandle() const { return m_graph_handle; } //�摜���擾
	inline int getWide() const { return m_wide; }
	inline int getHeight() const { return m_height; }

	// �Z�b�^
	void setGraph(int handle, int ex);
	void setString(std::string new_string);//�^�O�����Ȃ���
	inline void setX(int x) { m_x = x; }
	inline void setColor(int colorHandle) { m_color = colorHandle; }

	// �{�^����on/off�؂�ւ�
	void changeFlag(bool f, int new_color);

	// �}�E�X���d�Ȃ��Ă��邩�m�F
	bool overlap(int hand_x, int hand_y);

	// �`��
	void draw(int hand_x, int hand_y);
};


#endif