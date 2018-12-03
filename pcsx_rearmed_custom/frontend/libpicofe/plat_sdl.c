/*
 * (C) Gražvydas "notaz" Ignotas, 2012
 *
 * This work is licensed under the terms of any of these licenses
 * (at your option):
 *  - GNU GPL, version 2 or later.
 *  - GNU LGPL, version 2.1 or later.
 *  - MAME license.
 * See the COPYING file in the top-level directory.
 */

#include <stdio.h>
#include <SDL.h>
#include <SDL_syswm.h>

#include "menu.h"
#include "plat.h"
#include "gl.h"
#include "plat_sdl.h"

// XXX: maybe determine this instead..
#define WM_DECORATION_H 32



SDL_Surface *plat_sdl_screen;
#if SDL_MAJOR_VERSION == 1
SDL_Overlay *plat_sdl_overlay;
#endif
int plat_sdl_gl_active;
void (*plat_sdl_resize_cb)(int w, int h);
void (*plat_sdl_quit_cb)(void);

#if SDL_MAJOR_VERSION == 2
static const char *vid_drv_name;
SDL_Window *sdl2_window;
SDL_Renderer *sdl2_renderer;
SDL_Texture *sdl2_texture;
#else
static char vid_drv_name[32];
#endif
static int window_w, window_h;
static int fs_w, fs_h;
static int old_fullscreen;
static int vout_mode_overlay = -1, vout_mode_gl = -1;
static void *display, *window;
static int gl_quirks;
int gl_works = 0;

