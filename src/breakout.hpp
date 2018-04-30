#ifndef BREAKOUT_HPP_
#define BREAKOUT_HPP_

#include "game.hpp"

typedef struct CollisionLayer
{
	std::vector<Rect2D*> colliders; 
};

void initGame(Game&, CollisionLayer&);
void gameLoop(Game&, CollisionLayer&);
void gameCycle(Game&, bool, CollisionLayer&, float&, float&);

#endif
