#include <SDL.h>


extern SDL_Surface *plat_sdl_screen;
#if SDL_MAJOR_VERSION == 1
extern SDL_Overlay *plat_sdl_overlay;
#endif

#if SDL_MAJOR_VERSION == 2
extern SDL_Window *sdl2_window;
extern SDL_Renderer *sdl2_renderer;
extern SDL_Texture *sdl2_texture;
#endif

extern int plat_sdl_gl_active;
extern void (*plat_sdl_resize_cb)(int w, int h);
extern void (*plat_sdl_quit_cb)(void);

#if SDL_MAJOR_VERSION == 2
int plat_sdl_init(int isGame);
#else
int plat_sdl_init(void);
#endif
int plat_sdl_change_video_mode(int w, int h, int force);
void plat_sdl_overlay_clear(void);
void plat_sdl_event_handler(void *event_);
void plat_sdl_finish(void);
