#ifndef GFX_H
#define GFX_H

void gfx_init(void);
void gfx_load_level(char *path);
void gfx_load_sprite(const char *rel_path);
void gfx_update(void);
#endif
