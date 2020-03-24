#ifndef GBA_H
#define GBA_H

#include "tl6.h"

// ---------------------------------------------------------------------------
//                       USEFUL TYPEDEFS
// ---------------------------------------------------------------------------
/** An unsigned 32-bit (4-byte) type */
typedef unsigned int u32;

/** An unsigned 16-bit (2-byte) type */
typedef unsigned short u16;

/** An unsigned 8-bit (1-byte) type. Note that this type cannot be written onto RAM directly. */
typedef unsigned char u8;

// ---------------------------------------------------------------------------
//                       Function Prototypes
// ---------------------------------------------------------------------------
// @see draw.c
void waitForVblank(void);
void drawFullScreenImage(const u16 *img);
void delay(int n);
void drawBox(Box box);
void undrawPlayer(Player* p);
void drawFilledRectangle(int row, int column, int width, int height, u16 color);
void drawHollowRectangle(int row, int col, int width, int height, u16 color);
void drawBoo(int row, int col, int width, int height, const u16 *boo);

void drawChar(int row, int col, char ch, u16 color);
void drawString(int row, int col, char *str, u16 color);

// @see tl6.c
void drawBackgroundPortion(int row, int col, int width, int height, const u16 *bg);
Coordinates getNextLocation(int time);
void drawPlayer(Player* p, Coordinates (*nextCoordinates)(int));
int playerWithinBoxBounds(Player p, Box box);
int pixelWithinBoxBounds(Coordinates pixelLocation, Box box);

// ---------------------------------------------------------------------------
//                       MODE3 MACROS
// ---------------------------------------------------------------------------

#define OFFSET(r, c, rowlen) ((c)+(rowlen)*(r))
#define MODE3 3
#define BG2_ENABLE (1<<10)

#define COLOR(r,g,b) ((r) | (g) << 5 | (b) << 10)
#define WHITE COLOR(31,31,31)
#define BLACK 0
#define GREEN COLOR(0, 31, 0)
#define RED COLOR(31, 0, 0)
#define BLUE COLOR(0, 0, 31)

#define SCREEN_WIDTH 240  // this is the width of the GBA emulator
#define SCREEN_HEIGHT 160 // this is the height of the GBA emulator

/* Mode 3 */
extern volatile unsigned short *videoBuffer;      // 0x6000000
#define REG_DISPCNT  *(volatile unsigned short *)0x4000000
#define SCANLINECOUNTER (volatile unsigned short *)0x4000006

typedef struct
{
	const volatile void *src;
	const volatile void *dst;
	u32                  cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER *) 0x040000B0)

// Defines
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_ON (1 << 31)

#define UNUSED_PARAM(param) ((void)((param)))

extern const unsigned char fontdata_6x8[12288];
extern Box boxes[3]; // will be initialized for you

#endif