#include "Teacher.h"
#include "DxLib.h"

#include <sstream>
#include <algorithm>

using namespace std;



int calcIndex(int size, int index, bool repeat) {
	if (repeat) { index %= size; }
	else { index = min(size - 1, index); }
	return index;
}


void clearVector(vector<int>& vec) {
	for (unsigned int i = 0; i < vec.size(); i++) {
		DeleteGraph(vec[i]);
	}
	vec.clear();
}



/*
* 教師のアクション
*/
TeacherAction::TeacherAction() {
	init();
}

void TeacherAction::init() {
	m_jumpFlag = false;
	m_dx = 0;
	m_dy = 0;
	m_vy = 0;
	m_quakeCnt = 0;
	m_quakeDx = 0;
	m_quakeDy = 0;
}

void TeacherAction::play() {

	if (m_jumpFlag) {
		m_vy++;
		m_dy += m_vy;
		if (m_dy > 0 && m_vy > 0) {
			init();
		}
	}

	if (m_quakeCnt > 0) {
		m_quakeCnt--;
		m_quakeDx = GetRand(50) - 25;
		m_quakeDy = GetRand(50) - 25;
		if (m_vy == 0 && m_quakeCnt == 0) {
			init();
		}
	}

}


/*
* 発言
*/
Text::Text(const char* speakerName, int num, int wait, TeacherAction* teacherAction_p) {
	m_speakerName = speakerName;
	m_text = "";
	m_textNow = 0;
	m_cnt = 0;
	m_wait = wait;
	m_textSpeed = TEXT_SPEED;
	// 対象のファイルを開く "text/トモチ/1.txt"
	ostringstream oss;
	oss << "text/" << speakerName << "/" << num << ".txt";
	m_fp = FileRead_open(oss.str().c_str());
	m_teacherAction_p = teacherAction_p;
}

Text::~Text() {
	// ファイルを閉じる
	FileRead_close(m_fp);
}

// 会話を行う
bool Text::play() {
	if (m_wait == 0) { return true; }
	// プレイヤーからのアクション（スペースキー入力）
	if (finishText()) {
		// 全ての会話が終わった
		if (FileRead_eof(m_fp) != 0) {
			m_wait--;
			if (m_wait == 0) { return true; }
			return false;
		}
		// 次のテキストへ移る
		loadNextBlock();
	}

	// 表示文字を増やす
	m_cnt++;
	if (m_cnt % m_textSpeed == 0 && !finishText()) {
		// 日本語表示は１文字がサイズ２分
		m_textNow = min(m_textNow + 2, (unsigned int)m_text.size());
	}

	return false;
}

// セリフを最後まで表示したか
bool Text::finishText() const {
	return m_textNow == m_text.size();
}

void Text::loadNextBlock() {
	// バッファ
	const int size = 512;
	char buff[size];
	// ブロックの1行目
	string str = "";
	while (FileRead_eof(m_fp) == 0) {
		// 空行以外が来るまでループ
		FileRead_gets(buff, size, m_fp);
		str = buff;
		if (str != "") { break; }
	}
	if (str == "@quake") {
		// フキダシを揺らす
		FileRead_gets(buff, size, m_fp);
		string s = buff; // 時間
		m_teacherAction_p->setQuakeCnt(stoi(s));
		loadNextBlock();
	}
	else if (str == "@jump") {
		// フキダシをジャンプさせる
		FileRead_gets(buff, size, m_fp);
		string s = buff; // 初速
		m_teacherAction_p->setVy(stoi(s));
		loadNextBlock();
	}
	else {
		// セリフ更新
		setNextText(size, buff);
	}
}


void Text::setNextText(const int size, char* buff) {
	m_cnt = 0;
	m_textNow = 0;

	FileRead_gets(buff, size, m_fp);
	m_text = buff;

	if (FileRead_eof(m_fp) == 0) {
		FileRead_gets(buff, size, m_fp);
		string s = buff;
		if (s == "") {
			m_textSpeed = TEXT_SPEED;
		}
		else {
			m_textSpeed = stoi(s);
			FileRead_gets(buff, size, m_fp);
		}
	}
	else {
		m_textSpeed = TEXT_SPEED;
	}
}

// テキストを返す（描画用）
std::string Text::getText() const {
	return m_text.substr(0, m_textNow);
}


/*
* 教師
*/
Teacher::Teacher(int nameIndex, int clothIndex) {
	m_reverseX = true;

	// 名前
	m_name = TEACHER_LIST[nameIndex];

	m_cloth = CLOTH_LIST[clothIndex];

	for (unsigned int i = 0; i < TEACHER_SUM; i++) {
		m_exp.push_back(0);
		string path = "data/teacher/";
		path += TEACHER_LIST[i];
		path += ".dat";
		FILE* intFp = nullptr;
		if (fopen_s(&intFp, path.c_str(), "rb") != 0) {
			continue;
		}
		// Read
		long long int exp = 0;
		fread(&exp, sizeof(exp), 1, intFp);
		m_exp[i] = exp;
		fclose(intFp);
	}

	// セリフ
	m_text = nullptr;

	// 表情
	m_emote = EMOTE::NORMAL;

	m_teacherAction = new TeacherAction();

	m_animeRepeat = true;

	m_handleIndex = 0;

	changeTeacher(nameIndex);
}

