#ifndef CONTROL_H_INCLUDED
#define CONTROL_H_INCLUDED
//////�L�[�{�[�h����̓��͂��i�[���A�Ԃ��֐��Q///////////

int updateKey();

void mouseLimit(int& hand_x, const int hand_y);
//���N���b�N�̏��
void mouseClick();
int leftClick();
int rightClick();

// W�L�[�i��L�[�j
int controlW();

// S�L�[�i���L�[�j
int controlS();

// A�L�[�i���L�[�j
int controlA();

// D�L�[�i�E�L�[�j
int controlD();

// F�L�[�i�X�L�������j
int controlF();

// Q�L�[�i�ꎞ��~�j
int controlQ();

// Z�L�[�i�C�x���g�X�L�b�v�j
int controlZ();

//FPS�\���̃I���I�t
int controlDebug();

//�X�y�[�X�L�[
int controlSpace();

// ��Shift�L�[
int controlLeftShift();

// �EShift�L�[
int controlRightShift();

//ESC�L�[�F�Q�[���I��
int controlEsc();

#endif