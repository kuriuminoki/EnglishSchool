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



/*
* ���t�̃A�N�V����
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
* ����
*/
Text::Text(const char* speakerName, int num, int wait, TeacherAction* teacherAction_p) {
	m_speakerName = speakerName;
	m_text = "";
	m_textNow = 0;
	m_cnt = 0;
	m_wait = wait;
	m_textSpeed = TEXT_SPEED;
	// �Ώۂ̃t�@�C�����J�� "text/�g���`/1.txt"
	ostringstream oss;
	oss << "text/" << speakerName << "/" << num << ".txt";
	m_fp = FileRead_open(oss.str().c_str());
	m_teacherAction_p = teacherAction_p;
}

Text::~Text() {
	// �t�@�C�������
	FileRead_close(m_fp);
}

// ��b���s��
bool Text::play() {
	if (m_wait == 0) { return true; }
	// �v���C���[����̃A�N�V�����i�X�y�[�X�L�[���́j
	if (finishText()) {
		// �S�Ẳ�b���I�����
		if (FileRead_eof(m_fp) != 0) {
			m_wait--;
			if (m_wait == 0) { return true; }
			return false;
		}
		// ���̃e�L�X�g�ֈڂ�
		loadNextBlock();
	}

	// �\�������𑝂₷
	m_cnt++;
	if (m_cnt % m_textSpeed == 0 && !finishText()) {
		// ���{��\���͂P�������T�C�Y�Q��
		m_textNow = min(m_textNow + 2, (unsigned int)m_text.size());
	}

	return false;
}

// �Z���t���Ō�܂ŕ\��������
bool Text::finishText() const {
	return m_textNow == m_text.size();
}

void Text::loadNextBlock() {
	// �o�b�t�@
	const int size = 512;
	char buff[size];
	// �u���b�N��1�s��
	string str = "";
	while (FileRead_eof(m_fp) == 0) {
		// ��s�ȊO������܂Ń��[�v
		FileRead_gets(buff, size, m_fp);
		str = buff;
		if (str != "") { break; }
	}
	if (str == "@quake") {
		// �t�L�_�V��h�炷
		FileRead_gets(buff, size, m_fp);
		string s = buff; // ����
		m_teacherAction_p->setQuakeCnt(stoi(s));
		loadNextBlock();
	}
	else if (str == "@jump") {
		// �t�L�_�V���W�����v������
		FileRead_gets(buff, size, m_fp);
		string s = buff; // ����
		m_teacherAction_p->setVy(stoi(s));
		loadNextBlock();
	}
	else {
		// �Z���t�X�V
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

// �e�L�X�g��Ԃ��i�`��p�j
std::string Text::getText() const {
	return m_text.substr(0, m_textNow);
}


/*
* ���t
*/
Teacher::Teacher(const char* name) {
	// ���O
	m_name = name;

	// �摜
	string path = "picture/";
	path += m_name;
	path += "/";
	m_normalHandle.push_back(LoadGraph((path + "�ʏ�1.png").c_str()));
	m_normalHandle.push_back(LoadGraph((path + "�ʏ�2.png").c_str()));
	m_smileHandle.push_back(LoadGraph((path + "�Ί�1.png").c_str()));
	m_smileHandle.push_back(LoadGraph((path + "�Ί�2.png").c_str()));
	m_angryHandle.push_back(LoadGraph((path + "����1.png").c_str()));
	m_angryHandle.push_back(LoadGraph((path + "����2.png").c_str()));

	// �Z���t
	m_text = nullptr;

	// �\��
	m_emote = EMOTE::NORMAL;

	m_teacherAction = new TeacherAction();

	m_animeRepeat = true;

	m_handleIndex = 0;
}

Teacher::~Teacher() {
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
	m_teacherAction->play();
}

void Teacher::jump() {
	m_teacherAction->setVy(-10);
}

void Teacher::quake() {
	m_teacherAction->setQuakeCnt(30);
}