// This is a minimal C source file that essentially allows the compiler to
// compile "map.gen.h" into its own compilation unit (cos it's big).
//
// No other source file should #include "map.gen.h".

#include "map.h"
#include "map_gen.h"

unsigned char *MapData = MAP_GEN_DATA;
int MapWidth = MAP_GEN_WIDTH;
int MapHeight = MAP_GEN_HEIGHT;
int MapFormat = MAP_GEN_FORMAT;
size_t MapDataSize = sizeof(MAP_GEN_DATA);
