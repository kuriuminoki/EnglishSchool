#include "Study.h"
#include "StudyDrawer.h"

#include "DxLib.h"


StudyDrawer::StudyDrawer(const Study* study) {
	m_study_p = study;
}

StudyDrawer::~StudyDrawer() {

}

void StudyDrawer::draw(int handX, int handY) {
	if (m_study_p != nullptr) {
		m_study_p->draw(handX, handY);
	}
}