#ifndef __BOARD__
#define __BOARD__

#include "Utils.h"
#include "ShipPiece.h"
#include "Fleet.h"

class Board
{
	// atttr
	private:
		std::vector<std::vector<CellStatus>> Cells;
	public:
		Fleet fleet;
		COORD board_size;

	// methods
	private:
		void init_empty_board();

	public:
		void place_ship(ShipPiece* s);
		ShotStatus shoot_at(size_t x, size_t y);
		CellStatus* cell_stat(size_t x, size_t y);
		void add_ship_to_fleet(std::string id, size_t len, size_t x, size_t y, HeadDirection direction);
		Board(size_t x, size_t y);
};

#endif // !__BOARD__
