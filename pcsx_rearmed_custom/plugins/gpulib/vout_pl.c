/*
 * video output handling using plugin_lib
 * (C) Gražvydas "notaz" Ignotas, 2011
 *
 * This work is licensed under the terms of any of these licenses
 * (at your option):
 *  - GNU GPL, version 2 or later.
 *  - GNU LGPL, version 2.1 or later.
 * See the COPYING file in the top-level directory.
 */

#include <string.h>
#include "gpu.h"
#include "../../frontend/plugin_lib.h"

static const struct rearmed_cbs *cbs;

int vout_init(void)
{
  return 0;
}

int vout_finish(void)
{
  return 0;
}

static void check_mode_change(int force)
{
  static uint32_t old_status;
  static int old_h;
  int w = gpu.screen.hres;
  int h = gpu.screen.h;
  int w_out = w;
  int h_out = h;

  gpu.state.enhancement_active =
    gpu.get_enhancement_bufer != NULL && gpu.state.enhancement_enable
    && w <= 512 && h <= 256 && !gpu.status.rgb24;

  if (gpu.state.enhancement_active) {
    w_out *= 2;
    h_out *= 2;
  }

  // width|rgb24 change?
  if (force || (gpu.status.reg ^ old_status) & ((7<<16)|(1<<21)) || h != old_h)
  {
    old_status = gpu.status.reg;
    old_h = h;

    cbs->pl_vout_set_mode(w_out, h_out, w, h, gpu.status.rgb24 ? 24 : 16);
  }
}

extern int g_gpu_patch_flag;
void vout_update(void)
{
  int x = gpu.screen.x & ~1; // alignment needed by blitter
  int y = gpu.screen.y;
  int w = gpu.screen.w;
  int h = gpu.screen.h;
  uint16_t *vram = gpu.vram;
  int vram_h = 512;

  if (w == 0 || h == 0)
    return;

  check_mode_change(0);
  if (gpu.state.enhancement_active)
    vram = gpu.get_enhancement_bufer(&x, &y, &w, &h, &vram_h);

  if (y + h > vram_h) {
    if (y + h - vram_h > h / 2) {
      // wrap
      h -= vram_h - y;
      y = 0;
    }
    else
      // clip
      h = vram_h - y;
  }

  if (g_gpu_patch_flag & GPU_PATCH_IS_FF7) {
    if (gpu.screen.y2 - gpu.screen.y1 == 224) {
      y -= 8;
      h = gpu.screen.h = 240;
    }
  }else if(g_gpu_patch_flag & GPU_PATCH_IS_MR_DRILLER_JP) {
    if((gpu.screen.x1==830) && (gpu.screen.x2==3290) && (w==246)) {
      w = 208;
    }
  }

  vram += y * 1024 + x;

  cbs->pl_vout_flip(vram, 1024, gpu.status.rgb24, w, h);

  if (gpu.vram2 != NULL) {
    uint16_t *p_vram2 = gpu.vram2;
    p_vram2 += y * 1024 + x;
    for (int i = h-1; i >= 0; i--) {
      uint16_t *s_2 = p_vram2 + 1024*i;
      memset((char*)s_2, 0, w * (gpu.status.rgb24 ? 3 : 2));
    }
  }
}

void vout_blank(void)
{
  int w = gpu.screen.hres;
  int h = gpu.screen.h;

  check_mode_change(0);
  if (gpu.state.enhancement_active) {
    w *= 2;
    h *= 2;
  }
  cbs->pl_vout_flip(NULL, 1024, gpu.status.rgb24, w, h);
}

long GPUopen(void **unused)
{
  gpu.frameskip.active = 0;
  gpu.frameskip.frame_ready = 1;

  cbs->pl_vout_open();
  check_mode_change(1);
  vout_update();
  return 0;
}

long GPUclose(void)
{
  cbs->pl_vout_close();
  return 0;
}

void vout_set_config(const struct rearmed_cbs *cbs_)
{
  cbs = cbs_;
}

// vim:shiftwidth=2:expandtab
