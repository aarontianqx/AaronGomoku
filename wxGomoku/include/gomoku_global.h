#ifndef GOMOKU_GLOBAL_H_INCLUDED
#define GOMOKU_GLOBAL_H_INCLUDED

#include <cassert>

#define TABLESIZE 15
#define BREAK_ON_NULL(_N) if (!(_N)) break;


#define PATTERN_WIN 0
#define PATTERN_L4 1
#define PATTERN_S4 2
#define PATTERN_CL3 3
#define PATTERN_JL3 4
#define PATTERN_S3 5
#define PATTERN_L2 6
#define PATTERN_S2A 7
#define PATTERN_S2B 8
#define PATTERN_S2C 9
#define PATTERN_ONE 10
#define PATTERN_NONE 11

#define PATTERN_D44 12
#define PATTERN_D43 13
#define PATTERN_D33 14
#define PATTERN_ML2 15


#endif // GOMOKU_GLOBAL_H_INCLUDED
