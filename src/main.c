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

// TODO: remove test file stage 4 dos print
const uint8_t test_com_file[] = {
    0xB4, 0x09,       // mov ah, 0x09
    0xBA, 0x09, 0x01, // mov dx, 0x0109  (offset of message)
    0xCD, 0x21,       // int 0x21
    0xCD, 0x20,       // int 0x20  (terminate)
    'H', 'e', 'l', 'l', 'o', ' ', 'f', 'r', 'o', 'm', ' ', 'D', 'O', 'S', '!', '$'};

int main()
{
    printf("\033[2J\033[H"); // clear screen
    reset86();
    segregs[regcs] = 0x1000;
    segregs[regds] = 0x1000;
    segregs[reges] = 0x1000;
    segregs[regss] = 0x1000;
    ip = 0x0100;
    regs.wordregs[regsp] = 0xFFFE;
    uint32_t base_addr = (segregs[regcs] << 4) + ip;
    memcpy(RAM + base_addr, test_com_file, sizeof(test_com_file));
    // for (int i = 0; i < 25; i++)
    //     printf("%02X ", RAM[0x10100 + i]);
    // main exec loop
    while (hltstate == 0)
    {
        exec86(1); // execute cpu
        // TODO: terminal handle
    }
    printf("\nCPU Halted\n");

    return 0;
}