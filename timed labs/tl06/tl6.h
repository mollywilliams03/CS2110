/**
 * @file tl6.h
 * @author Farzam
 * @brief structs for defining the game logic.
 */
#include "images/boo.h"
#include "images/bear.h"

#define PLAYER_MOVES 5

typedef struct {
    int x, y; // starting row, column
} Coordinates;

typedef struct {
    Coordinates crd;
    int size;
} Player;

typedef struct {
    Coordinates crd;
    int width, height;
    volatile unsigned short color;
    int isFilled; // to check if player is withinBoxBounds
} Box;

// this array will be initialized with valid
// player Coordinates for you, DO NOT MODIFY THIS ARRAY.
extern Coordinates playerCoordinates[PLAYER_MOVES];
