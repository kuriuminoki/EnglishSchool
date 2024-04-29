#include "Study.h"
#include "StudyDrawer.h"

#include "DxLib.h"


StudyDrawer::StudyDrawer(const Study* study) {
	m_study_p = study;
}

StudyDrawer::~StudyDrawer() {

}

void StudyDrawer::draw(int handX, int handY) {
	m_study_p->draw(handX, handY);
}