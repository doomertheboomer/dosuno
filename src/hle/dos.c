#include "../includes.h"

extern union _bytewordregs_ regs;

// TODO: move these externs into a header file
extern void dosPrint(uint32_t addr);

// close program
void int20Handle() {
    hltstate = 1; // TODO: properly exit to command line
}

void int21Handle() {
    // printf("%x\n", regs.byteregs[regah]);
    switch (regs.byteregs[regah]) {
        case 0x9: // dos print
            dosPrint((segregs[regds] << 4) + regs.wordregs[regdx]);
            break;
        default:
            printf("unhandled dos func 0x%x\n", regs.byteregs[regah]);
    }
}