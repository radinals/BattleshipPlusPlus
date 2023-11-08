#ifndef __FLEET__
#define __FLEET__

#include <string>
#include <vector>
#include <exception>

#include "ShipPiece.h"

// not sure why i made this, but practice makes perfect
class
FleetException : public std::exception
{
    private:
	    char const * message;

    public:
	    FleetException(char const * msg) : message(msg) {}
	    char const * what () { return message; }
};

class Fleet
{
	public:
		std::vector <ShipPiece> ships;
		size_t ships_lost = 0;

	public:

		size_t ship_count();
		ShipPiece* ship_at_i(size_t index);
		void add_ship(std::string id, size_t len, size_t x, size_t y, HeadDirection direction);
};

#endif // !__FLEET__
