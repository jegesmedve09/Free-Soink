#include "GS.h"

/* builds a simple 32x32 checkerboard so you can see uv + scaling working
 * without needing real .chg/.lvg assets yet */
static void make_checker(u8 *buf, u16 w, u16 h, u8 tile)
{
    u16 x, y;
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            u8 c = ((x / tile) + (y / tile)) & 1;
            /* index 0 is transparent, so use 1/2 for the checker colors */
            buf[y * w + x] = c ? 2 : 1;
        }
    }
}

int main(int argc, char **argv)
{
    (void)argc; (void)argv;

    u8 checker[32 * 32];
    u8 tex_id;
    u32 palette[256];
    int i;

    if (!GS_init("gfx demo", 3)) return 1;

    /* GS_default_grayscale_palette() maps index i -> RGB(i,i,i), so
     * low indices like our checker's 1/2 are nearly invisible black-
     * on-black. Build an explicit palette instead: index 0 = a dark
     * background so you can see the screen bounds, 1 = orange,
     * 2 = cyan. This is the same kind of palette palette_to_c.py
     * would emit for a real level - GS_set_palette() takes that
     * output directly. */
    for (i = 0; i < 256; i++) palette[i] = 0xFF000000; /* opaque black */
    palette[0] = 0xFF202030; /* dark blue-gray background, not pure black */
    palette[1] = 0xFFFF8800; /* orange */
    palette[2] = 0xFF00DDFF; /* cyan */

    make_checker(checker, 32, 32, 4);
    tex_id = GS_upload_texture(checker, 32, 32);

    while (!GS_poll_quit()) {
        GS_clear(0);

        /* whole texture, 1:1 */
        GS_plot_texture(tex_id, 10, 10);

        /* just the top-left 16x16 quadrant of it */
        GS_plot_texture_uv(tex_id, 60, 10, 0, 0, 16, 16);

        /* whole texture scaled up to 64x64, like a GS sprite prim
         * with a bigger dest rect than source rect */
        GS_plot_texture_scaled(tex_id, 120, 10, 0, 0, 32, 32, 64, 64);

        /* same texture scaled DOWN to 12x12 */
        GS_plot_texture_scaled(tex_id, 200, 10, 0, 0, 32, 32, 12, 12);

        GS_present();
    }

    GS_shutdown();
    return 0;
}