/* w, h is layer resolution */
int plat_sdl_change_video_mode(int w, int h, int force)
{
  static int prev_w, prev_h;

  if (w != prev_w || h != prev_h) {
    force = 1;
  }

  printf("plat_sdl_change_video_mode() start w=%d,h=%d,force=%d \n",w,h,force);
  if (w == 0)
    w = prev_w;
  else
    prev_w = w;
  if (h == 0)
    h = prev_h;
  else
    prev_h = h;

  // invalid method might come from config..
  if (plat_target.vout_method != 0
      && plat_target.vout_method != vout_mode_overlay
      && plat_target.vout_method != vout_mode_gl)
  {
    fprintf(stderr, "invalid vout_method: %d\n", plat_target.vout_method);
    plat_target.vout_method = 0;
  }

  // skip GL recreation if window doesn't change - avoids flicker
  if (plat_target.vout_method == vout_mode_gl && plat_sdl_gl_active
      && plat_target.vout_fullscreen == old_fullscreen && !force)
  {
    return 0;
  }
#if SDL_MAJOR_VERSION == 1
  if (plat_sdl_overlay != NULL) {
    SDL_FreeYUVOverlay(plat_sdl_overlay);
    plat_sdl_overlay = NULL;
  }
#endif
  if (plat_sdl_gl_active) {
    gl_finish();
    plat_sdl_gl_active = 0;
  }

  if (plat_target.vout_method != 0) {
#if SDL_MAJOR_VERSION == 1
    Uint32 flags = SDL_RESIZABLE | SDL_SWSURFACE;
#else
    Uint32 flags = SDL_WINDOW_OPENGL;
    //Uint32 flags = SDL_RESIZABLE | SDL_SWSURFACE;
#endif
    int win_w = window_w;
    int win_h = window_h;
    printf("plat_sdl_change_video_mode() plat_target.vout_fullscreen=%d fs_w=%d,fs_h=%d\n",plat_target.vout_fullscreen,fs_w,fs_h);
#if SDL_MAJOR_VERSION == 1
    if (plat_target.vout_fullscreen) {
      flags |= SDL_FULLSCREEN;
      win_w = fs_w;
      win_h = fs_h;
    }
#endif
    // XXX: workaround some occasional mysterious deadlock in SDL_SetVideoMode
    // (seen on r-pi)
    SDL_PumpEvents();

#if SDL_MAJOR_VERSION == 2
    plat_sdl_screen = SDL_GetWindowSurface(sdl2_window);
    printf("002 plat_sdl_change_video_mode : SDL_GetWindowSurface() \n");
    printf("    win_w=%d, win_h=%d flags=%d \n",win_w,win_h,flags);
    if (plat_sdl_screen == NULL) {
      fprintf(stderr, "002 plat_sdl_change_video_mode : SDL_GetWindowSurface failed: %s\n", SDL_GetError());
      plat_target.vout_method = 0;
    }
#else
    plat_sdl_screen = SDL_SetVideoMode(win_w, win_h, 0, flags);

    if (plat_sdl_screen == NULL) {
      fprintf(stderr, "002 plat_sdl_change_video_mode : SDL_SetVideoMode failed: %s\n", SDL_GetError());
      plat_target.vout_method = 0;
    }
#endif
  }

  if (plat_target.vout_method == vout_mode_overlay) {
#if SDL_MAJOR_VERSION == 1
    plat_sdl_overlay = SDL_CreateYUVOverlay(w, h, SDL_UYVY_OVERLAY, plat_sdl_screen);
    if (plat_sdl_overlay != NULL) {
      if ((long)plat_sdl_overlay->pixels[0] & 3)
        fprintf(stderr, "warning: overlay pointer is unaligned\n");

      plat_sdl_overlay_clear();
    }
    else {
      fprintf(stderr, "warning: could not create overlay.\n");
      plat_target.vout_method = 0;
    }
#else
    plat_target.vout_method = 0;
#endif
  }
  else if (plat_target.vout_method == vout_mode_gl) {
    printf("plat_sdl_change_video_mode : gl_init()\n");
    plat_sdl_gl_active = (gl_init(display, window, &gl_quirks) == 0);
    if (!plat_sdl_gl_active) {
      printf("  \n");
      fprintf(stderr, "warning: could not plat_sdl_change_video_mode : gl_init.\n");
      plat_target.vout_method = 0;
    }
    else {
      printf("  gl_init() success!\n");
    }
  }

  if (plat_target.vout_method == 0) {
    SDL_PumpEvents();
#if SDL_MAJOR_VERSION == 2

    plat_sdl_screen = SDL_GetWindowSurface(sdl2_window);
    printf("001 plat_sdl_change_video_mode : SDL_GetWindowSurface() \n");
    if (plat_sdl_screen == NULL) {
      fprintf(stderr, "001 SDL_GetWindowSurface failed: %s\n", SDL_GetError());
      return -1;
    }
#else
    plat_sdl_screen = SDL_SetVideoMode(w, h, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (plat_sdl_screen == NULL) {
      fprintf(stderr, "001 plat_sdl_change_video_mode : SDL_SetVideoMode failed: %s\n", SDL_GetError());
      return -1;
    }
#endif


  }

  old_fullscreen = plat_target.vout_fullscreen;
  if (plat_sdl_resize_cb != NULL) {
    plat_sdl_resize_cb(plat_sdl_screen->w, plat_sdl_screen->h);
  }

  printf("plat_sdl_change_video_mode() end\n");
  return 0;
}






void plat_sdl_event_handler(void *event_)
{
  static int was_active;
  SDL_Event *event = event_;

  printf("frontend/libpicofe/plat.sdl.c : plat_sdl_event_handler() %d\n",event->type);

  switch (event->type) {
#if SDL_MAJOR_VERSION == 1
  case SDL_VIDEORESIZE:
    //printf("resize %dx%d\n", event->resize.w, event->resize.h);
    if (plat_target.vout_method != 0
        && !plat_target.vout_fullscreen && !old_fullscreen)
    {
      window_w = event->resize.w;
      window_h = event->resize.h;
      plat_sdl_change_video_mode(0, 0, 1);
    }
    break;
  case SDL_ACTIVEEVENT:
    if (event->active.gain && !was_active) {
      if (plat_sdl_overlay != NULL) {
        SDL_Rect dstrect = { 0, 0, plat_sdl_screen->w, plat_sdl_screen->h };
#if SDL_MAJOR_VERSION == 1
        SDL_DisplayYUVOverlay(plat_sdl_overlay, &dstrect);
#endif
      }
      else if (plat_sdl_gl_active) {
        if (gl_quirks & GL_QUIRK_ACTIVATE_RECREATE) {
          gl_finish();
          plat_sdl_gl_active = (gl_init(display, window, &gl_quirks) == 0);
        }
        gl_flip(NULL, 0, 0);
      }
      // else SDL takes care of it
    }
    was_active = event->active.gain;
    break;
#endif
  case SDL_QUIT:
    if (plat_sdl_quit_cb != NULL)
      plat_sdl_quit_cb();
    break;
  }
}










#if SDL_MAJOR_VERSION == 2
void gl_setup_wl_information(struct wl_display * idisplay, 
	struct wl_surface *isurface, 
	struct wl_shell_surface *ishell_surface);

int plat_sdl_init(int isGame)
#else
int plat_sdl_init(void)
#endif
{
  printf("+ /frontend/libpicofe/plat_sdl_init()\n");
  static const char *vout_list[] = { NULL, NULL, NULL, NULL };
#if SDL_MAJOR_VERSION == 1
  const SDL_VideoInfo *info;
#endif
  SDL_SysWMinfo wminfo;
  int overlay_works = 0;

  int i, ret, h;

#ifdef UI_INTEGRATION
	printf("SDL_Init() not used. for UI_INTEGRATION\n");
#else
	
#if SDL_MAJOR_VERSION == 2
  printf("plat_sdl_init() : SDL_Init(SDL_INIT_VIDEO), %d\n", SDL_INIT_VIDEO);
  ret = SDL_Init(SDL_INIT_VIDEO);
#else
  ret = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE);
#endif
  if (ret != 0) {
    fprintf(stderr, "plat_sdl_init() : SDL_Init() failed: %s\n", SDL_GetError());
    return -1;
  }

#endif
	
	
#if SDL_MAJOR_VERSION == 2
  /*  */

  sdl2_window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_FULLSCREEN_DESKTOP);



  if (sdl2_window == NULL) {
    printf("- /frontend/libpicofe/plat_sdl_init() : SDL_CreateWindow() Error %s\n",SDL_GetError());
    return -1;
  } 
  else {
    /*  */
//    SDL_SetWindowSize(sdl2_window,640,480);
//    printf("SDL_SetWindowSize()\n");

    SDL_GetWindowSize(sdl2_window, &fs_w, &fs_h);
    printf("SDL_GetWindowSize w=%d,h=%d\n", fs_w, fs_h);
  }
  //sdl2_renderer = SDL_CreateRenderer(sdl2_window, -1, SDL_RENDERER_ACCELERATED);
  sdl2_renderer = SDL_CreateRenderer(sdl2_window, -1, SDL_RENDERER_SOFTWARE);
  if (sdl2_renderer == NULL) {
    printf("- /frontend/libpicofe/plat_sdl_init() SDL_CreateRenderer Error %s\n",SDL_GetError());
    return -1;
  }
  else {
    printf("plat_sdl_init() : SDL_CreateRenderer() Success.\n");
  }
  SDL_RenderSetLogicalSize(sdl2_renderer, 640, 480);

  /*  */
  sdl2_texture = SDL_CreateTexture(sdl2_renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,fs_w, fs_h);
  if (sdl2_texture == NULL) {
    printf("SDL_CreateTexture() Error %s\n",SDL_GetError());
    return -1;
  }
  else {
    printf("plat_sdl_init() : SDL_CreateTexture Success.\n");
  }
