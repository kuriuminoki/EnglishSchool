#include "Vocabulary.h"
#include "DxLib.h"

#include <algorithm>
#include <fstream>

using namespace std;


/*
* 単語テスト用セット
*/
Vocabulary::Vocabulary(const char* path) {
	m_path = path;
	m_index = 0;
	m_prevIndex = m_index;
	m_importantWordSum = 0;
	read();
}

// ロード
bool Vocabulary::read() {

	m_words.clear();

	// ファイルポインタ
	int fp;

	// バッファ
	const int size = 512;
	char buff[size];

	// ファイルを開く
	fp = FileRead_open(m_path.c_str());
	FileRead_gets(buff, size, fp); // 最初の一行目はカラム名なので捨てる

	// ファイルの終端までループ
	while (FileRead_eof(fp) == 0) {
		// いったんバッファに一行分のテキストを入れる
		FileRead_gets(buff, size, fp);
		Word word;
		int now = 0;
		string oneCell = "";
		bool ignore = false;
		// 1文字ずつ見ていく
		for (int i = 0; buff[i] != '\0'; i++) {
			// CSVファイルなのでカンマで区切ってoneDataにpush_back
			if (buff[i] == '\"') {
				ignore = !ignore;
			}
			else if (buff[i] == ',' && now < 4 && !ignore) {
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
				else if (now == 3) {
					word.example = oneCell;
				}
				now++;
				oneCell = "";
			}
			else { // カンマ以外の文字なら合体
				oneCell += buff[i];
			}
		}
		// 4つめは例文
		word.count = stoi(oneCell);
		m_words.push_back(word);
	}

	// ファイルを閉じる
	FileRead_close(fp);
	return true;

}

// セーブ
bool Vocabulary::write() const {
	// ファイルポインタ
	ofstream outputFile(m_path);
	outputFile << "important,english,japanese,example,count" << endl;
	for (unsigned int i = 0; i < m_words.size(); i++) {
		outputFile << (int)m_words[i].importantFlag << ",";
		outputFile << '\"' << m_words[i].english << '\"' << ",";
		outputFile << '\"' << m_words[i].japanese << '\"' << ",";
		outputFile << '\"' << m_words[i].example << '\"' << ",";
		outputFile << '\"' << m_words[i].count << '\"' << endl;
	}
	return true;
}

// 単語除去
void Vocabulary::removeWord() {
	if ((int)m_words.size() == 1) { return; }
	if (m_words[m_index].importantFlag) { m_importantWordSum--; }
	m_words[m_index] = m_words.back();
	m_words.pop_back();
	if (m_index >= (int)m_words.size()) { m_index = (int)m_words.size() - 1; }
	m_prevIndex = m_index;
}

// 要注意
void Vocabulary::setImportantFlag(bool flag) {
	if (!m_words[m_index].importantFlag && flag) { m_importantWordSum++; }
	else if (m_words[m_index].importantFlag && !flag) { m_importantWordSum--; }
	m_words[m_index].importantFlag = flag;
}

// 単語シャッフル
void Vocabulary::shuffle() {
	int size = (int)m_words.size();
	for (int i = 0; i < size; i++) {
		int r = GetRand(size - 1 - i) + i;
		Word tmp = m_words[i];
		m_words[i] = m_words[r];
		m_words[r] = tmp;
	}
}

// 次の単語取得
Word Vocabulary::getWord() {
	return m_words[m_index];
}

// 次の単語へ移動
void Vocabulary::goNextWord(bool onlyImportant) {
	m_prevIndex = m_index;
	unsigned int i = 0;
	while (i == 0 || (onlyImportant && !m_words[m_index].importantFlag && i < m_words.size())) {
		if (++m_index == (int)m_words.size()) {
			m_index = 0;
		}
		i++;
	}
}

void Vocabulary::goPrevWord() {
	m_index = m_prevIndex;
}

void Vocabulary::init() {
	m_index = 0;
	m_prevIndex = m_index;
	m_importantWordSum = 0;
	read();
}

void Vocabulary::setFirstImportantWord() {
	if (!m_words[m_index].importantFlag) {
		goNextWord(true);
	}
}

void Vocabulary::wordCount() {
	m_words[m_index].count++;
}



