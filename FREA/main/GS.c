//-----------
// GS Lite
// A standard ps2sdk similar sintax for working with SDL
//-----------

#include "GS.h"
#include <string.h>
#include <stdlib.h>


typedef struct
{
    u8  *data;
    u16  w, h;
    u8   used;
}
GS_texture_t;

static GS_texture_t g_textures[GS_MAX_TEXTURES];


static u32 g_palette[256] =
{
    0x80000000, 0x00002000, 0x00004000, 0x00006000, 0x00008000, 0x0000A000, 0x0000C000, 0x0000E000,
    0x00200000, 0x00202000, 0x00204000, 0x00206000, 0x00208000, 0x0020A000, 0x0020C000, 0x0020E000,
    0x00400000, 0x00402000, 0x00404000, 0x00406000, 0x00408000, 0x0040A000, 0x0040C000, 0x0040E000,
    0x00600000, 0x00602000, 0x00604000, 0x00606000, 0x00608000, 0x0060A000, 0x0060C000, 0x0060E000,
    0x00800000, 0x00802000, 0x00804000, 0x00806000, 0x00808000, 0x0080A000, 0x0080C000, 0x0080E000,
    0x00A00000, 0x00A02000, 0x00A04000, 0x00A06000, 0x00A08000, 0x00A0A000, 0x00A0C000, 0x00A0E000,
    0x00C00000, 0x00C02000, 0x00C04000, 0x00C06000, 0x00C08000, 0x00C0A000, 0x00C0C000, 0x00C0E000,
    0x00E00000, 0x00E02000, 0x00E04000, 0x00E06000, 0x00E08000, 0x00E0A000, 0x00E0C000, 0x00E0E000,
    0x00000040, 0x00002040, 0x00004040, 0x00006040, 0x00008040, 0x0000A040, 0x0000C040, 0x0000E040,
    0x00200040, 0x00202040, 0x00204040, 0x00206040, 0x00208040, 0x0020A040, 0x0020C040, 0x0020E040,
    0x00400040, 0x00402040, 0x00404040, 0x00406040, 0x00408040, 0x0040A040, 0x0040C040, 0x0040E040,
    0x00600040, 0x00602040, 0x00604040, 0x00606040, 0x00608040, 0x0060A040, 0x0060C040, 0x0060E040,
    0x00800040, 0x00802040, 0x00804040, 0x00806040, 0x00808040, 0x0080A040, 0x0080C040, 0x0080E040,
    0x00A00040, 0x00A02040, 0x00A04040, 0x00A06040, 0x00A08040, 0x00A0A040, 0x00A0C040, 0x00A0E040,
    0x00C00040, 0x00C02040, 0x00C04040, 0x00C06040, 0x00C08040, 0x00C0A040, 0x00C0C040, 0x00C0E040,
    0x00E00040, 0x00E02040, 0x00E04040, 0x00E06040, 0x00E08040, 0x00E0A040, 0x00E0C040, 0x00E0E040,
    0x00000080, 0x00002080, 0x00004080, 0x00006080, 0x00008080, 0x0000A080, 0x0000C080, 0x0000E080,
    0x00200080, 0x00202080, 0x00204080, 0x00206080, 0x00208080, 0x0020A080, 0x0020C080, 0x0020E080,
    0x00400080, 0x00402080, 0x00404080, 0x00406080, 0x00408080, 0x0040A080, 0x0040C080, 0x0040E080,
    0x00600080, 0x00602080, 0x00604080, 0x00606080, 0x00608080, 0x0060A080, 0x0060C080, 0x0060E080,
    0x00800080, 0x00802080, 0x00804080, 0x00806080, 0x00808080, 0x0080A080, 0x0080C080, 0x0080E080,
    0x00A00080, 0x00A02080, 0x00A04080, 0x00A06080, 0x00A08080, 0x00A0A080, 0x00A0C080, 0x00A0E080,
    0x00C00080, 0x00C02080, 0x00C04080, 0x00C06080, 0x00C08080, 0x00C0A080, 0x00C0C080, 0x00C0E080,
    0x00E00080, 0x00E02080, 0x00E04080, 0x00E06080, 0x00E08080, 0x00E0A080, 0x00E0C080, 0x00E0E080,
    0x000000C0, 0x000020C0, 0x000040C0, 0x000060C0, 0x000080C0, 0x0000A0C0, 0x0000C0C0, 0x0000E0C0,
    0x002000C0, 0x002020C0, 0x002040C0, 0x002060C0, 0x002080C0, 0x0020A0C0, 0x0020C0C0, 0x0020E0C0,
    0x004000C0, 0x004020C0, 0x004040C0, 0x004060C0, 0x004080C0, 0x0040A0C0, 0x0040C0C0, 0x0040E0C0,
    0x006000C0, 0x006020C0, 0x006040C0, 0x006060C0, 0x006080C0, 0x0060A0C0, 0x0060C0C0, 0x0060E0C0,
    0x008000C0, 0x008020C0, 0x008040C0, 0x008060C0, 0x008080C0, 0x0080A0C0, 0x0080C0C0, 0x0080E0C0,
    0x00A000C0, 0x00A020C0, 0x00A040C0, 0x00A060C0, 0x00A080C0, 0x00A0A0C0, 0x00A0C0C0, 0x00A0E0C0,
    0x00C000C0, 0x00C020C0, 0x00C040C0, 0x00C060C0, 0x00C080C0, 0x00C0A0C0, 0x00C0C0C0, 0x00C0E0C0,
    0x00E000C0, 0x00E020C0, 0x00E040C0, 0x00E060C0, 0x00E080C0, 0x00E0A0C0, 0x00E0C0C0, 0x00E0E0C0,
};

