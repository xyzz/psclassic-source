/*
 * (C) Gražvydas "notaz" Ignotas, 2011-2013
 *
 * This work is licensed under the terms of any of these licenses
 * (at your option):
 *  - GNU GPL, version 2 or later.
 *  - GNU LGPL, version 2.1 or later.
 * See the COPYING file in the top-level directory.
 */

#include <stdio.h>
#include <SDL.h>

#include "libpicofe/input.h"
#include "libpicofe/in_sdl.h"
#include "libpicofe/menu.h"
#include "libpicofe/fonts.h"
#include "libpicofe/plat_sdl.h"
#include "libpicofe/gl.h"
#include "cspace.h"
#include "plugin_lib.h"
#include "plugin.h"
#include "main.h"
#include "plat.h"
#include "revision.h"
#if SDL_MAJOR_VERSION == 2
#include "libpicofe/keysym.h"
#endif

#define RMASK_16 0x0000F800
#define GMASK_16 0x000007E0
#define BMASK_16 0x0000001F
#define RMASK_24 0x00FF0000
#define GMASK_24 0x0000FF00
#define BMASK_24 0x000000FF


static const struct in_default_bind in_sdl_defbinds[] = {
#if SDL_MAJOR_VERSION == 2
  { MY_SDLK_UP,     IN_BINDTYPE_PLAYER12, DKEY_UP },
  { MY_SDLK_DOWN,   IN_BINDTYPE_PLAYER12, DKEY_DOWN },
  { MY_SDLK_LEFT,   IN_BINDTYPE_PLAYER12, DKEY_LEFT },
  { MY_SDLK_RIGHT,  IN_BINDTYPE_PLAYER12, DKEY_RIGHT },
  { MY_SDLK_d,      IN_BINDTYPE_PLAYER12, DKEY_TRIANGLE },
  { MY_SDLK_z,      IN_BINDTYPE_PLAYER12, DKEY_CROSS },
  { MY_SDLK_x,      IN_BINDTYPE_PLAYER12, DKEY_CIRCLE },
  { MY_SDLK_s,      IN_BINDTYPE_PLAYER12, DKEY_SQUARE },
  { MY_SDLK_v,      IN_BINDTYPE_PLAYER12, DKEY_START },
  { MY_SDLK_c,      IN_BINDTYPE_PLAYER12, DKEY_SELECT },
  { MY_SDLK_w,      IN_BINDTYPE_PLAYER12, DKEY_L1 },
  { MY_SDLK_r,      IN_BINDTYPE_PLAYER12, DKEY_R1 },
  { MY_SDLK_e,      IN_BINDTYPE_PLAYER12, DKEY_L2 },
  { MY_SDLK_t,      IN_BINDTYPE_PLAYER12, DKEY_R2 },
  { MY_SDLK_EJECT,     IN_BINDTYPE_EMU, SACTION_CD_CHANGE },
  { MY_SDLK_AUDIOPLAY,    IN_BINDTYPE_EMU, SACTION_RESET_EVENT },
#else
  { SDLK_UP,     IN_BINDTYPE_PLAYER12, DKEY_UP },
  { SDLK_DOWN,   IN_BINDTYPE_PLAYER12, DKEY_DOWN },
  { SDLK_LEFT,   IN_BINDTYPE_PLAYER12, DKEY_LEFT },
  { SDLK_RIGHT,  IN_BINDTYPE_PLAYER12, DKEY_RIGHT },
  { SDLK_d,      IN_BINDTYPE_PLAYER12, DKEY_TRIANGLE },
  { SDLK_z,      IN_BINDTYPE_PLAYER12, DKEY_CROSS },
  { SDLK_x,      IN_BINDTYPE_PLAYER12, DKEY_CIRCLE },
  { SDLK_s,      IN_BINDTYPE_PLAYER12, DKEY_SQUARE },
  { SDLK_v,      IN_BINDTYPE_PLAYER12, DKEY_START },
  { SDLK_c,      IN_BINDTYPE_PLAYER12, DKEY_SELECT },
  { SDLK_w,      IN_BINDTYPE_PLAYER12, DKEY_L1 },
  { SDLK_r,      IN_BINDTYPE_PLAYER12, DKEY_R1 },
  { SDLK_e,      IN_BINDTYPE_PLAYER12, DKEY_L2 },
  { SDLK_t,      IN_BINDTYPE_PLAYER12, DKEY_R2 },
  { SDLK_ESCAPE, IN_BINDTYPE_EMU, SACTION_ENTER_MENU },
  { SDLK_F1,     IN_BINDTYPE_EMU, SACTION_SAVE_STATE },
  { SDLK_F2,     IN_BINDTYPE_EMU, SACTION_LOAD_STATE },
  { SDLK_F3,     IN_BINDTYPE_EMU, SACTION_PREV_SSLOT },
  { SDLK_F4,     IN_BINDTYPE_EMU, SACTION_NEXT_SSLOT },
  { SDLK_F5,     IN_BINDTYPE_EMU, SACTION_TOGGLE_FSKIP },
  { SDLK_F6,     IN_BINDTYPE_EMU, SACTION_SCREENSHOT },
  { SDLK_F7,     IN_BINDTYPE_EMU, SACTION_TOGGLE_FPS },
  { SDLK_F8,     IN_BINDTYPE_EMU, SACTION_SWITCH_DISPMODE },
  { SDLK_F9,     IN_BINDTYPE_EMU, SACTION_CD_CHANGE },
  { SDLK_F10,    IN_BINDTYPE_EMU, SACTION_RESET_EVENT },
  { SDLK_F11,    IN_BINDTYPE_EMU, SACTION_TOGGLE_FULLSCREEN },
  { SDLK_BACKSPACE, IN_BINDTYPE_EMU, SACTION_FAST_FORWARD },
  { SDLK_EJECT,     IN_BINDTYPE_EMU, SACTION_CD_CHANGE },
  { SDLK_AUDIOPLAY,    IN_BINDTYPE_EMU, SACTION_RESET_EVENT },
#endif
  { 0, 0, 0 }
};

