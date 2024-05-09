#ifndef TEACHER_H_INCLUDED
#define TEACHER_H_INCLUDED

#include <string>
#include <vector>


/*
* ���t�̃A�N�V����
*/
class TeacherAction {
private:

	// �W�����v��
	bool m_jumpFlag;

	// ���W�̂���
	int m_dx, m_dy;

	// ���x
	int m_vy;

	// �U������c�莞��
	int m_quakeCnt;

	// �U���ɂ�邸��
	int m_quakeDx, m_quakeDy;

public:

	TeacherAction();

	// �Q�b�^
	int getDx() const { return m_dx + m_quakeDx; }
	int getDy() const { return m_dy + m_quakeDy; }

	// �Z�b�^
	void setVy(int vy) { m_vy = vy; m_jumpFlag = true; }
	void setQuakeCnt(int cnt) { m_quakeCnt = cnt; }

	void init();

	void play();

};


/*
* ����
*/
class Text {
private:

	// �����\���̑��� 1���ő�
	const unsigned int TEXT_SPEED = 5;
	unsigned int m_textSpeed;

	// �Z���t
	std::string m_text;

	// �t�@�C���|�C���^
	int m_fp;

	// �����҂̖��O
	std::string m_speakerName;

	// ���������ڂ܂Ŕ���������
	unsigned int m_textNow;

	// �J�E���g
	unsigned int m_cnt;

	int m_wait;

	TeacherAction* m_teacherAction_p;

public:

	Text(const char* speakerName, int num, int wait, TeacherAction* teacherAction_p);
	~Text();

	inline unsigned int getCnt() { return m_cnt; }

	// ��b���s��
	bool play();

	// �Ō�܂ŃZ���t�\��������
	bool finishText() const;

	// �e�L�X�g��Ԃ��i�`��p�j
	std::string getText() const;

private:
	void loadNextBlock();
	void setNextText(const int size, char* buff);

};


enum EMOTE {
	NORMAL,	// �ʏ�
	SMILE,	// �Ί�
	ANGRY	// ����
};

// ���t�ꗗ
static const int TEACHER_SUM = 5;
static const char* TEACHER_LIST[TEACHER_SUM] = {
	"�g���`",
	"�~���g�l",
	"�I���_",
	"�g�E�m",
	"�^�L�m"
};

// �� 10���x�����ƂɎg���镞��+1����Ă���
static const int CLOTH_SUM = 3;
static const char* CLOTH_LIST[CLOTH_SUM] = {
	"",
	"����",
	"�ˌ�"
};

/*
* ���t
*/
class Teacher {
private:

	// �摜
	std::vector<int> m_normalHandle;
	std::vector<int> m_smileHandle;
	std::vector<int> m_angryHandle;

	const int ANIME_SPEED = 5;
	bool m_animeRepeat;

	// ���O
	const char* m_name;

	// ��
	const char* m_cloth;

	int m_nameIndex;
	int m_clothIndex;

	// �L�����𔽓]�`�悷�邩
	bool m_reverseX;

	// �Z���t
	Text* m_text;

	int m_handleIndex;

	// �\��
	EMOTE m_emote;

	TeacherAction* m_teacherAction;

	// �o���l
	std::vector<long long int> m_exp;

public:

	Teacher(int nameIndex, int clothIndex);
	~Teacher();

	// �Q�b�^
	inline const Text* getText() const { return m_text; }
	inline const TeacherAction* getAction() const { return m_teacherAction; }
	inline bool getReverseX() const { return m_reverseX; }
	inline long long int getExp() const { return m_exp[m_nameIndex]; }
	// Level = exp / 60 / 60 / 60 / 10
	inline long long int getLevel() const { return m_exp[m_nameIndex] / 2160000; }

	// �摜�擾
	int getHandle() const;

	// �����J�n
	void setText(int num, int wait, EMOTE emote, bool animeRepeat);

	// �G�k
	void setRandomText();

	// �A�h�o�C�X
	void setAdviceText();

	void play();

	void jump();

	void quake();

	void setNextTeacher();

	void setNextCloth();

	// ���t�ύX
	void changeTeacher(int index);

	// �����ύX
	void changeCloth(int index);

	// �o���l�l��
	void addExp(long long int exp) { 
		long long int prevLevel = getLevel();
		m_exp[m_nameIndex] += exp;
		// ���x���A�b�v
		if(prevLevel < getLevel()){
			setText(7, 120, EMOTE::SMILE, true);
		}
	}

};


#endif