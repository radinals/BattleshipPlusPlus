#include <cstdio>

#ifndef __UTILS__
#define __UTILS__

enum HeadDirection { HeadNorth, HeadWest, HeadSouth, HeadEast };
enum CellStatus { CellEmpty, CellMiss, CellHit, CellShip};
enum ShotStatus { ShotMiss, ShotHit, ShotInvalid };

struct COORD {
	size_t x = 0;
	size_t y = 0;
};

#endif // !__UTILS__
