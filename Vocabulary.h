#ifndef VOCABULARY_H_INCLUDED
#define VOCABULARY_H_INCLUDED

#include <string>
#include <vector>

struct Word {
	std::string english;	// �p�P��
	std::string japanese;	// �P��̓��{���
	std::string example;	// �p��̗ᕶ
	bool importantFlag;		// �v���ӒP��Ȃ�true
};

class Vocabulary {
private:

	std::string m_path;

	std::vector<Word> m_words;

	int m_index;

	int m_importantWordSum;

public:

	Vocabulary(const char* path);

	// �Q�b�^
	inline int getIndex() const { return m_index; }
	inline int getWordSum() const { return (int)m_words.size(); }
	inline int getImportantWordSum() const { return m_importantWordSum; }

	// �t�@�C���̓ǂݏ���
	bool read();
	bool write() const;

	// �P��ǉ��p
	void addWord(Word word);
	void removeWord();
	void setImportantFlag(bool flag);

	// �P��e�X�g�p
	void shuffle();
	Word getWord();
	void goNextWord(bool onlyImportant);
	void init();
	void setFirstImportantWord();

};

#endif