#else
  info = SDL_GetVideoInfo();
  if (info != NULL) {
    fs_w = info->current_w;
    fs_h = info->current_h;
    printf("plat_sdl: using %dx%d as fullscreen resolution\n", fs_w, fs_h);
  }
#endif
  g_menuscreen_w = 640;
  if (fs_w != 0 && g_menuscreen_w > fs_w)
    g_menuscreen_w = fs_w;
  g_menuscreen_h = 480;
  if (fs_h != 0) {
    h = fs_h;
#if SDL_MAJOR_VERSION == 2
    if (sdl2_window && h > WM_DECORATION_H)
      h -= WM_DECORATION_H;
#else
    if (info && info->wm_available && h > WM_DECORATION_H)
      h -= WM_DECORATION_H;
#endif
    if (g_menuscreen_h > h)
      g_menuscreen_h = h;
  }

  /***************************************************/
  ret = plat_sdl_change_video_mode(g_menuscreen_w, g_menuscreen_h, 1);
  if (ret != 0) {
#if SDL_MAJOR_VERSION == 2
    plat_sdl_screen = SDL_GetWindowSurface(sdl2_window);
    printf("002 plat_sdl_init : SDL_GetWindowSurface() \n");
    printf("  plat_sdl_screen->w=%d,plat_sdl_screen->h=%d\n",plat_sdl_screen->w,plat_sdl_screen->h);
    if (plat_sdl_screen == NULL) {
      fprintf(stderr, "002 plat_sdl_init : SDL_GetWindowSurface() failed: %s\n", SDL_GetError());
      goto fail;
    }
    if (plat_sdl_screen->w < 320 || plat_sdl_screen->h < 240) {
      fprintf(stderr, "resolution %dx%d is too small, sorry.\n",
              plat_sdl_screen->w, plat_sdl_screen->h);
      goto fail;
    }
#else
    plat_sdl_screen = SDL_SetVideoMode(0, 0, 16, SDL_SWSURFACE);

    if (plat_sdl_screen == NULL) {
      fprintf(stderr, "002 plat_sdl_init : SDL_SetVideoMode failed: %s\n", SDL_GetError());
      goto fail;
    }

    if (plat_sdl_screen->w < 320 || plat_sdl_screen->h < 240) {
      fprintf(stderr, "resolution %dx%d is too small, sorry.\n",
              plat_sdl_screen->w, plat_sdl_screen->h);
      goto fail;
    }
#endif
  }

