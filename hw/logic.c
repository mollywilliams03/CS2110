#include "logic.h"

void initializeAppState(AppState* appState) {
    // TA-TODO: Initialize everything that's part of this AppState struct here.
    // Suppose the struct contains random values, make sure everything gets
    // the value it should have when the app begins.
    //(appState->avoid)= [{10, 110, 1},
                        //{10, 70, 1},
                        // {10, 50, 1},
                        // {10, 140, 1}];
    (appState->avoid)[0].row = 110;
    (appState->avoid)[0].col = 10;
    (appState->avoid)[0].toDraw = 1;
    (appState->avoid)[1].row = 70;
    (appState->avoid)[1].col = 10;
    (appState->avoid)[1].toDraw = 1;
    (appState->avoid)[2].row = 40;
    (appState->avoid)[2].col = 10;
    (appState->avoid)[2].toDraw = 1;
    (appState->avoid)[3].row = 140;
    (appState->avoid)[3].col = 10;
    (appState->avoid)[3].toDraw = 1;
    appState->score = 0;
    appState->gameOver = 0;
    (appState->player).row = 120;
    (appState->player).col = 120;
    (appState->player).toDraw = 1;
    (appState->doNotAvoid).row = 20;
    (appState->doNotAvoid).col = 70;
    (appState->doNotAvoid).toDraw = 1;
}

static int hit(PlayerPosition player1, PlayerPosition object) {
    int side = 20;

    int topleftx = (object.row);
    int toplefty = (object.col);
    if (toplefty <= (player1.col + side) && toplefty >= (player1.col)) {
        if (topleftx <= (player1.row + side) && topleftx >= (player1.row)) {
            return 1;
        }
    }
    if ((object.col + side) <= (player1.col + side) && (object.col + side) >= (player1.col)) {
        if (topleftx <= (player1.row + side) && topleftx >= (player1.row)) {
            return 1;
        }
    }
    if (toplefty <= (player1.col + side) && toplefty >= (player1.col)) {
        if ((object.row + side) <= (player1.row + side) && (object.row + side) >= (player1.row)) {
            return 1;
        }
    }
    if ((object.col + side) <= (player1.col + side) && (object.col + side) >= (player1.col)) {
        if ((object.row + side) <= (player1.row + side) && (object.row + side) >= (player1.row)) {
            return 1;
        }
    }
    return 0;
}

static int onScreen (int x, int y) {
    if (x < 240 && x > 0 && y < 160 && y > 0) {
        return 1;
    }
    return 0;
}

// TA-TODO: Add any process functions for sub-elements of your app here.
// For example, for a snake game, you could have a processSnake function
// or a createRandomFood function or a processFoods function.
//
// e.g.:
// static Snake processSnake(Snake* currentSnake);
// static void generateRandomFoods(AppState* currentAppState, AppState* nextAppState);

// This function processes your current app state and returns the new (i.e. next)
// state of your application.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow) {
    /* TA-TODO: Do all of your app processing here. This function gets called
     * every frame.
     *
     * To check for key presses, use the KEY_JUST_PRESSED macro for cases where
     * you want to detect each key press once, or the KEY_DOWN macro for checking
     * if a button is still down.
     *
     * To count time, suppose that the GameBoy runs at a fixed FPS (60fps) and
     * that VBlank is processed once per frame. Use the vBlankCounter variable
     * and the modulus % operator to do things once every (n) frames. Note that
     * you want to process button every frame regardless (otherwise you will
     * miss inputs.)
     *
     * Do not do any drawing here.
     *
     * TA-TODO: VERY IMPORTANT! READ THIS PART.
     * You need to perform all calculations on the currentAppState passed to you,
     * and perform all state updates on the nextAppState state which we define below
     * and return at the end of the function. YOU SHOULD NOT MODIFY THE CURRENTSTATE.
     * Modifying the currentAppState will mean the undraw function will not be able
     * to undraw it later.
     */

    AppState nextAppState = *currentAppState;

    for (int i = 0; i < 4; i++) {
        if (hit(currentAppState->player, (currentAppState->avoid)[i])) {
            nextAppState.gameOver = 1;
        }
    }

    if (hit(currentAppState->player, currentAppState->doNotAvoid)) {
        nextAppState.score = currentAppState->score + 1;
        (nextAppState.doNotAvoid).toDraw = 0;
    }
    for (int i = 0; i < 4; i++) {
        if (!hit(currentAppState->player, (currentAppState->avoid)[i]) && onScreen((currentAppState->avoid)[i].row, (currentAppState->avoid)[i].col) == 1) {
                (nextAppState.avoid)[i].col = (nextAppState.avoid)[i].col + 1;
        }
        if (onScreen((currentAppState->avoid)[i].row, (currentAppState->avoid)[i].col) == 0) {
            (nextAppState.avoid)[i].col = 10;
            (nextAppState.avoid)[i].row = randint(20,220);
        }
    }

    if ((currentAppState->doNotAvoid).toDraw == 0) {
        (nextAppState.doNotAvoid).toDraw = 1;
        (nextAppState.doNotAvoid).row = randint(20, 220);
        (nextAppState.doNotAvoid).col = randint(20, 140);
    }


    if (KEY_DOWN(BUTTON_RIGHT, keysPressedNow)) {
        if ((nextAppState.player).row <= 239) {
            (nextAppState.player).row += 2;
        }
    }
    if (KEY_DOWN(BUTTON_LEFT, keysPressedNow)) {
        if ((nextAppState.player).row > 0) {
            (nextAppState.player).row -= 2;
        }
    }
    if (KEY_DOWN(BUTTON_UP, keysPressedNow)) {
        if ((nextAppState.player).col > 0) {
            (nextAppState.player).col -= 2;
        }
    }
    if (KEY_DOWN(BUTTON_DOWN, keysPressedNow)) {
        if ((nextAppState.player).col < 240) {
            (nextAppState.player).col += 2;
        }
    }



    UNUSED(keysPressedBefore);

    return nextAppState;
}
