#include "Vocabulary.h"
#include "DxLib.h"

#include <algorithm>
#include <fstream>

using namespace std;


Vocabulary::Vocabulary(const char* path) {
	m_path = path;
	m_index = 0;
	m_importantWordSum = 0;
	read();
}

// ���[�h
bool Vocabulary::read() {

	m_words.clear();

	// �t�@�C���|�C���^
	int fp;

	// �o�b�t�@
	const int size = 512;
	char buff[size];

	// �t�@�C�����J��
	fp = FileRead_open(m_path.c_str());
	FileRead_gets(buff, size, fp); // �ŏ��̈�s�ڂ̓J�������Ȃ̂Ŏ̂Ă�

	// �t�@�C���̏I�[�܂Ń��[�v
	while (FileRead_eof(fp) == 0) {
		// ��������o�b�t�@�Ɉ�s���̃e�L�X�g������
		FileRead_gets(buff, size, fp);
		Word word;
		int now = 0;
		string oneCell = "";
		// 1���������Ă���
		for (int i = 0; buff[i] != '\0'; i++) {
			// CSV�t�@�C���Ȃ̂ŃJ���}�ŋ�؂���oneData��push_back
			if (buff[i] == ',' && now < 3) {
				if (now == 0) {
					word.importantFlag = (bool)stoi(oneCell);
					if (word.importantFlag) { m_importantWordSum++; }
				}
				else if (now == 1) {
					word.english = oneCell;
				}
				else if (now == 2) {
					word.japanese = oneCell;
				}
				now++;
				oneCell = "";
			}
			else { // �J���}�ȊO�̕����Ȃ獇��
				oneCell += buff[i];
			}
		}
		// 4�߂͗ᕶ
		word.example = oneCell;
		m_words.push_back(word);
	}

	// �t�@�C�������
	FileRead_close(fp);
	return true;

}

// �Z�[�u
bool Vocabulary::write() const {
	// �t�@�C���|�C���^
	ofstream outputFile(m_path);
	outputFile << "important,english,japanese,example" << endl;
	for (unsigned int i = 0; i < m_words.size(); i++) {
		outputFile << (int)m_words[i].importantFlag << ",";
		outputFile << m_words[i].english << ",";
		outputFile << m_words[i].japanese << ",";
		outputFile << m_words[i].example << endl;
	}
	return true;
}

// �P��ǉ�
void Vocabulary::addWord(Word word) {
	if (word.importantFlag) { m_importantWordSum++; }
	m_words.push_back(word);
}

// �P�ꏜ��
void Vocabulary::removeWord() {
	if ((int)m_words.size() == 1) { return; }
	if (m_words[m_index].importantFlag) { m_importantWordSum--; }
	m_words[m_index] = m_words.back();
	m_words.pop_back();
	if (m_index >= (int)m_words.size()) { m_index = (int)m_words.size() - 1; }
}

// �v����
void Vocabulary::setImportantFlag(bool flag) {
	if (!m_words[m_index].importantFlag && flag) { m_importantWordSum++; }
	else if (m_words[m_index].importantFlag && !flag) { m_importantWordSum--; }
	m_words[m_index].importantFlag = flag;
}

// �P��V���b�t��
void Vocabulary::shuffle() {
	int size = (int)m_words.size();
	for (int i = 0; i < size; i++) {
		int r = GetRand(size - 1 - i) + i;
		Word tmp = m_words[i];
		m_words[i] = m_words[r];
		m_words[r] = tmp;
	}
}

// ���̒P��擾
Word Vocabulary::getWord() {
	return m_words[m_index];
}

// ���̒P��ֈړ�
void Vocabulary::goNextWord(bool onlyImportant) {
	unsigned int i = 0;
	while (i == 0 || (onlyImportant && !m_words[m_index].importantFlag && i < m_words.size())) {
		if (++m_index == (int)m_words.size()) {
			m_index = 0;
		}
		i++;
	}
}

void Vocabulary::init() {
	m_index = 0;
	m_importantWordSum = 0;
	read();
}

void Vocabulary::setFirstImportantWord() {
	if (!m_words[m_index].importantFlag) {
		goNextWord(true);
	}
}