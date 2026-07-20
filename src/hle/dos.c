#include "../includes.h"

extern union _bytewordregs_ regs;

// close program
void int20Handle() {
    hltstate = 1; // TODO: properly exit to command line
}

void int21Handle() {
    // printf("%x\n", regs.byteregs[regah]);
    switch (regs.byteregs[regah]) {
        default:
            printf("unhandled dos func 0x%x\n", regs.byteregs[regah]);
    }
}