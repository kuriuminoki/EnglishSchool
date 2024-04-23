#ifndef GAME_DRAWER_H_INCLUDED
#define GAME_DRAWER_H_INCLUDED


class Game;


class GameDrawer {
private:

	const Game* m_game_p;

public:

	GameDrawer(const Game* game);
	~GameDrawer();

	void draw();

};

#endif