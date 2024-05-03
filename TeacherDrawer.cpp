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
	
	// 教師の画像
	int handle = m_teacher->getHandle();
	int dx = 0, dy = 0;
	dx = m_teacher->getAction()->getDx();
	dy = m_teacher->getAction()->getDy();
	DrawRotaGraph(1600 + dx, 600 + dy, 0.7, 0, handle, TRUE);

	// セリフ
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
	// セリフ
	while (now < size) {

		// 次は何文字目まで表示するか
		int next = now + min(MAX_TEXT_LEN, size - now);

		// 次の行の先頭が「、」か「。」ならそれも含める
		if (next - now >= 0 && size >= next + 2) {
			string nextStrHead = text.substr(next, 2);
			if (nextStrHead == "、" || nextStrHead == "。" || nextStrHead == "？" || nextStrHead == "！") {
				next += 2;
			}
		}

		string disp = text.substr(now, next - now);
		size_t br = disp.find("｜"); // 改行の記号
		if (br != string::npos) {
			disp = disp.substr(0, br);
			now += (int)br + 2;
		}
		else {
			now = next;
		}

		// セリフを描画
		if (disp.size() == 0) { continue; }
		DrawStringToHandle(x, y + (i * height), disp.c_str(), BLACK, m_font);

		// 次の行
		i++;
	}
}