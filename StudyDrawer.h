#ifndef STUDY_DRAWER_H_INCLUDED
#define STUDY_DRAWER_H_INCLUDED

class Study;


class StudyDrawer {
private:

	const Study* m_study_p;

public:

	StudyDrawer(const Study* study);
	~StudyDrawer();

	void setStudy(const Study* study) { m_study_p = study; }

	void draw(int handX, int handY);

};

#endif