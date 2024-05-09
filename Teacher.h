#ifndef TEACHER_H_INCLUDED
#define TEACHER_H_INCLUDED

#include <string>
#include <vector>


/*
* 教師のアクション
*/
class TeacherAction {
private:

	// ジャンプ中
	bool m_jumpFlag;

	// 座標のずれ
	int m_dx, m_dy;

	// 速度
	int m_vy;

	// 振動する残り時間
	int m_quakeCnt;

	// 振動によるずれ
	int m_quakeDx, m_quakeDy;

public:

	TeacherAction();

	// ゲッタ
	int getDx() const { return m_dx + m_quakeDx; }
	int getDy() const { return m_dy + m_quakeDy; }

	// セッタ
	void setVy(int vy) { m_vy = vy; m_jumpFlag = true; }
	void setQuakeCnt(int cnt) { m_quakeCnt = cnt; }

	void init();

	void play();

};


/*
* 発言
*/
class Text {
private:

	// 文字表示の速さ 1が最速
	const unsigned int TEXT_SPEED = 5;
	unsigned int m_textSpeed;

	// セリフ
	std::string m_text;

	// ファイルポインタ
	int m_fp;

	// 発言者の名前
	std::string m_speakerName;

	// 今何文字目まで発言したか
	unsigned int m_textNow;

	// カウント
	unsigned int m_cnt;

	int m_wait;

	TeacherAction* m_teacherAction_p;

public:

	Text(const char* speakerName, int num, int wait, TeacherAction* teacherAction_p);
	~Text();

	inline unsigned int getCnt() { return m_cnt; }

	// 会話を行う
	bool play();

	// 最後までセリフ表示したか
	bool finishText() const;

	// テキストを返す（描画用）
	std::string getText() const;

private:
	void loadNextBlock();
	void setNextText(const int size, char* buff);

};


enum EMOTE {
	NORMAL,	// 通常
	SMILE,	// 笑顔
	ANGRY	// 注意
};

// 教師一覧
static const int TEACHER_SUM = 5;
static const char* TEACHER_LIST[TEACHER_SUM] = {
	"トモチ",
	"ミヤトネ",
	"オワダ",
	"トウノ",
	"タキノ"
};

// 服 10レベルごとに使える服が+1されていく
static const int CLOTH_SUM = 3;
static const char* CLOTH_LIST[CLOTH_SUM] = {
	"",
	"水着",
	"突撃"
};

/*
* 教師
*/
class Teacher {
private:

	// 画像
	std::vector<int> m_normalHandle;
	std::vector<int> m_smileHandle;
	std::vector<int> m_angryHandle;

	const int ANIME_SPEED = 5;
	bool m_animeRepeat;

	// 名前
	const char* m_name;

	// 服
	const char* m_cloth;

	int m_nameIndex;
	int m_clothIndex;

	// キャラを反転描画するか
	bool m_reverseX;

	// セリフ
	Text* m_text;

	int m_handleIndex;

	// 表情
	EMOTE m_emote;

	TeacherAction* m_teacherAction;

	// 経験値
	std::vector<long long int> m_exp;

public:

	Teacher(int nameIndex, int clothIndex);
	~Teacher();

	// ゲッタ
	inline const Text* getText() const { return m_text; }
	inline const TeacherAction* getAction() const { return m_teacherAction; }
	inline bool getReverseX() const { return m_reverseX; }
	inline long long int getExp() const { return m_exp[m_nameIndex]; }
	// Level = exp / 60 / 60 / 60 / 10
	inline long long int getLevel() const { return m_exp[m_nameIndex] / 2160000; }

	// 画像取得
	int getHandle() const;

	// 発言開始
	void setText(int num, int wait, EMOTE emote, bool animeRepeat);

	// 雑談
	void setRandomText();

	// アドバイス
	void setAdviceText();

	void play();

	void jump();

	void quake();

	void setNextTeacher();

	void setNextCloth();

	// 教師変更
	void changeTeacher(int index);

	// 服装変更
	void changeCloth(int index);

	// 経験値獲得
	void addExp(long long int exp) { 
		long long int prevLevel = getLevel();
		m_exp[m_nameIndex] += exp;
		// レベルアップ
		if(prevLevel < getLevel()){
			setText(7, 120, EMOTE::SMILE, true);
		}
	}

};


#endif