const struct menu_keymap in_sdl_key_map[] =
{
#if SDL_MAJOR_VERSION == 2
  { MY_SDLK_UP,     PBTN_UP },
  { MY_SDLK_DOWN,   PBTN_DOWN },
  { MY_SDLK_LEFT,   PBTN_LEFT },
  { MY_SDLK_RIGHT,  PBTN_RIGHT },
  { MY_SDLK_RETURN, PBTN_MOK },
  { MY_SDLK_ESCAPE, PBTN_MBACK },
  { MY_SDLK_SEMICOLON,    PBTN_MA2 },
  { MY_SDLK_QUOTE,        PBTN_MA3 },
  { MY_SDLK_LEFTBRACKET,  PBTN_L },
  { MY_SDLK_RIGHTBRACKET, PBTN_R },
#else
  { SDLK_UP,     PBTN_UP },
  { SDLK_DOWN,   PBTN_DOWN },
  { SDLK_LEFT,   PBTN_LEFT },
  { SDLK_RIGHT,  PBTN_RIGHT },
  { SDLK_RETURN, PBTN_MOK },
  { SDLK_ESCAPE, PBTN_MBACK },
  { SDLK_SEMICOLON,    PBTN_MA2 },
  { SDLK_QUOTE,        PBTN_MA3 },
  { SDLK_LEFTBRACKET,  PBTN_L },
  { SDLK_RIGHTBRACKET, PBTN_R },
#endif
};

const struct menu_keymap in_sdl_joy_map_1[] =
{
#if SDL_MAJOR_VERSION == 2
  { MY_SDLK_UP,    PBTN_UP },
  { MY_SDLK_DOWN,  PBTN_DOWN },
  { MY_SDLK_LEFT,  PBTN_LEFT },
  { MY_SDLK_RIGHT, PBTN_RIGHT },
  /* joystick */
  { MY_SDLK_WORLD_0, PBTN_MA2 },
  { MY_SDLK_WORLD_1, PBTN_MBACK },
  { MY_SDLK_WORLD_2, PBTN_MOK },
  { MY_SDLK_WORLD_3, PBTN_MA3 },
#else
  { SDLK_UP,    PBTN_UP },
  { SDLK_DOWN,  PBTN_DOWN },
  { SDLK_LEFT,  PBTN_LEFT },
  { SDLK_RIGHT, PBTN_RIGHT },
  /* joystick */
  { SDLK_WORLD_0, PBTN_MOK },
  { SDLK_WORLD_1, PBTN_MBACK },
  { SDLK_WORLD_2, PBTN_MA2 },
  { SDLK_WORLD_3, PBTN_MA3 },
#endif
};

