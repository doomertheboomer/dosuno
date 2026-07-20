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

// TODO: remove gemini test code
extern uint8_t RAM[0x100000];
extern union _bytewordregs_ regs;
extern uint16_t segregs[4];
extern uint16_t ip;
extern void reset86();
extern void exec86(uint32_t execloops);int main() {
    // 1. Reset the CPU state
    reset86(); 

    // 2. Set the CPU registers to our starting address
    segregs[regcs] = 0x1000;
    ip = 0x0100;
    segregs[regss] = 0x1000;
    regs.wordregs[regsp] = 0xFFFE;

    // Calculate the physical memory address (CS * 16 + IP)
    uint32_t base_addr = (segregs[regcs] << 4) + ip;

    // 3. Inject Machine Code into RAM
    // Instruction 1: MOV AX, 0x1234 (Opcode: B8 34 12)
    RAM[base_addr + 0] = 0xB8; 
    RAM[base_addr + 1] = 0x34; // Low byte
    RAM[base_addr + 2] = 0x12; // High byte

    // Instruction 2: HLT (Opcode: F4)
    // This safely stops the Fake86 execution loop
    RAM[base_addr + 3] = 0xF4;

    // 4. Execute the instructions
    // We pass '2' because we injected two instructions.
    exec86(2); 

    // 5. Verify the result
    printf("Execution complete.\n");
    printf("AX Register contains: 0x%04X\n", regs.wordregs[regax]);

    return 0;
}