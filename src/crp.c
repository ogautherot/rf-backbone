/*
 * crp.c
 * Source file to create CRP word expected by Code Red linker
 */

#include <stdint.h>

//#ifdef __CODE_RED
//#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
extern const uint32_t CRP_WORD;

__attribute__ ((__used__, section(".crp"))) const uint32_t CRP_WORD = 0xffffffff ;

//#endif
