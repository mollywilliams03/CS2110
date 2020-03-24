#include "gba.h"

/**
 * DO NOT MODIFY THIS FILE/METHOD.
 * 
 * Here we initialize our player and boxes and call
 * the functions required (in order) for you.
 */
int main(void) {
    REG_DISPCNT = MODE3 | BG2_ENABLE;

    // Initializing our player @see tl6.h
    Player player = {
        {SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2},
        BOO_HEIGHT, // same as BOO_WIDTH
    };
    
    drawFullScreenImage(bear);

    while(1) {
        undrawPlayer(&player);

        int allDone = 1;
        // Checking if player is within bounds of any box
        // and updating the .isFilled field of that box
        for (u32 i = 0; i < sizeof(boxes) / sizeof(Box); i++) {
            if (!boxes[i].isFilled) {
                boxes[i].isFilled = playerWithinBoxBounds(player, boxes[i]);
                if (!boxes[i].isFilled) {
                    allDone = 0;
                }
            }
        }

        // If all boxes are drawn..
        if (allDone) {
            drawString(SCREEN_HEIGHT / 2 + 25, SCREEN_WIDTH / 2 - 85, "HAPPY BIRTHDAY BEAR BEARHY!", WHITE);
        }

        // Drawing boxes
        for (u32 i = 0; i < sizeof(boxes) / sizeof(Box); i++) {
            // Filling the background portion if player is withinBoxBounds
            if (boxes[i].isFilled) {
                drawBackgroundPortion(boxes[i].crd.x, boxes[i].crd.y, boxes[i].width, boxes[i].height, bear);
            } else {
                drawFilledRectangle(boxes[i].crd.x, boxes[i].crd.y, boxes[i].width, boxes[i].height, boxes[i].color);
            }
            
        }

        drawPlayer(&player, getNextLocation);
        delay(7); // making our boo invisible for a quick moment!
        waitForVblank();
    }
}
