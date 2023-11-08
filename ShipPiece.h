#ifndef __SHIPPIECE__
#define __SHIPPIECE__

#include <vector>
#include <string>
#include "Utils.h"

class ShipPiece
{
	// atttr
	private:
		COORD start_coord;
		HeadDirection direction;
	public:
		unsigned short len = 0;
		unsigned short hit_count = 0;
		std::string id;
		bool is_sunk = false;
		std::vector<COORD> coordinates;

	// methods
	private:
		void generate_coordinates();

	public:
		ShipPiece(std::string id, int len, size_t x, size_t y, HeadDirection direction);
		void take_hit();
};
#endif // !__SHIPPIECE__
