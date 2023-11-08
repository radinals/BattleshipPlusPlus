#include <iostream>
#include <random>
#include <map>

#include "Utils.h"
#include "ShipPiece.cpp"
#include "Fleet.cpp"
#include "Board.cpp"
#include "Player.cpp"

// the pieces to be used, id , len
std::map<std::string, int> game_pieces{
	{"Carrier",    5},
	{"Battleship", 4},
	{"Cruiser",    3},
	{"Submarine",  3},
	{"Destroyer",  2}
};

// characters to represent things on the board
struct BoardChar {
	const char CellEmpty = ' ';
	const char CellMiss  = '-';
	const char CellHit   = 'X';
	const char CellShip  = '#';
};

BoardChar BChar;

// it's not great.. but it works:)
const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXY";
const std::string numbers = "   1   2   3   4   5   6   7   8   9   10";
const std::string cell_separator = " | ";
const std::string line_separator = "----";
const size_t board_xy_max = 10;

// macro to clear the terminal
#ifdef _WIN32
	#define clear_screen system("cls");
#else
	#define clear_screen system("clear");
#endif



// random number generator, in a range of max to max (including)
unsigned int
rand_range(unsigned int min, unsigned int max)
{
	// random number generator, from /dev/urandom. used for the seed.
	std::random_device rd;

	// >=c++11 32bit pseudo-random number generator.
	std::mt19937 rng(rd());

	// range of numbers between min & max.
	std::uniform_int_distribution<unsigned int> uni(min,max);

	return uni(rng);
}

// methods to print out stuff

void
printout(std::string s) {
	std::cout << s;
	std::cout.flush();
}

void
printout(char s) {
	std::cout << s;
	std::cout.flush();
}


void
printout(long long s) {
	std::cout << s;
	std::cout.flush();
}

// again, not great.. but it works:)
void
draw_board(Board* board, bool hide_ships)
{

	printout("\n  ");
	for(size_t x=0; x < board_xy_max; x++)
		printout(line_separator);
	printout("\n");

	for(size_t y=0; y < board_xy_max; y++) {
		printout(letters.at(y));
		for(size_t x=0; x < board_xy_max; x++) {
			CellStatus* cell_ptr = board->cell_stat(x,y);
			printout(" | ");
			switch (*cell_ptr) {
				case CellShip: {
					if (hide_ships)
						printout(BChar.CellEmpty);
					else
						printout(BChar.CellShip);
					break;
				}
				case CellHit:
					printout(BChar.CellHit);
					break;
				case CellMiss:
					printout(BChar.CellMiss);
					break;
				default:
					printout(BChar.CellEmpty);
					break;

			}
		}
		printout(" | ");
		printout("\n  ");
		for(size_t x=0; x < board_xy_max; x++)
			printout(line_separator);
		printout("\n");
	}
	printout(numbers + "\n");
}

void
get_coord(COORD* coord, HeadDirection* direction, std::string id, size_t len)
{
	char c, dir_c;
	size_t x, y;

	printout("Enter Starting Coordinates and the direction for your " + id + "(" + std::to_string(len) + ")" ": ");

	scanf("%c %zu %c", &c, &x, &dir_c);
	fflush(stdin);

	// only accepts letters (insensitive) from a to z
	if ((tolower(c) < 'a' && tolower(c) > 'z'))
		throw std::invalid_argument("ERROR: get_coord(): Invalid argument");

	coord->x = x-1;

	// 'a' - 'a' = 0 , 'b' - 'a' = 1, ...
	coord->y = tolower(c) - 'a';

	// check if coordinates is out of bounds
	if (coord->x > board_xy_max-1 && coord->y > board_xy_max-1)
		throw std::invalid_argument("ERROR: get_coord(): Invalid argument");

	// get the direction
	switch (tolower(dir_c)) {
		case 'n':
			*direction = HeadNorth;
			break;
		case 'e':
			*direction = HeadEast;
			break;
		case 's':
			*direction = HeadSouth;
			break;
		case 'w':
			*direction = HeadWest;
			break;
		default:
			throw std::invalid_argument("ERROR: get_coord(): Invalid argument");
	}

}

