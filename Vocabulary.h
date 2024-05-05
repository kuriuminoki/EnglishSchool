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

	int m_importantWordSum;

public:

	Vocabulary(const char* path);

	// ゲッタ
	inline int getIndex() const { return m_index; }
	inline int getWordSum() const { return (int)m_words.size(); }
	inline int getImportantWordSum() const { return m_importantWordSum; }

	// ファイルの読み書き
	bool read();
	bool write() const;

	// 単語追加用
	void addWord(Word word);
	void removeWord();
	void setImportantFlag(bool flag);

	// 単語テスト用
	void shuffle();
	Word getWord();
	void goNextWord(bool onlyImportant);
	void init();
	void setFirstImportantWord();

};

#endif