static u8  g_framebuffer[SCREEN_WIDTH * SCREEN_HEIGHT];
static u32 g_rgba[SCREEN_WIDTH * SCREEN_HEIGHT];

static SDL_Window   *g_window   = NULL;
static SDL_Renderer *g_renderer = NULL;
static SDL_Texture  *g_screen_tex = NULL;

int GS_init(const char *title, int window_scale)
{
    if (window_scale < 1) window_scale = 1;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("GS_init: SDL_Init failed: %s", SDL_GetError());
        return 0;
    }

    /* the crispyness (or blurryness, who looks at it) of the PS2*/
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    g_window = SDL_CreateWindow
    (
        title ? title : "Sonic THe Hedgehog & The Chaos Within (FALLBACK)",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH * window_scale,
        SCREEN_HEIGHT * window_scale,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN
    );

    if (!g_window)
    {
        SDL_Log("GS_init: CreateWindow failed: %s", SDL_GetError());
        return 0;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!g_renderer)
    {
        // HAIL THE CPU RENDERING, Run this on an AMD Epyc, i dunno what happens, never tried it
        g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_SOFTWARE);
    }
    if (!g_renderer)
    {
        SDL_Log("GS_init: CreateRenderer failed: %s", SDL_GetError());
        return 0;
    }

    SDL_RenderSetLogicalSize(g_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    g_screen_tex = SDL_CreateTexture(g_renderer,
                                    SDL_PIXELFORMAT_ARGB8888,
                                    SDL_TEXTUREACCESS_STREAMING,
                                    SCREEN_WIDTH,
                                    SCREEN_HEIGHT
                                    );
    if (!g_screen_tex)
    {
        SDL_Log("GS_init: CreateTexture failed: %s", SDL_GetError());
        return 0;
    }

    memset(g_textures, 0, sizeof(g_textures));
    GS_clear(0);

    return 1;
}

void GS_shutdown(void)
{
    GS_free_all_textures();

    if (g_screen_tex)
    {
        SDL_DestroyTexture(g_screen_tex);
        g_screen_tex = NULL;
    }
    if (g_renderer)
    {
        SDL_DestroyRenderer(g_renderer);
        g_renderer = NULL;
    }
    if (g_window)
    {
        SDL_DestroyWindow(g_window);
        g_window = NULL;
    }

    SDL_Quit();
}

int GS_poll_quit(void)
{
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        if (ev.type == SDL_QUIT) return 1;
        if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE) return 1;
    }
    return 0;
}

u8 GS_upload_texture(const u8 *pixels, u16 w, u16 h)
{
    int i;
    for (i = 0; i < GS_MAX_TEXTURES; i++)
    {
        if (!g_textures[i].used)
        {
            size_t sz = (size_t)w * (size_t)h;
            g_textures[i].data = (u8 *)malloc(sz);

            if (!g_textures[i].data)
            {
                return GS_INVALID_TEX;
            }

            memcpy(g_textures[i].data, pixels, sz);
            g_textures[i].w = w;
            g_textures[i].h = h;
            g_textures[i].used = 1;
            return (u8)i;
        }
    }
    return GS_INVALID_TEX; /* VRAM full, at 320x224 8bit there can be around ~39 or so...*/
}

