#include "../includes.h"

extern uint8_t vidmode;
uint8_t extra = 0; // TODO: add proper 80x50 support

void locToPos(uint32_t loc, uint8_t att, uint32_t out[])
{
    uint8_t col, row;
    switch (vidmode)
    {
    case 3:
        col = 80;
        row = 25 + extra; // allows 80x50 or whatever
        break;
    default:
    case 0:
    case 1:
        col = 40;
        row = 25;
        break;
    }
    uint16_t temploc = (loc - att - 0xB8000) / 2; // minus 1 if its an attribute byte
    out[0] = temploc % col;
    out[1] = temploc / col;
}

void updateText(uint32_t loc)
{
    // scuffed fast code here. no ifs!
    uint8_t isAttr = loc % 2;
    uint8_t text = RAM[loc - isAttr];     // if isAttr is 1, then subtract 1 to get text
    uint8_t attr = RAM[loc - isAttr + 1]; // if isAttr is 0, then add 1 to get attr

    // parse attribute
    uint8_t fgColor = attr & 0xF;        // upper 4 bits
    uint8_t bgColor = (attr >> 4) & 0x7; // lower 3 bits
    uint8_t blink = (attr >> 7) & 1;     // first bit
    uint32_t pos[2];                     // [x,y]
    locToPos(loc, isAttr, pos);

    // this portion is vibecoded ansi confuses me
    printf("\033[%d;%dH", pos[1] + 1, pos[0] + 1);
    printf("\033[0");
    if (blink) printf(";5");
    if (fgColor >= 8) printf(";1");
    printf(";%d", 30 + (fgColor & 7));
    printf(";%d", 40 + bgColor);
    printf("m");
    printf("%c", text);

    // printf("write text %c attr 0x%x to 0x%x at pos %d,%d; isAttr = %d\n", text, attr, loc, pos[0], pos[1], isAttr);
}