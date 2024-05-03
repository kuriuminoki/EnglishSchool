#include "TeacherDrawer.h"
#include "Teacher.h"
#include "Define.h"
#include "DxLib.h"

#include <algorithm>

using namespace std;


TeacherDrawer::TeacherDrawer(const Teacher* teacher) {
	m_teacher = teacher;
	m_font = CreateFontToHandle(NULL, 40, 3);
}

TeacherDrawer::~TeacherDrawer() {
	DeleteFontToHandle(m_font);
}

void TeacherDrawer::draw() {
	
	// ���t�̉摜
	int handle = m_teacher->getHandle();
	int dx = 0, dy = 0;
	dx = m_teacher->getAction()->getDx();
	dy = m_teacher->getAction()->getDy();
	DrawRotaGraph(1600 + dx, 600 + dy, 0.7, 0, handle, TRUE);

	// �Z���t
	const Text* text = m_teacher->getText();
	if (text != nullptr) {
		string str = text->getText();
		drawText(600, 50, 500, str, BLACK, m_font);
	}

}

void TeacherDrawer::drawText(int x, int y, int height, const std::string text, int color, int font) {
	int now = 0;
	int i = 0;
	const int size = (int)(text.size());
	// �Z���t
	while (now < size) {

		// ���͉������ڂ܂ŕ\�����邩
		int next = now + min(MAX_TEXT_LEN, size - now);

		// ���̍s�̐擪���u�A�v���u�B�v�Ȃ炻����܂߂�
		if (next - now >= 0 && size >= next + 2) {
			string nextStrHead = text.substr(next, 2);
			if (nextStrHead == "�A" || nextStrHead == "�B" || nextStrHead == "�H" || nextStrHead == "�I") {
				next += 2;
			}
		}

		string disp = text.substr(now, next - now);
		size_t br = disp.find("�b"); // ���s�̋L��
		if (br != string::npos) {
			disp = disp.substr(0, br);
			now += (int)br + 2;
		}
		else {
			now = next;
		}

		// �Z���t��`��
		if (disp.size() == 0) { continue; }
		DrawStringToHandle(x, y + (i * height), disp.c_str(), BLACK, m_font);

		// ���̍s
		i++;
	}
}