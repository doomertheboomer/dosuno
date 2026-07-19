#include <stdio.h>
#include <stdint.h>

// get cpu to compile
// TODO: probably put a lot of these in their own files
uint8_t vidmode = 0;
uint8_t updatedscreen = 0;
uint16_t VGA_SC[0x100], VGA_CRTC[0x100], VGA_ATTR[0x100], VGA_GC[0x100];

void writeVGA(uint32_t addr32, uint8_t value) {}
uint8_t readVGA (uint32_t addr32) { return 0xFFFF; }
void vidinterrupt() {}
void portout(uint16_t portnum, uint8_t value) {}
void portout16(uint16_t portnum, uint16_t value) {}
uint8_t portin(uint16_t portnum) {}
uint16_t portin16(uint16_t portnum) { return 0xFFFF; }
void readdisk (uint8_t drivenum, uint16_t dstseg, uint16_t dstoff, uint16_t cyl, uint16_t sect, uint16_t head, uint16_t sectcount) {}
void diskhandler() {}
void timing() {}
uint8_t	nextintr() {}

int main() {
    printf("hello fake86 core\n");
    return 0;
}