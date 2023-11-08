#include <stdexcept>

#include "Fleet.h"

// helps with creating the ShipPiece object, annd adds it to the vector of ships
void
Fleet::add_ship(std::string id, size_t len, size_t x, size_t y, HeadDirection direction)
{
	try {
		this->ships.push_back(ShipPiece(id, len, x, y, direction));

	} catch(std::out_of_range) {
		throw FleetException("ERROR: add_ship(): Ship has invalid coordinates");

	} catch(std::invalid_argument) {
		throw FleetException("ERROR: add_ship(): Ship has invalid direction");

	}
}

// return the ships vector element count
size_t
Fleet::ship_count() {
	return this->ships.size();
}

// get the pointer to a instance of ShipPiece by index in the ships vector
ShipPiece*
Fleet::ship_at_i(size_t index)
{
	try {
		return &this->ships.at(index);

	} catch(std::out_of_range) {
		return nullptr;
	}
}
