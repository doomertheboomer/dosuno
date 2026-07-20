#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "cpu/cpu.h"

// cpu globals
extern uint8_t RAM[0x100000];
extern union _bytewordregs_ regs;
extern uint16_t segregs[4];
extern uint16_t ip;
extern uint8_t hltstate;
extern void reset86();
extern void exec86(uint32_t execloops);