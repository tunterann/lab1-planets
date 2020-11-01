
#ifndef _GAME_PLANETS_
#define _GAME_PLANETS_

#include "./serialize.hpp"

struct gportal : public portal
{
	bool visited = false;
};

class planet_game
{
private:
	vector<struct gportal> portals;
	int cur_planet = 0;
	bool init = false;

	bool set_visited(int);

public:
	planet_game(struct portal *, int);
	int start(void);
};

#endif