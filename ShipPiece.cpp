#include <stdexcept>

#include "ShipPiece.h"

// this generates all the coordinates that the ship
// will occupy in the board.
void
ShipPiece::generate_coordinates()
{
	COORD tmp;

	// set it to long long, because size_t is unsigned
	// need it to check for negative values
	long long tmp_x, tmp_y;

	tmp.x = this->start_coord.x;
	tmp.y = this->start_coord.y;

	// add the starting coordinate
	this->coordinates.push_back(tmp);

	// generate the rest
	for(size_t i=0; i < this->len-1; i++) {

		switch(this->direction) {
			case HeadNorth:
				tmp.y-=1;
				break;
			case HeadWest:
				tmp.x-=1;
				break;
			case HeadEast:
				tmp.x+=1 ;
				break;
			case HeadSouth:
				tmp.y+=1;
				break;
			default:
				throw std::invalid_argument("ShipPiece(): Invalid Direction");
     		}

		if (tmp.x < 0 || tmp.y < 0)
			throw std::out_of_range("ShipPiece(), generate_coordinates(): x and y out of range");


		this->coordinates.push_back(tmp);
	}
}


// increment the hit count, and check if the ship is sunk (hit_count >= len)
void
ShipPiece::take_hit()
{
	this->hit_count++;
	this->is_sunk = (this->hit_count >= this->len);
}

// constructor
ShipPiece::ShipPiece(std::string id, int len, size_t x, size_t y, HeadDirection direction)
{
	this->id = id;
	this->len = len;
	this->start_coord.x = x;
	this->start_coord.y = y;
	this->direction = direction;

	generate_coordinates();
}
