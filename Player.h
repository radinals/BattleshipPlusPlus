#ifndef __PLAYER__
#define __PLAYER__

#include <vector>
#include <string>

#include "Board.h"

class Player
{
	// atttr
	private:
		Board* PlayerBoard;
		Board* EnemyBoard;
	public:
		std::string id = "Player";

	// methods
	public:
		bool has_no_more_ship();
		ShotStatus shoot_at(size_t x, size_t y);
		Player(Board* PlayerBoard, Board* EnemyBoard);
};
#endif // !__PLAYER__