/*
* 音読練習用セット
*/
SpeakingSet::SpeakingSet(const char* path) {
	m_path = path;
	m_index = 0;
	m_now = 0;
	m_cnt = 0;
	m_importantWordSum = 0;
	read();
}

bool SpeakingSet::speak() {
	m_cnt++;
	if (m_cnt % TEXT_SPEED == 1 && m_now < m_sentences[m_index].english.size()) {
		m_now = min(m_now + 2, (int)m_sentences[m_index].english.size());
		if (m_now == m_sentences[m_index].english.size()) {
			m_sentences[m_index].count++;
			return true;
		}
	}
	return false;
}

// ロード
bool SpeakingSet::read() {

	m_sentences.clear();

	// ファイルポインタ
	int fp;

	// バッファ
	const int size = 512;
	char buff[size];

	// ファイルを開く
	fp = FileRead_open(m_path.c_str());
	FileRead_gets(buff, size, fp); // 最初の一行目はカラム名なので捨てる

	// ファイルの終端までループ
	while (FileRead_eof(fp) == 0) {
		// いったんバッファに一行分のテキストを入れる
		FileRead_gets(buff, size, fp);
		Sentence sentence;
		int now = 0;
		string oneCell = "";
		bool ignore = false;
		// 1文字ずつ見ていく
		for (int i = 0; buff[i] != '\0'; i++) {
			// CSVファイルなのでカンマで区切ってoneDataにpush_back
			if (buff[i] == '\"') {
				ignore = !ignore;
			}
			else if (buff[i] == ',' && now < 4 && !ignore) {
				if (now == 0) {
					sentence.importantFlag = (bool)stoi(oneCell);
					if (sentence.importantFlag) { m_importantWordSum++; }
				}
				else if (now == 1) {
					sentence.english = oneCell;
				}
				else if (now == 2) {
					sentence.japanese = oneCell;
				}
				else if (now == 3) {
					sentence.appendix = oneCell;
				}
				now++;
				oneCell = "";
			}
			else { // カンマ以外の文字なら合体
				oneCell += buff[i];
			}
		}
		// 4つめは例文
		sentence.count = stoi(oneCell);
		m_sentences.push_back(sentence);
	}

	// ファイルを閉じる
	FileRead_close(fp);
	return true;

}

// セーブ
bool SpeakingSet::write() const {
	// ファイルポインタ
	ofstream outputFile(m_path);
	outputFile << "important,english,japanese,appendix,count" << endl;
	for (unsigned int i = 0; i < m_sentences.size(); i++) {
		outputFile << (int)m_sentences[i].importantFlag << ",";
		outputFile << '\"' << m_sentences[i].english << '\"' << ",";
		outputFile << '\"' << m_sentences[i].japanese << '\"' << ",";
		outputFile << '\"' << m_sentences[i].appendix << '\"' << ",";
		outputFile << m_sentences[i].count << endl;
	}
	return true;
}

// 要注意
void SpeakingSet::setImportantFlag(bool flag) {
	if (!m_sentences[m_index].importantFlag && flag) { m_importantWordSum++; }
	else if (m_sentences[m_index].importantFlag && !flag) { m_importantWordSum--; }
	m_sentences[m_index].importantFlag = flag;
}

// 文章シャッフル
void SpeakingSet::shuffle() {
	int size = (int)m_sentences.size();
	for (int i = 0; i < size; i++) {
		int r = GetRand(size - 1 - i) + i;
		Sentence tmp = m_sentences[i];
		m_sentences[i] = m_sentences[r];
		m_sentences[r] = tmp;
	}
}

// 次の文章取得
Sentence SpeakingSet::getSentence() {
	return m_sentences[m_index];
}

// 次の文章へ移動
void SpeakingSet::goNextSentence(bool onlyImportant) {
	unsigned int i = 0;
	m_now = 0;
	m_cnt = 0;
	while (i == 0 || (onlyImportant && !m_sentences[m_index].importantFlag && i < m_sentences.size())) {
		if (++m_index == (int)m_sentences.size()) {
			m_index = 0;
		}
		i++;
	}
}

void SpeakingSet::init() {
	m_index = 0;
	m_now = 0;
	m_cnt = 0;
	m_importantWordSum = 0;
	read();
}

void SpeakingSet::setFirstImportantSentence() {
	if (!m_sentences[m_index].importantFlag) {
		goNextSentence(true);
	}
}