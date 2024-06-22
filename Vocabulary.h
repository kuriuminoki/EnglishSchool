#ifndef VOCABULARY_H_INCLUDED
#define VOCABULARY_H_INCLUDED

#include <string>
#include <vector>

struct Word {
	std::string english;	// 英単語
	std::string japanese;	// 単語の日本語訳
	std::string example;	// 英語の例文
	bool importantFlag;		// 要注意単語ならtrue
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

	// ゲッタ
	inline int getIndex() const { return m_index; }
	inline int getPrevIndex() const { return m_prevIndex; }
	inline int getWordSum() const { return (int)m_words.size(); }
	inline int getImportantWordSum() const { return m_importantWordSum; }

	// ファイルの読み書き
	bool read();
	bool write() const;

	// 単語追加用
	void removeWord();
	void setImportantFlag(bool flag);

	// 単語テスト用
	void shuffle();
	Word getWord();
	void goNextWord(bool onlyImportant);
	void goPrevWord();
	void init();
	void setFirstImportantWord();

};


struct Sentence {
	std::string english;	// 英単語
	std::string japanese;	// 単語の日本語訳
	std::string appendix;	// 英語の例文
	bool importantFlag;		// 要注意単語ならtrue
	int count;				// 音読回数
};

class SpeakingSet {
private:

	std::string m_path;

	std::vector<Sentence> m_sentences;

	int m_now; // 今何文字目まで表示したか
	int m_cnt;
	const int TEXT_SPEED = 5;

	int m_index;

	int m_importantWordSum;

public:

	SpeakingSet(const char* path);

	// ゲッタ
	inline int getIndex() const { return m_index; }
	inline int getSentenceSum() const { return (int)m_sentences.size(); }
	inline int getImportantSentenceSum() const { return m_importantWordSum; }
	inline int getNow() const { return m_now; }

	inline void setZeroNow() { m_now = 0; }

	// 音読練習
	bool speak();

	// ファイルの読み書き
	bool read();
	bool write() const;

	void setImportantFlag(bool flag);

	// 音読練習用
	void shuffle();
	Sentence getSentence();
	void goNextSentence(bool onlyImportant);
	void init();
	void setFirstImportantSentence();

};


#endif