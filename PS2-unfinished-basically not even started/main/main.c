#include <tamtypes.h>
#include <kernel.h>

#include "utils.h"
#include "gfx.h"

//u8 level_index=0;
//u8 act_index=0;

int main()
{
    gfx_init();
    gfx_load_level("levels/test2/");
    while (1)
    {
        gfx_update();
        //gfx_mv_bcg_x(5);
    }
    return 0;
}