const struct menu_keymap in_sdl_joy_map_2[] =
{
#if SDL_MAJOR_VERSION == 2
  { MY_SDLK_UP,    PBTN_UP },
  { MY_SDLK_DOWN,  PBTN_DOWN },
  { MY_SDLK_LEFT,  PBTN_LEFT },
  { MY_SDLK_RIGHT, PBTN_RIGHT },
  /* joystick */
  { MY_SDLK_WORLD_0, PBTN_MA2 },
  { MY_SDLK_WORLD_1, PBTN_MOK },
  { MY_SDLK_WORLD_2, PBTN_MBACK },
  { MY_SDLK_WORLD_3, PBTN_MA3 },
#else
  { SDLK_UP,    PBTN_UP },
  { SDLK_DOWN,  PBTN_DOWN },
  { SDLK_LEFT,  PBTN_LEFT },
  { SDLK_RIGHT, PBTN_RIGHT },
  /* joystick */
  { SDLK_WORLD_0, PBTN_MOK },
  { SDLK_WORLD_1, PBTN_MBACK },
  { SDLK_WORLD_2, PBTN_MA2 },
  { SDLK_WORLD_3, PBTN_MA3 },
#endif
};

static const struct in_pdata in_sdl_platform_data_1 = {
  .defbinds  = in_sdl_defbinds,
  .key_map   = in_sdl_key_map,
  .kmap_size = sizeof(in_sdl_key_map) / sizeof(in_sdl_key_map[0]),
  .joy_map   = in_sdl_joy_map_1,
  .jmap_size = sizeof(in_sdl_joy_map_1) / sizeof(in_sdl_joy_map_1[0]),
};

static const struct in_pdata in_sdl_platform_data_2 = {
  .defbinds  = in_sdl_defbinds,
  .key_map   = in_sdl_key_map,
  .kmap_size = sizeof(in_sdl_key_map) / sizeof(in_sdl_key_map[0]),
  .joy_map   = in_sdl_joy_map_2,
  .jmap_size = sizeof(in_sdl_joy_map_2) / sizeof(in_sdl_joy_map_2[0]),
};

static int psx_w, psx_h;
static void *shadow_fb, *last_shadow_fb, *menubg_img;
static int in_menu;
static int menu_leave;

static int change_video_mode(int force)
{
  int w, h;

  if (in_menu) {
    w = g_menuscreen_w;
    h = g_menuscreen_h;
  }
  else {
    w = psx_w;
    h = psx_h;
  }

  return plat_sdl_change_video_mode(w, h, force);
}

static void resize_cb(int w, int h)
{
  // used by some plugins..
  pl_rearmed_cbs.screen_w = w;
  pl_rearmed_cbs.screen_h = h;
  pl_rearmed_cbs.gles_display = gl_es_display;
  pl_rearmed_cbs.gles_surface = gl_es_surface;
  plugin_call_rearmed_cbs();
}

static void quit_cb(void)
{
  emu_core_ask_exit();
}

static void get_layer_pos(int *x, int *y, int *w, int *h)
{
  // always fill entire SDL window
  *x = *y = 0;
  *w = pl_rearmed_cbs.screen_w;
  *h = pl_rearmed_cbs.screen_h;
}

#if SDL_MAJOR_VERSION == 2
void plat_init(int isGame, int enter_mode)
#else
void plat_init(void)
#endif
{
  int shadow_size;
  int ret;

  plat_sdl_quit_cb = quit_cb;
  plat_sdl_resize_cb = resize_cb;

#if SDL_MAJOR_VERSION == 2
  ret = plat_sdl_init(isGame);
#else
  ret = plat_sdl_init();
#endif
  if (ret != 0)
    exit(1);

  in_menu = 1;
  menu_leave = 0;
#if SDL_MAJOR_VERSION == 2
  SDL_SetWindowTitle(sdl2_window, "PCSX-ReARMed " REV); 
#else
  SDL_WM_SetCaption("PCSX-ReARMed " REV, NULL);
#endif
  shadow_size = g_menuscreen_w * g_menuscreen_h * 3;
  if (shadow_size < 640 * (576 + 2) * 3)
    shadow_size = 640 * (576 + 2) * 3;

  shadow_fb = malloc(shadow_size);
  last_shadow_fb = malloc(shadow_size);
  menubg_img = malloc(shadow_size);
  if (shadow_fb == NULL || last_shadow_fb == NULL || menubg_img == NULL) {
    fprintf(stderr, "OOM\n");
    exit(1);
  }
  if (enter_mode == 1) {
    in_sdl_init(&in_sdl_platform_data_1, plat_sdl_event_handler);
  }
  else {
    in_sdl_init(&in_sdl_platform_data_2, plat_sdl_event_handler);
  }
  in_probe();
  pl_rearmed_cbs.only_16bpp = 0;
  pl_rearmed_cbs.pl_get_layer_pos = get_layer_pos;

  bgr_to_uyvy_init();
}

