#include "includes.h"

// get cpu to compile
// TODO: probably put a lot of these in their own files
uint8_t vidmode = 3;
uint8_t updatedscreen = 0;
uint16_t VGA_SC[0x100], VGA_CRTC[0x100], VGA_ATTR[0x100], VGA_GC[0x100];

void writeVGA(uint32_t addr32, uint8_t value) {}
uint8_t readVGA(uint32_t addr32) { return 0xFFFF; }
void vidinterrupt() {}
void portout(uint16_t portnum, uint8_t value) {}
void portout16(uint16_t portnum, uint16_t value) {}
uint8_t portin(uint16_t portnum) {}
uint16_t portin16(uint16_t portnum) { return 0xFFFF; }
void readdisk(uint8_t drivenum, uint16_t dstseg, uint16_t dstoff, uint16_t cyl, uint16_t sect, uint16_t head, uint16_t sectcount) {}
void diskhandler() {}
void timing() {}
uint8_t nextintr() {}

// TODO: remove test file stage 3 direct console write
const uint8_t test_com_file[] = {
    0xB8, 0x00, 0xB8,   // mov ax, 0xB800
    0x8E, 0xC0,         // mov es, ax
    0x26, 0xC6, 0x06, 0x00, 0x00, 0x48, // mov byte [es:0x0000], 'H'
    0x26, 0xC6, 0x06, 0x01, 0x00, 0x0F, // mov byte [es:0x0001], 0x0F
    0xCD, 0x20          // int 20h
};

int main()
{
    reset86();
    segregs[regcs] = 0x1000;
    ip = 0x0100;
    segregs[regss] = 0x1000;
    regs.wordregs[regsp] = 0xFFFE;
    uint32_t base_addr = (segregs[regcs] << 4) + ip;
    memcpy(RAM + base_addr, test_com_file, sizeof(test_com_file));

    // main exec loop
    while (hltstate == 0)
    {
        exec86(1); // execute cpu
        // TODO: terminal handle
    }
    printf("CPU Halted\n");

    return 0;
}