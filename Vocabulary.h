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

	int m_prevIndex;

	int m_importantWordSum;

public:

	Vocabulary(const char* path);

	// �Q�b�^
	inline int getIndex() const { return m_index; }
	inline int getPrevIndex() const { return m_prevIndex; }
	inline int getWordSum() const { return (int)m_words.size(); }
	inline int getImportantWordSum() const { return m_importantWordSum; }

	// �t�@�C���̓ǂݏ���
	bool read();
	bool write() const;

	// �P��ǉ��p
	void removeWord();
	void setImportantFlag(bool flag);

	// �P��e�X�g�p
	void shuffle();
	Word getWord();
	void goNextWord(bool onlyImportant);
	void goPrevWord();
	void init();
	void setFirstImportantWord();

};


struct Sentence {
	std::string english;	// �p�P��
	std::string japanese;	// �P��̓��{���
	std::string appendix;	// �p��̗ᕶ
	bool importantFlag;		// �v���ӒP��Ȃ�true
	int count;				// ���ǉ�
};

class SpeakingSet {
private:

	std::string m_path;

	std::vector<Sentence> m_sentences;

	int m_now; // ���������ڂ܂ŕ\��������
	int m_cnt;
	const int TEXT_SPEED = 5;

	int m_index;

	int m_importantWordSum;

public:

	SpeakingSet(const char* path);

	// �Q�b�^
	inline int getIndex() const { return m_index; }
	inline int getSentenceSum() const { return (int)m_sentences.size(); }
	inline int getImportantSentenceSum() const { return m_importantWordSum; }
	inline int getNow() const { return m_now; }

	inline void setZeroNow() { m_now = 0; }

	// ���Ǘ��K
	bool speak();

	// �t�@�C���̓ǂݏ���
	bool read();
	bool write() const;

	void setImportantFlag(bool flag);

	// ���Ǘ��K�p
	void shuffle();
	Sentence getSentence();
	void goNextSentence(bool onlyImportant);
	void init();
	void setFirstImportantSentence();

};


#endif