void plat_finish(void)
{
  free(shadow_fb);
  shadow_fb = NULL;
  free(last_shadow_fb);
  last_shadow_fb = NULL;
  free(menubg_img);
  menubg_img = NULL;
  plat_sdl_finish();
}

void plat_gvideo_open(int is_pal)
{
}

static void uyvy_to_rgb565(void *d, const void *s, int pixels)
{
  unsigned short *dst = d;
  const unsigned int *src = s;
  int v;

  // no colors, for now
  for (; pixels > 0; src++, dst += 2, pixels -= 2) {
    v = (*src >> 8) & 0xff;
    v = (v - 16) * 255 / 219 / 8;
    dst[0] = (v << 11) | (v << 6) | v;

    v = (*src >> 24) & 0xff;
    v = (v - 16) * 255 / 219 / 8;
    dst[1] = (v << 11) | (v << 6) | v;
  }
}

static void overlay_blit(int doffs, const void *src_, int w, int h,
                         int sstride, int bgr24)
{
#if SDL_MAJOR_VERSION == 1
  const unsigned short *src = src_;
  unsigned short *dst;
  int dstride = plat_sdl_overlay->w;

  SDL_LockYUVOverlay(plat_sdl_overlay);
  dst = (void *)plat_sdl_overlay->pixels[0];

  dst += doffs;
  if (bgr24) {
    for (; h > 0; dst += dstride, src += sstride, h--)
      bgr888_to_uyvy(dst, src, w);
  }
  else {
    for (; h > 0; dst += dstride, src += sstride, h--)
      bgr555_to_uyvy(dst, src, w);
  }

  SDL_UnlockYUVOverlay(plat_sdl_overlay);
#endif
}

static void overlay_hud_print(int x, int y, const char *str, int bpp)
{
#if SDL_MAJOR_VERSION == 1
  SDL_LockYUVOverlay(plat_sdl_overlay);
  basic_text_out_uyvy_nf(plat_sdl_overlay->pixels[0], plat_sdl_overlay->w, x, y, str);
  SDL_UnlockYUVOverlay(plat_sdl_overlay);
#endif
}

void *plat_gvideo_set_mode(int *w, int *h, int *bpp)
{
  psx_w = *w;
  psx_h = *h;

  /* workaround for ps logo issue */
  if (psx_w == 640 && psx_h == 472) psx_h = 480;

  change_video_mode(0);
#if SDL_MAJOR_VERSION == 1
  if (plat_sdl_overlay != NULL) {
    pl_plat_clear = plat_sdl_overlay_clear;
    pl_plat_blit = overlay_blit;
    pl_plat_hud_print = overlay_hud_print;
    return NULL;
  }
  else {
    pl_plat_clear = NULL;
    pl_plat_blit = NULL;
    pl_plat_hud_print = NULL;
    if (plat_sdl_gl_active)
      return shadow_fb;
    else
      return plat_sdl_screen->pixels;
  }
#else
  printf("plat_gvideo_set_mode() : plat_sdl_gl_active=%d psx_w=%d,psx_h=%d\n",plat_sdl_gl_active,psx_w,psx_h);
  pl_plat_clear = NULL;
  pl_plat_blit = NULL;
  pl_plat_hud_print = NULL;
  if (plat_sdl_gl_active) {
    printf("   shadow_fb=%0x\n",shadow_fb);
    return shadow_fb;
  }
  else {
    printf("   plat_sdl_screen->pixels=%0x\n",plat_sdl_screen->pixels);
    return plat_sdl_screen->pixels;
  }
#endif
}

