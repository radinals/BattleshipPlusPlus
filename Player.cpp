#include "Player.h"
#include "ShipPiece.h"

// just shoots at the enemy
ShotStatus
Player::shoot_at(size_t x, size_t y)
{
	return EnemyBoard->shoot_at(x, y);
}


// check the amount of ships on board and the ships that has the amount of ships
// that has been lost (sunk). the .ship_lost attribute is incremented in the shoot_at()
// method in Board()
bool
Player::has_no_more_ship()
{
	if (this->PlayerBoard->fleet.ship_count() == this->PlayerBoard->fleet.ships_lost)
		return true;
	return false;
}

Player::Player(Board* PlayerBoard, Board* EnemyBoard)
{
	this->PlayerBoard = PlayerBoard;
	this->EnemyBoard = EnemyBoard;
}
