#include <vector>
#include <string>
#include <stdexcept>

#include "Board.h"

// get a pointer to a cell in the board
CellStatus*
Board::cell_stat(size_t x, size_t y)
{
	try {
		return &this->Cells.at(y).at(x);

	} catch (std::out_of_range) {
		return nullptr;
	}
}

// reset/initialize the board to be empty cells
void
Board::init_empty_board()
{
	this->Cells = {};
	for (size_t y=0; y < this->board_size.y; y++) {
		std::vector<CellStatus> tmp;
		for (size_t x=0; x < this->board_size.x; x++)
			tmp.push_back(CellEmpty);
		this->Cells.push_back(tmp);
	}

}

// the shooting action
ShotStatus
Board::shoot_at(size_t x, size_t y)
{

	CellStatus* cell_ptr = cell_stat(x,y);

	if (cell_ptr == nullptr) return ShotInvalid;

	// if the cell is empty set the cell to miss
	if(*cell_ptr == CellEmpty) {
		*cell_ptr = CellMiss;
		return ShotMiss;

	// if the cell is a ship set the cell to miss
	} else if(*cell_ptr == CellShip) {

		// keeps track of the ship index
		size_t i = 0;

		for(ShipPiece s : this->fleet.ships) {
			for (COORD coord : s.coordinates) {
				if (coord.x == x && coord.y == y) {

					this->fleet.ship_at_i(i)->take_hit();

					// this is true if take_hit() increment the
					// hit count >= ship len
					if (this->fleet.ship_at_i(i)->is_sunk)
						this->fleet.ships_lost++;
				}
			}
			i++;
		}

		*cell_ptr = CellHit;
		return ShotHit;
	}

	return ShotInvalid;

}

// place a ship on the board
// the cells it occcupies are set to CellShip
void
Board::place_ship(ShipPiece* s)
{
	std::vector<std::vector<CellStatus>> tmp = this->Cells;

	for(COORD coord : s->coordinates) {
		// CellStatus* cell_ptr = cell_stat(coord.x, coord.y);
		try {
			if (tmp.at(coord.y).at(coord.x) == CellEmpty)
				tmp.at(coord.y).at(coord.x) = CellShip;
			else {
				throw std::invalid_argument(
					"ERROR: Board(), place_ship(): Ship has an invalid coordinate"
				);
			}
		} catch (...) {
			throw std::invalid_argument(
				"ERROR: Board(), place_ship(): Ship has an invalid coordinate"
			);
		}
	}

	this->Cells = tmp;
}

// creates a ship and add it to the board and fleet
void
Board::add_ship_to_fleet(std::string id, size_t len, size_t x, size_t y, HeadDirection direction) {
	if (x > this->board_size.x-1  || y > board_size.y-1)
		throw std::out_of_range("ERROR: Board(), add_ship_to_fleet(): Coordinate out of range");

	this->fleet.add_ship(id, len, x, y, direction);

	try {
		place_ship(this->fleet.ship_at_i(this->fleet.ship_count()-1));

	} catch (...) {
		throw std::out_of_range("ERROR: Board(), add_ship_to_fleet(): Coordinate out of range");
	}
}

// creates a board in x,y, size
Board::Board(size_t x, size_t y)
{
	this->board_size.x = x;
	this->board_size.y = y;
	this->fleet = Fleet();

	init_empty_board();
}