#if SDL_MAJOR_VERSION == 2

#if 1
//    SDL_SetWindowSize(sdl2_window,640,480);
//    printf("SDL_SetWindowSize()\n");
    SDL_GetWindowSize(sdl2_window,&plat_sdl_screen->w,&plat_sdl_screen->h);
#endif

   printf("  plat_sdl_screen->w=%d,plat_sdl_screen->h=%d\n",plat_sdl_screen->w,plat_sdl_screen->h);


   SDL_GetWindowSize(sdl2_window,&window_w,&window_h);
   printf("SDL_GetWindowSize() window_w=%d,window_h=%d\n",window_w,window_h);

//#ifdef SDL2_0_DEBUG
//  g_menuscreen_w = window_w = plat_sdl_screen->w * 2;
//  g_menuscreen_h = window_h = plat_sdl_screen->h;
//#else
//
//#if 0
//  g_menuscreen_w = window_w = 640;
//  g_menuscreen_h = window_h = 480;
//#else
//  g_menuscreen_w = window_w = plat_sdl_screen->w;
//  g_menuscreen_h = window_h = plat_sdl_screen->h;
//#endif
//
//#endif

#else
//  g_menuscreen_w = window_w = plat_sdl_screen->w;
//  g_menuscreen_h = window_h = plat_sdl_screen->h;
  g_menuscreen_w = 640;
  g_menuscreen_h = 480;
#endif


  // overlay/gl require native bpp in some cases..
#if SDL_MAJOR_VERSION == 2
    plat_sdl_screen = SDL_GetWindowSurface(sdl2_window);
    printf("003 plat_sdl_init : SDL_GetWindowSurface() \n");
    if (plat_sdl_screen == NULL) {
      fprintf(stderr, "003 plat_sdl_init : SDL_GetWindowSurface() failed: %s\n", SDL_GetError());
      goto fail;
    }
#else
  plat_sdl_screen = SDL_SetVideoMode(g_menuscreen_w, g_menuscreen_h,
    0, plat_sdl_screen->flags);

  if (plat_sdl_screen == NULL) {
    fprintf(stderr, "003 SDL_SetVideoMode failed: %s\n", SDL_GetError());
    goto fail;
  }
#endif

#if SDL_MAJOR_VERSION == 1
  /****************************************************************************/
  plat_sdl_overlay = SDL_CreateYUVOverlay(plat_sdl_screen->w, plat_sdl_screen->h,
   SDL_UYVY_OVERLAY, plat_sdl_screen);
  if (plat_sdl_overlay != NULL) {
    printf("plat_sdl: overlay: fmt %x, planes: %d, pitch: %d, hw: %d\n",
      plat_sdl_overlay->format, plat_sdl_overlay->planes, *plat_sdl_overlay->pitches,
      plat_sdl_overlay->hw_overlay);

    if (plat_sdl_overlay->hw_overlay)
      overlay_works = 1;
    else
      fprintf(stderr, "warning: video overlay is not hardware accelerated, "
                      "not going to use it.\n");
    SDL_FreeYUVOverlay(plat_sdl_overlay);
    plat_sdl_overlay = NULL;
  }
  else
    fprintf(stderr, "overlay is not available.\n");
#endif

  // get x11 display/window for GL
#if SDL_MAJOR_VERSION == 2
  vid_drv_name = SDL_GetCurrentVideoDriver();
  printf("plat_sdl_init : SDL_GetCurrentVideoDriver() vid_drv_name=%s\n",vid_drv_name);
#else
  SDL_VideoDriverName(vid_drv_name, sizeof(vid_drv_name));
#endif

#ifdef SDL_VIDEO_DRIVER_X11
  if (strcmp(vid_drv_name, "x11") == 0) {
    SDL_VERSION(&wminfo.version);
#if SDL_MAJOR_VERSION == 2
    ret = SDL_GetWindowWMInfo(sdl2_window,&wminfo); 
#else
    ret = SDL_GetWMInfo(&wminfo);
#endif
    if (ret > 0) {
      display = wminfo.info.x11.display;
      window = (void *)wminfo.info.x11.window;
    }
  }
