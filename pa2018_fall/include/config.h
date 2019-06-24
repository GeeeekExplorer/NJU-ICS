#ifndef __PA_CONFIG_H__
#define __PA_CONFIG_H__

// reference implementations, only for debugging, do not submit when defined
//#define NEMU_REF_ALU
//#define NEMU_REF_INSTR


// PA 2


// PA 3
//#define CACHE_ENABLED
#define IA32_SEG             // protect mode enable
#define IA32_PAGE            // virtual memory management is now complete
//#define TLB_ENABLED

// PA 4
#define IA32_INTR            // tells NEMU and Kernel that we are ready for handling exceptions(traps only) and interrupts
#define HAS_DEVICE_TIMER
#define HAS_DEVICE_SERIAL    // the disturbing 'nemu trap output:' tag will be removed
#define HAS_DEVICE_IDE       // the loader will load the elf from the hard disk instead of mem disk
#define HAS_DEVICE_KEYBOARD  // keyboard input
#define HAS_DEVICE_VGA       // we then have display
#define HAS_DEVICE_AUDIO     // audio, this is experimental, need to enable when submit pa-4-3

#endif