void
get_user_fleet(Board* board)
{
	for(const auto& game_piece : game_pieces) {

		std::string id  = game_piece.first;
		size_t len = game_piece.second;

		COORD coord;
		HeadDirection direction;

		while(true) {
			try {
				clear_screen;
				printout("Player's Fleet:\n");
				draw_board(board, false);
				get_coord(&coord, &direction, id, len);
				board->add_ship_to_fleet(id, len, coord.x, coord.y, direction);

			} catch (...) { continue; }

			break;
		}
	}
}

void
generate_enemy_fleet(Board* board)
{

	for(const auto& game_piece : game_pieces) {

		// get the id and len from the map
		std::string id  = game_piece.first;
		size_t len = game_piece.second;

		COORD coord;
		HeadDirection direction;

		while(true) {
			try {
				// randomly choose the coordinates
				coord.x = rand_range(0, board_xy_max-1);
				coord.y = rand_range(0, board_xy_max-1);

				// randomly choose the direction
				size_t dir = rand_range(1, 4);
				switch (dir) {

					case 1:
						direction = HeadNorth;
						break;
					case 2:
						direction = HeadEast;
						break;
					case 3:
						direction = HeadSouth;
						break;
					case 4:
						direction = HeadWest;
						break;
					default:
						exit(-1);
				}

				board->add_ship_to_fleet(id, len, coord.x, coord.y, direction);

			} catch (...) { continue; }

			break;
		}
	}
}

COORD
user_take_shot()
{
	COORD coord;
	char c;
	size_t x, y;

	while(true) {
		try {
			printout("Enter Where You Want to SHOOT :" );

			scanf("%c %zu", &c, &x);
			fflush(stdin);

			if ((tolower(c) < 'a' && tolower(c) > 'z'))
				throw std::invalid_argument("ERROR: get_coord(): Invalid argument");

			coord.x = x-1;

			// 'a' - 'a' = 0 , 'b' - 'a' = 1, ...
			coord.y = tolower(c) - 'a';

			if (coord.x > board_xy_max-1 && coord.y > board_xy_max-1)
				throw std::invalid_argument("ERROR: get_coord(): Invalid argument");

		} catch(...) {continue;}
		break;
	}
	return coord;
}


int
main()
{
	Board player_board = Board(board_xy_max, board_xy_max);
	Board enemy_board = Board(board_xy_max, board_xy_max);

	get_user_fleet(&player_board);
	generate_enemy_fleet(&enemy_board);

	Player Human = Player(&player_board, &enemy_board);
	Player Enemy = Player(&enemy_board, &player_board);

	while(true) {

		// check if any player has no remaining ships on the board
		if (Human.has_no_more_ship()) {
			printout("Game Over Player Lose\n");
			break;
		} else if (Enemy.has_no_more_ship()) {
			printout("Game Over Player Wins\n");
			break;
		}

		// draw the boards
		clear_screen;

		printout("Player's Fleet:\n");
		draw_board(&player_board, false);

		printout('\n');

		printout("BattleView:\n");
		draw_board(&enemy_board, true);

		// input loop, get coordinates from user where to shoot
		while(true) {
			COORD coord = user_take_shot();
			switch(Human.shoot_at(coord.x, coord.y)) {
					case ShotHit:
						printout("A Hit!\n");
						break;
					case ShotMiss:
						printout("A Miss!\n");
						break;
					default:
						printout("Invalid Coordinates!\n");
						continue;
			}
			break;
		}

		// run the RNG for the enemy
		while(true) {
			switch(Enemy.shoot_at(rand_range(0, board_xy_max), rand_range(0, board_xy_max))) {
					case ShotHit:
						printout("A Hit!\n");
						break;
					case ShotMiss:
						printout("A Miss!\n");
						break;
					default:
						continue;
			}
			break;
		}
	}

	return 0;
}