#else

#if 1
  (void)wminfo;
  ret = SDL_GetWindowWMInfo(sdl2_window, &wminfo); 
  if (ret > 0) {
      gl_setup_wl_information(wminfo.info.wl.display, wminfo.info.wl.surface, wminfo.info.wl.shell_surface);
	  
      printf("wminfo: 0x%x, 0x%x, 0x%x\n", 
	  	wminfo.info.wl.display, wminfo.info.wl.surface, wminfo.info.wl.shell_surface);
  }
#endif

#endif



#ifdef SDL2_0_DEBUG
#if SDL_MAJOR_VERSION == 2
if (isGame) {
#endif
  ret = gl_init(display, window, &gl_quirks);
  printf("plat_sdl_init : gl_init() ret=%d\n",ret);
  if (ret == 0) {
    gl_works = 1;
    printf("plat_sdl_init : gl_finish()\n");
    gl_finish();
  }
#if SDL_MAJOR_VERSION == 2
}
#endif

#else
  ret = gl_init(display, window, &gl_quirks);
  printf("plat_sdl_init : gl_init() ret=%d\n",ret);
  if (ret == 0) {
    gl_works = 1;
    printf("plat_sdl_init : gl_finish()\n");
    gl_finish();
  }
#endif


  i = 0;
  vout_list[i++] = "SDL Window";

  printf("plat_sdl_init : overlay_works=%d\n",overlay_works);
  if (overlay_works) {
    plat_target.vout_method = vout_mode_overlay = i;
    vout_list[i++] = "Video Overlay";
  }
  printf("plat_sdl_init : gl_works=%d\n",gl_works);
  if (gl_works) {
    plat_target.vout_method = vout_mode_gl = i;
    vout_list[i++] = "OpenGL";
  }
  int j;
  for(j=0;j<i;j++) {
    printf("plat_sdl_init : vout_list[%d]=%s\n",j,vout_list[j]);
  }

  plat_target.vout_methods = vout_list;


  printf("- /frontend/libpicofe/plat_sdl_init() end\n");
  return 0;

fail:
#ifdef UI_INTEGRATION
	printf("SDL_Quit() not used. for UI_INTEGRATION\n");
#else
  printf("SDL_Quit()\n");
  SDL_Quit();
#endif
	printf("- /frontend/libpicofe/plat_sdl_init() fail\n");
  return -1;
}


void plat_sdl_finish(void)
{
printf("+ /frontend/libpicofe/plat_sdl_finish()\n");
#if SDL_MAJOR_VERSION == 1
  if (plat_sdl_overlay != NULL) {
    SDL_FreeYUVOverlay(plat_sdl_overlay);
    plat_sdl_overlay = NULL;
  }
#endif
  if (plat_sdl_gl_active) {
    gl_finish();
    plat_sdl_gl_active = 0;
  }
  // restore back to initial resolution
  // resolves black screen issue on R-Pi
  if (strcmp(vid_drv_name, "x11") != 0) {
#if SDL_MAJOR_VERSION == 2
    SDL_GetWindowSurface(sdl2_window);
    printf("005 /frontend/libpicofe/SDL_GetWindowSurface() \n");
#else
    SDL_SetVideoMode(fs_w, fs_h, 16, SDL_SWSURFACE);
    printf("SDL_SetVideoMode\n");
#endif
  }

#ifdef UI_INTEGRATION
	printf("SDL_Quit() not used. for UI_INTEGRATION\n");
#else
  printf("SDL_Quit()\n");
  SDL_Quit();
#endif
	
	printf("- /frontend/libpicofe/plat_sdl_finish()\n");
}

void plat_sdl_overlay_clear(void)
{
printf("plat_sdl_overlay_clear()\n");
#if SDL_MAJOR_VERSION == 1
  int pixels = plat_sdl_overlay->w * plat_sdl_overlay->h;
  int *dst = (int *)plat_sdl_overlay->pixels[0];
  int v = 0x10801080;

  for (; pixels > 0; dst += 4, pixels -= 2 * 4)
    dst[0] = dst[1] = dst[2] = dst[3] = v;

  for (; pixels > 0; dst++, pixels -= 2)
    *dst = v;
#endif
}

// vim:shiftwidth=2:expandtab
