#ifndef GAME_DRAWER_H_INCLUDED
#define GAME_DRAWER_H_INCLUDED


class Game;
class StudyDrawer;


class GameDrawer {
private:

	const Game* m_game_p;

	StudyDrawer* m_studyDrawer;

public:

	GameDrawer(const Game* game);
	~GameDrawer();

	void draw();

};

#endif