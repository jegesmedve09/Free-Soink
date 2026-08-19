#include <tamtypes.h>
#include <kernel.h>


#include "utils.c"
#include "gfx.c"

int main(void)
{
    gfx_init();

    gfx_clear(0xFF0000); // AA BB GG RR
    *(volatile u64 *)0x01EFF270 = GS_SETREG_RGBAQ(0xFF,0x00,0x00,0x00,0x00);
    //gfx_clear(0x8000FF00); // AA BB GG RR
    gfx_exec();
    gfx_flip();
    while(1){}
    return 0;
}