void GS_free_texture(u8 tex_id)
{
    if (!g_textures[tex_id].used) { return; }

    free(g_textures[tex_id].data);
    g_textures[tex_id].data = NULL;
    g_textures[tex_id].used = 0;
    g_textures[tex_id].w = 0;
    g_textures[tex_id].h = 0;
}

void GS_free_all_textures(void)
{
    int i;
    for (i = 0; i < GS_MAX_TEXTURES; i++)
    {
        if (g_textures[i].used)
        {
            GS_free_texture((u8)i);
        }
    }
}

u16 GS_texture_width(u8 tex_id)
{
    if (!g_textures[tex_id].used)
    {
        return 0;
    }

    return g_textures[tex_id].w;
}

u16 GS_texture_height(u8 tex_id)
{
    if (!g_textures[tex_id].used)
    {
        return 0;
    }

    return g_textures[tex_id].h;
}

void GS_clear(u8 index)
{
    memset(g_framebuffer, index, sizeof(g_framebuffer));
}

void GS_plot_texture_uv(u8 tex_id, s32 x, s32 y, s32 u, s32 v, s32 w, s32 h)
{
    GS_texture_t *tex;
    s32 row, col;

    if (!g_textures[tex_id].used) return;
    tex = &g_textures[tex_id];

    for (row = 0; row < h; row++)
    {
        s32 py = y + row;
        s32 sy = v + row;

        if (py < 0 || py >= SCREEN_HEIGHT)
        {
            continue;
        }

        if (sy < 0 || sy >= tex->h)
        {
            continue;
        }

        for (col = 0; col < w; col++)
        {
            s32 px = x + col;
            s32 sx = u + col;
            u8  idx;

            if (px < 0 || px >= SCREEN_WIDTH)
            {
                continue;
            }

            if (sx < 0 || sx >= tex->w)
            {
                continue;
            }

            idx = tex->data[sy * tex->w + sx];
            if (idx == 0) continue; /* PRIM_ALPHA */

            g_framebuffer[py * SCREEN_WIDTH + px] = idx;
        }
    }
}

void GS_plot_texture_scaled(u8 tex_id, s32 x, s32 y, s32 u, s32 v, s32 w, s32 h, s32 out_w, s32 out_h)
{
    GS_texture_t *tex;
    s32 row, col;
    s32 step_u, step_v; /* 16.16 fixed point, no floats */

    if (!g_textures[tex_id].used)
    {
        return;
    }

    if (out_w <= 0 || out_h <= 0 || w <= 0 || h <= 0)
    {
        return;
    }

    tex = &g_textures[tex_id];

    step_u = (w << 16) / out_w;
    step_v = (h << 16) / out_h;

    for (row = 0; row < out_h; row++)
    {
        s32 py = y + row;
        s32 sy = v + ((row * step_v) >> 16);

        if (py < 0 || py >= SCREEN_HEIGHT)
        {
            continue;
        }

        if (sy < 0 || sy >= tex->h)
        {
            continue;
        }

        for (col = 0; col < out_w; col++)
        {
            s32 px = x + col;
            s32 sx = u + ((col * step_u) >> 16);
            u8  idx;

            if (px < 0 || px >= SCREEN_WIDTH)
            {
                continue;
            }
            if (sx < 0 || sx >= tex->w)
            {
                continue;
            }

            idx = tex->data[sy * tex->w + sx];

            if (idx == 0)
            {
                continue;
            }

            g_framebuffer[py * SCREEN_WIDTH + px] = idx;
        }
    }
}

void GS_present(void)
{
    u32 i;
    for (i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
    {
        g_rgba[i] = g_palette[g_framebuffer[i]];
    }

    SDL_UpdateTexture(g_screen_tex, NULL, g_rgba, SCREEN_WIDTH * sizeof(u32));
    SDL_RenderClear(g_renderer);
    SDL_RenderCopy(g_renderer, g_screen_tex, NULL, NULL);
    SDL_RenderPresent(g_renderer);
}