Teacher::~Teacher() {
	for (unsigned int i = 0; i < TEACHER_SUM; i++) {
		string path = "data/teacher/";
		path += TEACHER_LIST[i];
		path += ".dat";
		FILE* intFp = nullptr;
		if (fopen_s(&intFp, path.c_str(), "wb") != 0) {
			continue;
		}
		// Read
		long long int exp = m_exp[i];
		fwrite(&exp, sizeof(exp), 1, intFp);
		fclose(intFp);
	}
	for (unsigned int i = 0; i < m_normalHandle.size(); i++) {
		DeleteGraph(m_normalHandle[i]);
	}
	for (unsigned int i = 0; i < m_smileHandle.size(); i++) {
		DeleteGraph(m_smileHandle[i]);
	}
	for (unsigned int i = 0; i < m_angryHandle.size(); i++) {
		DeleteGraph(m_angryHandle[i]);
	}
	delete m_teacherAction;
}

int Teacher::getHandle() const {
	int size = 0;
	switch (m_emote) {
	case NORMAL:
		return m_normalHandle[calcIndex(2, m_handleIndex, m_animeRepeat)];
	case SMILE:
		return m_smileHandle[calcIndex(2, m_handleIndex, m_animeRepeat)];
	case ANGRY:
		return m_angryHandle[calcIndex(2, m_handleIndex, m_animeRepeat)];
	}
	return m_normalHandle[0];
}

void Teacher::setText(int num, int wait, EMOTE emote, bool animeRepeat) {
	if (m_text != nullptr) { delete m_text; }
	m_text = new Text(m_name, num, wait, m_teacherAction);
	m_emote = emote;
	m_animeRepeat = animeRepeat;
}

// 
void Teacher::setRandomText() {
	// セリフの総数
	int sum = 5;
	// レベルが上がるとセリフの数が増える
	if (getLevel() < 10) {
		sum = 5;
	}
	int num = GetRand(sum - 1) + 1000;
	setText(num, 120, EMOTE::NORMAL, true);
}

// 
void Teacher::setAdviceText() {
	// セリフの総数
	int sum = 5;
	// レベルが上がるとセリフの数が増える
	if (getLevel() < 10) {
		sum = 5;
	}
	int num = GetRand(sum - 1) + 2000;
	setText(num, 120, EMOTE::NORMAL, true);
}

void Teacher::play() {
	if (m_text != nullptr) {
		if (m_text->play()) {
			delete m_text;
			m_text = nullptr;
			m_emote = EMOTE::NORMAL;
			m_handleIndex = 0;
		}
		else {
			if (m_text->getCnt() % ANIME_SPEED == 0 && !m_text->finishText()) {
				m_handleIndex++;
			}
			else if (m_text->finishText()) {
				m_handleIndex = 0;
			}
		}
	}
	else if (GetRand(300) == 0) {
		setAdviceText();
	}
	m_teacherAction->play();
}

void Teacher::jump() {
	m_teacherAction->setVy(-10);
}

void Teacher::quake() {
	m_teacherAction->setQuakeCnt(30);
}

void Teacher::setNextTeacher() {
	changeTeacher(m_nameIndex + 1);
}

void Teacher::setNextCloth() {
	changeCloth(m_clothIndex + 1);
}

// 教師変更
void Teacher::changeTeacher(int index) {

	m_nameIndex = index % TEACHER_SUM;
	if (m_nameIndex == 2 || m_nameIndex == 3) {
		m_reverseX = false;
	}
	else {
		m_reverseX = true;
	}

	// セリフがあるなら消す
	if (m_text != nullptr) { 
		delete m_text;
		m_text = nullptr;
	}

	// 名前
	m_name = TEACHER_LIST[m_nameIndex];

	// レベルと使える服の判定
	if (getLevel() / 10 < m_clothIndex) {
		m_clothIndex = 0;
		m_cloth = CLOTH_LIST[m_clothIndex];
	}

	// 初期化
	clearVector(m_normalHandle);
	clearVector(m_smileHandle);
	clearVector(m_angryHandle);

	// 画像
	string path = "picture/";
	path += m_name;
	path += "/";
	path += m_cloth;
	m_normalHandle.push_back(LoadGraph((path + "通常1.png").c_str()));
	m_normalHandle.push_back(LoadGraph((path + "通常2.png").c_str()));
	m_smileHandle.push_back(LoadGraph((path + "笑顔1.png").c_str()));
	m_smileHandle.push_back(LoadGraph((path + "笑顔2.png").c_str()));
	m_angryHandle.push_back(LoadGraph((path + "注意1.png").c_str()));
	m_angryHandle.push_back(LoadGraph((path + "注意2.png").c_str()));
}

// 服装変更
void Teacher::changeCloth(int index) {
	m_clothIndex = index % CLOTH_SUM;
	m_cloth = CLOTH_LIST[m_clothIndex];
	changeTeacher(m_nameIndex);
}