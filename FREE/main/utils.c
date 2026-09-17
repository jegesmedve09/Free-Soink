#include <kernel.h>
#include <sifrpc.h>
#include <iopcontrol.h>
#include <loadfile.h>
#include <iopheap.h>
#include <libpwroff.h>
#include <sbv_patches.h>
#include <stdint.h>
#include <timer.h>
#include <sys/stat.h>
#include <kernel.h>
#include <sifrpc.h>
#include <libcdvd.h>
#include <loadfile.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "utils.h"

#define PORTABLE_ADDRESS    0x01EFF800

#define DEV_EXIST(path) (stat(path, &(struct stat){0}) == 0)

//define MY_THOUGHTS_WHILE_MAKING_THIS_PIECE_OF_SOFTWARE "https://youtu.be/iL1HvAu8V1w?si=M3bgF1X83DeaJ30o"

void FuckAroundSilentlyMs(int miliseconds)
{
    unsigned int start, now;

    __asm__ volatile("mfc0 %0, $9" : "=r"(start));

    while (1)
    {
        __asm__ volatile("mfc0 %0, $9" : "=r"(now));
        if ((now - start) >= (unsigned int)(miliseconds * 147456))
            break;
    }
}

/*
int get_random_in_range(int from, int to)
{
    if (from > to)
    {
        int temp = from;
        from = to;
        to = temp;
    }

    u32 entropy = 0;

    u32 count;
    __asm__ volatile ("mfc0 %0, $9" : "=r"(count));
    entropy ^= count;
    __asm__ volatile ("mfc0 %0, $9" : "=r"(count));
    entropy ^= (count << 13) | (count >> 19);
    __asm__ volatile ("mfc0 %0, $9" : "=r"(count));
    entropy ^= count ^ (count << 7) ^ (count >> 11);


    volatile u32 stack_ptr;
    __asm__ volatile ("move %0, $sp" : "=r"(stack_ptr));
    entropy ^= stack_ptr ^ (stack_ptr >> 8);


    entropy ^= (u32)(uintptr_t)&get_random_in_range;


    extern GSGLOBAL *gsGlobal;
    if (gsGlobal)
    {
        u64 csr = *GS_CSR;
        entropy ^= (u32)csr ^ (u32)(csr >> 32);
    }

    u64 timer = GetTimerSystemTime();
    entropy ^= (u32)timer ^ (u32)(timer >> 32);


    volatile u32 dummy = entropy & 0xFF;
    u32 loop_count = 0;
    for (volatile u32 i = 0; i < 128 + dummy; i++)
    {
        loop_count += i ^ entropy;
    }
    entropy ^= loop_count ^ (loop_count << 5) ^ (loop_count >> 17);

    u32 x = entropy;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;

    __asm__ volatile ("mfc0 %0, $9" : "=r"(count));
    x ^= count;

    if (x == 0) x = 0x80000001;

    u32 range = (u32)(to - from + 1);
    return from + (int)(x % range);
}
*/
char *path_portableinator(const char *path)
{
    static char result[2048];

    strncpy(result, (char*)PORTABLE_ADDRESS, sizeof(result) - 1);
    result[sizeof(result) - 1] = '\0';
    strncat(result, path, sizeof(result) - strlen(result) - 1);
    result[sizeof(result) - 1] = '\0';
    return result;
}
unsigned int read_count(void)
{
    unsigned int c;
    __asm__ volatile("mfc0 %0, $9" : "=r"(c));
    return c;
}


// This is the only part of the entire codebase which is made from
// Stalinium and is blessed by Sticks the Badger...
// Poor Silver, he already knows how much of a disaster this is gonna be...

/*
   [PSYCHIC FORECAST: FUTURE STATUS = OBLITERATED]
   Silver: "No, wait! The timeline... its tearing apart! I can see the memory 
           registers collapsing into a singularity of raw, unshielded noise! 
           Sticks, what did you DO to the IOP?!"
   Sticks: "I saved us from the microwave beams, future boy! Drink the swamp 
            water and listen to the GS!"
*/
// we need this so Sticks doesnt realize we are co-working
// with the....shit..Sticks in my room...with her boomerang...
// fuck...
#define POINTER u32*
POINTER get_random_address_from_Sticks_the_badger() {

    // Sticks secret location of the Randomium in her room....
    u32 raw_noise = *(volatile u32*)0x10000000;

    // Sticks-proof, no aliens or mole people were harmed
    u32 safe_ram_mask = 0x01EFFFFF;
    u32 final_address = 0x00100000 + (raw_noise & safe_ram_mask);

    // 3. Return the pointer directly. NO RAM WASTED!
    return (u32*)final_address;

    /*
    "Do NOT trust this function! It doesn't fetch memory
    from 'Sticks knows where'-it fetches it from the government!
    That pointer isn't random; it's a direct psychic link tracking
    your hardware inputs! Every time you call a uninitialized
    32-bit address on the Emotion Engine, a data-mining satellite
    replaces your level data with a secret frequency meant to turn
    your Chao into tiny mind-control spies! If you let that pointer
    dereference, Dr. Eggman will use the PS2's sub-atomic laser grid
    to reprogram your memory card and replace your breakfast waffles
    with tiny, listening devices shaped like violins! I buried my
    source code in a hole behind my burrow, wrapped in tinfoil, just
    to keep the rendering bots from reading my thoughts!"
    -Sticks "what...the..fuck?" Badger
    */

}



