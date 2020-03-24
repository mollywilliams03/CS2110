/**
 * @file tl6.c
 * @author Molly Williams
 * @brief Timed Lab 6 - Spring 2019
 *
 * DO NOT MODIFY THE FOLLOWING #include(s).
 * DO NOT ADD ANY GLOBAL VARIABLES.
 * DO NOT MODIFY ANY OTHER FILES BESIDES tl6.c
 */
#include "gba.h"

/**
 * @brief Use DMA to draw only a portion of the background image. This porition should be a rectangle
 * with the top left starting at (row, col) and with the corresponding width and height. The background
 * is guaranteed to be 240x160.
 *
 * @param row the starting row of the box
 * @param col the starting column of the box
 * @param width the width of this box
 * @param height the height of this box
 * @param bg ENTIRE background image passed in
 */
void drawBackgroundPortion(int row, int col, int width, int height, const u16 *bg) {
    for (int r = row; r < row + height; r++) {
        DMA[3].src = bg + OFFSET(r, col, 240);
        DMA[3].dst = videoBuffer + OFFSET(r, col, 240);
        DMA[3].cnt = width | DMA_ON | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT;
    }
}

// *
//  * @brief Use the counter to get the next location from
//  * the playerCoordinates array. If the index is out of the bounds
//  * of the array, return the coordinate 0,0!
//  *
//  * @param counter the current count of the number of jumps
//  *        the player has made so far
//  * @return the coordinates of the next location

Coordinates getNextLocation(int counter) {
    Coordinates next;
    if (counter >= 5) {
        next.x = 0;
        next.y = 0;
    } else {
        next.x = playerCoordinates[counter].x;
        next.y = playerCoordinates[counter].y;
    }
    UNUSED_PARAM(counter);
    UNUSED_PARAM(next);
    return next;
}

/**
 * @brief Use nextCoordinates to get the next location
 * of the player, passing in the number of times the player has
 * drawn so far, which you should keep track of in this function.
 * Then, draw the player at the next location using the drawBoo function.
 *
 * The drawBoo function is defined as:
 *      void drawBoo(int row, int col, int width, int height, const u16 *boo)
 *
 * @param p the player to be drawn at the next coordinates
 * @param nextCoordinates the function to get the next coordinates
 */
void drawPlayer(Player* p, Coordinates (*nextCoordinate)(int)) {
    // UNUSED_PARAM(p);
    UNUSED_PARAM(nextCoordinate);
    static int count = 0;
    Coordinates next = getNextLocation(count);
    (p->crd).x = next.x;
    (p->crd).y = next.y;
    drawBoo((p->crd).x, (p->crd).y, p->size, p->size, boo);
    count++;
}

/**
 * @brief function to check if a player is overlapping with a box.
 *
 * This is essentially checking for a collision between the player
 * and the box.
 *
 * @param p the player
 * @param box the box
 * @return 1 if there is a collison, 0 if not
 */
int playerWithinBoxBounds(Player p, Box box) {
    // UNUSED_PARAM(p);
    // UNUSED_PARAM(box);
    int side = p.size;

    int topleftx = (box.crd).x;
    int toplefty = (box.crd).y;
    if (toplefty <= ((p.crd).y + side) && toplefty >= ((p.crd).y)) {
        if (topleftx <= ((p.crd).x + side) && topleftx >= ((p.crd).x)) {
            return 1;
        }
    }
    if (((box.crd).y + side) <= (((p.crd).y) + side) && ((box.crd).y + side) >= (p.crd).y) {
        if (topleftx <= ((p.crd).x + side) && topleftx >= ((p.crd).x)) {
            return 1;
        }
    }
    if (toplefty <= ((p.crd).y + side) && toplefty >= ((p.crd).y)) {
        if (((box.crd).x + side) <= ((p.crd).x + side) && ((box.crd).x + side) >= (p.crd).x) {
            return 1;
        }
    }
    if (((box.crd).y + side) <= (((p.crd).y) + side) && ((box.crd).y + side) >= (p.crd).y) {
        if (((box.crd).x + side) <= ((p.crd).x + side) && ((box.crd).x + side) >= ((p.crd).x)) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief OPTIONAL helper function for playerWithinBoxBounds
 * that just checks if a single location is inside a box.
 *
 * @param pixelLocation the single location being checked
 * @param box the box pixelLocation is being checked against
 * @return 1 if true, 0 if false
 */
int pixelWithinBoxBounds(Coordinates pixelLocation, Box box) {
    UNUSED_PARAM(pixelLocation);
    UNUSED_PARAM(box);
    return 0;
}