void *plat_gvideo_flip(int rgb888)
{

#if SDL_MAJOR_VERSION == 1
  if (plat_sdl_overlay != NULL) {
    SDL_Rect dstrect = { 0, 0, plat_sdl_screen->w, plat_sdl_screen->h };
    SDL_DisplayYUVOverlay(plat_sdl_overlay, &dstrect);
    return NULL;
  }
  else if (plat_sdl_gl_active) {
#else
  if (plat_sdl_gl_active) {
#endif
    if (menu_leave) {
      // restore last shadow_fb
      memcpy(shadow_fb, last_shadow_fb, psx_w * psx_h * (rgb888 ? 3 : 2));
      menu_leave = 0;
    }
    gl_flip(shadow_fb, psx_w, psx_h, rgb888);
    return shadow_fb;
  }
  else {
    // XXX: no locking, but should be fine with SDL_SWSURFACE?
#if SDL_MAJOR_VERSION == 2
    SDL_Window* window;
    SDL_Renderer* renderer;

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderPresent(renderer);
#else
    SDL_Flip(plat_sdl_screen);
#endif
    return plat_sdl_screen->pixels;
  }
}

void plat_gvideo_close(void)
{
}

void plat_video_menu_enter(int is_rom_loaded, int bpp)
{
  int force_mode_change = 0;

printf("frontend/plat_sdl.c : plat_video_menu_enter() : plat_sdl_gl_active=%d is_rom_loaded=%d\n",plat_sdl_gl_active,is_rom_loaded);

  in_menu = 1;

#if SDL_MAJOR_VERSION == 1
  /* surface will be lost, must adjust pl_vout_buf for menu bg */
  if (plat_sdl_overlay != NULL)
    uyvy_to_rgb565(menubg_img, plat_sdl_overlay->pixels[0], psx_w * psx_h);
  else if (plat_sdl_gl_active)
    memcpy(menubg_img, shadow_fb, psx_w * psx_h * 2);
  else
    memcpy(menubg_img, plat_sdl_screen->pixels, psx_w * psx_h * 2);
  pl_vout_buf = menubg_img;
  }
#else
  int depth = bpp;
  if (plat_sdl_gl_active) {

    SDL_Surface *source_surface, *target_surface, *darken_surface;
    int ret;
    int pitch = psx_w * depth / 8;
    Uint32 rmask, gmask, bmask;

    if (depth == 16) {
      rmask = RMASK_16;
      gmask = GMASK_16;
      bmask = BMASK_16;
    }
    else {
      rmask = RMASK_24;
      gmask = GMASK_24;
      bmask = BMASK_24;
    }

    // keep last shdow_fb
    memcpy(last_shadow_fb, shadow_fb, psx_w * psx_h * depth / 8);

    // create source surface (original size)
    source_surface = SDL_CreateRGBSurfaceFrom(shadow_fb, psx_w, psx_h, depth, pitch, rmask, gmask, bmask, 0);
    if (source_surface == NULL) {
      printf("failed to create source_surface\n");
      goto out;
    }
    // create target surface (full size)
    target_surface = SDL_CreateRGBSurface(0, g_menuscreen_w, g_menuscreen_h, depth, rmask, gmask, bmask, 0);
    if (target_surface == NULL) {
      printf("failed to create target_surface\n");
      goto out;
    }
    // blit source surface to target surface
    ret = SDL_BlitScaled(source_surface, NULL, target_surface, NULL);
    if (ret < 0) {
      printf("SDL_BlitScaled error\n");
      goto out;
    }
    // create darken surface (full size)
    darken_surface = SDL_CreateRGBSurface(0, g_menuscreen_w, g_menuscreen_h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    if (darken_surface == NULL) {
      printf("failed to create darken_surface\n");
      goto out;
    }
    // set pixels of darken surface
    ret = SDL_FillRect(darken_surface, NULL, SDL_MapRGB(darken_surface->format, 0, 0, 0));
    if (ret < 0) {
      printf("SDL_FillRect error\n");
      goto out;
    }
    // set alpha of darken surface (30%)
    ret = SDL_SetSurfaceAlphaMod(darken_surface, 204);
    if (ret < 0) {
      printf("SDL_SetSurfaceAlphaMod error\n");
      goto out;
    }
    // blit darken surface to target surface
    ret = SDL_BlitSurface(darken_surface, NULL, target_surface, NULL);
    if (ret < 0) {
      printf("SDL_BlitSurface error\n");
    }

    memcpy(menubg_img, target_surface->pixels, g_menuscreen_w * g_menuscreen_h * depth / 8);

out:
    SDL_FreeSurface(source_surface);
    SDL_FreeSurface(target_surface);
    SDL_FreeSurface(darken_surface);

    pl_vout_buf = menubg_img;
  }
  else {
    memcpy(menubg_img, plat_sdl_screen->pixels, psx_w * psx_h * depth / 8);
    pl_vout_buf = menubg_img;
    printf("memcpy   menubg_img=%0x,plat_sdl_screen->pixels=%0x,psx_w=%d,psx_h=%d\n",menubg_img,plat_sdl_screen->pixels,psx_w,psx_h);
  }
#endif

  /* gles plugin messes stuff up.. */
  if (pl_rearmed_cbs.gpu_caps & GPU_CAP_OWNS_DISPLAY)
    force_mode_change = 1;

  change_video_mode(force_mode_change);
}



void plat_video_menu_begin(void)
{
#if SDL_MAJOR_VERSION == 1
  if (plat_sdl_overlay != NULL || plat_sdl_gl_active) {
    g_menuscreen_ptr = shadow_fb;
  }
  else {
    SDL_LockSurface(plat_sdl_screen);
    g_menuscreen_ptr = plat_sdl_screen->pixels;
  }
#else
  printf("frontend/plat_sdl.c : plat_video_menu_begin() : plat_sdl_gl_active=%d\n",plat_sdl_gl_active);

  if (plat_sdl_gl_active) {
    g_menuscreen_ptr = shadow_fb;
  }
  else {
    SDL_LockSurface(plat_sdl_screen);
    g_menuscreen_ptr = plat_sdl_screen->pixels;
  }
  printf("plat_video_menu_begin() end\n");
  printf("  shadow_fb=%x\n",shadow_fb);
  printf("  plat_sdl_screen->pixels=%x\n",plat_sdl_screen->pixels);
  printf("  g_menuscreen_ptr=%x\n",g_menuscreen_ptr);

#endif
}





void plat_video_menu_end(void)
{
#if SDL_MAJOR_VERSION == 1
  if (plat_sdl_overlay != NULL) {
    SDL_Rect dstrect = { 0, 0, plat_sdl_screen->w, plat_sdl_screen->h };

    SDL_LockYUVOverlay(plat_sdl_overlay);
    rgb565_to_uyvy(plat_sdl_overlay->pixels[0], shadow_fb,
      g_menuscreen_w * g_menuscreen_h);
    SDL_UnlockYUVOverlay(plat_sdl_overlay);

    SDL_DisplayYUVOverlay(plat_sdl_overlay, &dstrect);
  }
  else if (plat_sdl_gl_active) {
    gl_flip(g_menuscreen_ptr, g_menuscreen_w, g_menuscreen_h, 0);
  }
  else {
    SDL_Flip(plat_sdl_screen);
  }
#else
  printf("frontend/plat_sdl.c : plat_video_menu_end() : plat_sdl_gl_active=%d\n",plat_sdl_gl_active);
  printf("    plat_sdl_gl_active=%d\n",plat_sdl_gl_active);

  if (plat_sdl_gl_active) {

    printf("gl_flip() g_menuscreen_ptr=%0x, g_menuscreen_w=%d, g_menuscreen_h=%d\n",g_menuscreen_ptr,g_menuscreen_w,g_menuscreen_h);

    //gl_flip(g_menuscreen_ptr, 640, 480);
    gl_flip(g_menuscreen_ptr, g_menuscreen_w, g_menuscreen_h, 0);

    printf("gl_flip() end\n");
  }
  else {

    SDL_UnlockSurface(plat_sdl_screen);

    int fs_w,fs_h;
    SDL_GetWindowSize(sdl2_window, &fs_w, &fs_h);
    printf("plat_video_menu_end: window->W=%d, h=%d \n", fs_w, fs_h);
    printf("plat_video_menu_end:  plat_sdl_screen->w=%d, h=%d \n",plat_sdl_screen->w,plat_sdl_screen->h);

#if 0
    sdl2_texture = SDL_CreateTextureFromSurface(sdl2_renderer, plat_sdl_screen);
    SDL_RenderClear(sdl2_renderer);
    SDL_RenderCopy(sdl2_renderer, sdl2_texture, NULL, NULL);

    SDL_RenderPresent(sdl2_renderer);
#else
    SDL_UpdateWindowSurface(sdl2_window);
#endif


  }
#endif
  g_menuscreen_ptr = NULL;
}

void plat_video_menu_leave(void)
{
  in_menu = 0;
  menu_leave = 1;
}

/* unused stuff */
void *plat_prepare_screenshot(int *w, int *h, int *bpp)
{
  return 0;
}

void plat_trigger_vibrate(int pad, int low, int high)
{
}

void plat_minimize(void)
{
}

// vim:shiftwidth=2:expandtab
