#include "includes.h"

// get cpu to compile
// TODO: probably put a lot of these in their own files
uint8_t vidmode = 0;
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

// TODO: remove test file
const uint8_t test_com_file[] = {
    0xB4, 0x09,       // mov ah, 09h    -> DOS function: Print String
    0xBA, 0x08, 0x01, // mov dx, 0108h  -> Memory offset where string starts (0x100 base + 8 byte header offset)
    0xCD, 0x21,       // int 21h        -> Execute DOS service
    0xF4,             // hlt            -> Halt CPU
    // --- The String Data below (Offset 0x0108 onwards) ---
    0x68, 0x65, 0x6C, 0x6C, 0x6F, 0x2C, 0x20, 0x77, 0x6F, 0x72, 0x6C, 0x64, // "hello, world"
    0x0D, 0x0A,                                                             // Carriage Return (\r), Line Feed (\n)
    0x24                                                                    // '$' character (The required DOS string terminator)
};

extern uint8_t RAM[0x100000];
extern union _bytewordregs_ regs;
extern uint16_t segregs[4];
extern uint16_t ip;
extern uint8_t hltstate;
extern void reset86();
extern void exec86(uint32_t execloops);

// TODO: remove gemini test code
int main()
{
    reset86();
    segregs[regcs] = 0x1000;
    ip = 0x0100;
    segregs[regss] = 0x1000;
    regs.wordregs[regsp] = 0xFFFE;
    uint32_t base_addr = (segregs[regcs] << 4) + ip;
    memcpy(RAM + base_addr, test_com_file, 23);

    // main exec loop
    while (hltstate == 0)
    {
        exec86(1);
    }
    printf("CPU Halted\n");

    return 0;
}