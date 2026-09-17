#ifndef GS_H
#define GS_H

/* ------------------------------------------------------------------
 * gfx.h - "GS-lite" software rasterizer wrapper around SDL2.
 *
 * Goal: give you a gsKit-shaped API on PC
 *
 * Everything internally is 8bpp indexed, one global 256-entry CLUT,
 * ------------------------------------------------------------------ */

#include <SDL.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed int     s32;

#define SCREEN_WIDTH   320
#define SCREEN_HEIGHT  224
#define GS_MAX_TEXTURES 256
#define GS_INVALID_TEX   0xFF


int  GS_init(const char *title, int window_scale);
void GS_shutdown(void);

int  GS_poll_quit(void);

void GS_set_palette(const u32 *pal256);

void GS_default_grayscale_palette(void);

u8   GS_upload_texture(const u8 *pixels, u16 w, u16 h);

void GS_free_texture(u8 tex_id);

void GS_free_all_textures(void);

u16  GS_texture_width(u8 tex_id);
u16  GS_texture_height(u8 tex_id);

void GS_clear(u8 index);

void GS_plot_texture_uv(u8 tex_id, s32 x, s32 y, s32 u, s32 v, s32 w, s32 h);

void GS_plot_texture_scaled(u8 tex_id, s32 x, s32 y, s32 u, s32 v, s32 w, s32 h, s32 out_w, s32 out_h);

void GS_present(void);

#endif /* GS_H */
