#include <stdio.h>
#include <stdlib.h>
#include <EGL/egl.h>
#include <GLES/gl.h>

#include "gl.h"
#include "gl_platform.h"

#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include <EGL/egl.h>
#include <wayland-client.h>
#include <wayland-egl.h>
#include <libdrm/drm_fourcc.h>
//#include <xf86drm.h>
//#include <xf86drmMode.h>


#ifdef VCOS_VERSION

/*
 * hacks for Broadcom VideoCore / Raspberry Pi..
 * Why do I have to do this proprietary API stuff,
 * couldn't they implement EGL properly? D:
 */
#include <bcm_host.h>
//#include <X11/Xlib.h>
#include <dlfcn.h>

//static Display *x11display;
//static Window x11window;
static DISPMANX_DISPLAY_HANDLE_T m_dispmanDisplay;
static EGL_DISPMANX_WINDOW_T m_nativeWindow;

static void *x11lib;
#define FPTR(f) typeof(f) * p##f
//static FPTR(XGetGeometry);
//static FPTR(XGetWindowAttributes);
//static FPTR(XTranslateCoordinates);

static void get_window_rect(VC_RECT_T *rect)
{
  //	XWindowAttributes xattrs_root;
	uint32_t disp_w = 0, disp_h = 0;
	int dx = 0, dy = 0;
	unsigned int dw = 0, dh = 0, dummy;
	//	Window root, dummyw;

	graphics_get_display_size(0, &disp_w, &disp_h);
	if (disp_w == 0 || disp_h == 0)
		fprintf(stderr, "ERROR: graphics_get_display_size is broken\n");

	// default to fullscreen
	rect->x = rect->y = 0;
	rect->width = disp_w;
	rect->height = disp_h;

	//	if (x11display == NULL || x11window == 0)
		return; // use fullscreen

		//	pXGetGeometry(x11display, x11window, &root, &dx, &dy, &dw, &dh,
		//		&dummy, &dummy);
		//	pXGetWindowAttributes(x11display, root, &xattrs_root);

		//	if (dw == xattrs_root.width && dh == xattrs_root.height)
		//		return; // use fullscreen

		//	pXTranslateCoordinates(x11display, x11window, root,
		//		dx, dy, &dx, &dy, &dummyw);

	// how to deal with that weird centering thing?
	// this is not quite right..
		//	dx += (disp_w - xattrs_root.width) / 2;
		//	dy += (disp_h - xattrs_root.height) / 2;

		//	rect->x = dx;
		//	rect->y = dy;
		//	rect->width = dw;
		//	rect->height = dh;
}

static void submit_rect(void)
{
	DISPMANX_UPDATE_HANDLE_T m_dispmanUpdate;
	DISPMANX_ELEMENT_HANDLE_T m_dispmanElement;
	VC_RECT_T srcRect = { 0, }; // unused, but we segfault without passing it??
	VC_RECT_T dstRect;

	get_window_rect(&dstRect);

	m_dispmanDisplay = vc_dispmanx_display_open(0);
	m_dispmanUpdate = vc_dispmanx_update_start(0);

	m_dispmanElement = vc_dispmanx_element_add(m_dispmanUpdate,
		m_dispmanDisplay, 0, &dstRect, 0, &srcRect,
		DISPMANX_PROTECTION_NONE, 0, 0, DISPMANX_NO_ROTATE);

	m_nativeWindow.element = m_dispmanElement;
	m_nativeWindow.width = dstRect.width;
	m_nativeWindow.height = dstRect.height;

	vc_dispmanx_update_submit_sync(m_dispmanUpdate);
}

int gl_platform_init(void **display, void **window, int *quirks)
{
  //	x11display = NULL;
  //	x11window = 0;

	//	x11lib = dlopen("libX11.so.6", RTLD_LAZY);
	//	if (x11lib != NULL) {
	//		pXGetGeometry = dlsym(x11lib, "XGetGeometry");
	//		pXGetWindowAttributes = dlsym(x11lib, "XGetWindowAttributes");
	//		pXTranslateCoordinates = dlsym(x11lib, "XTranslateCoordinates");
	//		if (pXGetGeometry != NULL && pXGetWindowAttributes != NULL
	//		    && pXTranslateCoordinates != NULL)
	//		{
	//			x11display = *display;
	//			x11window = (Window)*window;
	//		}
	//	}

	bcm_host_init();
	submit_rect();

	*display = EGL_DEFAULT_DISPLAY;
	*window = &m_nativeWindow;
	*quirks |= GL_QUIRK_ACTIVATE_RECREATE;

	return 0;
}

void gl_platform_finish(void)
{
	vc_dispmanx_display_close(m_dispmanDisplay);
	bcm_host_deinit();

	if (x11lib) {
		dlclose(x11lib);
		x11lib = NULL;
	}

	//	x11display = NULL;
	//	x11window = 0;
}

#else

#if 1
struct wayland_info {
	struct wl_display *display;
	struct wl_registry *registry;
	struct wl_compositor *compositor;
	struct wl_shell *shell;

	bool roundtrip_needed;

	struct {
		struct wl_shell_surface	*shell_surface;
		struct wl_surface *surface;
		struct wl_egl_window *egl_window;
		EGLSurface egl_surface;
	} surface;

};
#endif

#if 0
static void
global_handler(void *data, struct wl_registry *registry, uint32_t id,
	       const char *interface, uint32_t version)
{
	struct wayland_info *info = data;

	if (strcmp(interface, "wl_compositor") == 0) {
		info->compositor = wl_registry_bind(registry, id,
						 &wl_compositor_interface, 1);
	}
	else if (strcmp(interface, "wl_shell") == 0) {
		info->shell = wl_registry_bind(registry, id,
					 &wl_shell_interface, 1);
	}
}

static void
global_remove_handler(void *data, struct wl_registry *registry, uint32_t name)
{

}

static const struct wl_registry_listener registry_listener = {
	global_handler,
	global_remove_handler
};

static void
handle_ping (void *data, struct wl_shell_surface *shell_surface,
    uint32_t serial)
{
	wl_shell_surface_pong (shell_surface, serial);
}


static void
handle_configure (void *data, struct wl_shell_surface *shell_surface,
    uint32_t edges, int32_t width, int32_t height)
{
	struct wayland_info *info = data;

	wl_egl_window_resize (info->surface.egl_window, width, height, 0, 0);
	printf("handle_configure ReSize Window[%d, %d]\n", width, height);
}

static void
handle_popup_done (void *data, struct wl_shell_surface *shell_surface)
{
}

static const struct wl_shell_surface_listener shell_surface_listener = {
	handle_ping,
	handle_configure,
	handle_popup_done
};

static void
create_surface(struct wayland_info *info)
{
	info->surface.shell_surface =  wl_shell_get_shell_surface (info->shell, info->surface.surface);
	wl_shell_surface_add_listener(info->surface.shell_surface, &shell_surface_listener, info);
	wl_shell_surface_set_toplevel(info->surface.shell_surface);
}

int __gl_platform_init(void **display, void **window, int *quirks)
{

	struct wayland_info *info = malloc(sizeof(struct wayland_info));
	
	if (info == NULL)
		return 0;

	info->display = wl_display_connect(NULL);
	if (!info->display) {
		printf("wl_display_connect is failed\n");
		exit(EXIT_SUCCESS);
	}

	info->registry = wl_display_get_registry(info->display);
	wl_registry_add_listener(info->registry, &registry_listener, info);
	wl_display_dispatch (info->display);
	wl_display_roundtrip(info->display);

	*display = info->display;

	info->surface.surface = wl_compositor_create_surface(info->compositor);
	create_surface(info);

	wl_display_roundtrip(info->display);

	info->surface.egl_window = wl_egl_window_create(info->surface.surface,
							1280,
						   	720);
	*window = info->surface.egl_window;
	
	return 0;
}

void gl_platform_finish(void)
{
}
#endif

#if 1
#if 1
static struct wl_display * aa_display;
static struct wl_shell_surface *aa_shell_surface;
static struct wl_surface *aa_surface;
static struct wl_egl_window *aa_window;

void gl_setup_wl_information(struct wl_display * idisplay, 
	struct wl_surface *isurface, 
	struct wl_shell_surface *ishell_surface)
{
	aa_display = idisplay;
	aa_surface = isurface;
	aa_shell_surface = ishell_surface;

	printf("gl_setup_wl_information, display:0x%x, surface: 0x%x\n", 
		aa_display, aa_surface);

}
#endif

#if 0
static struct wl_display * plat_display;
static struct wl_surface *plat_surface;
static struct wl_egl_window *plat_window;

void gl_setup_wl_information(struct wl_display * idisplay, 
	struct wl_surface *isurface)
{
	plat_display = idisplay;
	plat_surface = isurface;

	printf("aaaa gl_setup_wl_information, display:0x%x, surface: 0x%x\n", 
		plat_display, plat_surface);

}
#endif

int gl_platform_init(void **display, void **window, int *quirks)
{
#if 1
	struct wayland_info *info = malloc(sizeof(struct wayland_info));
	
	if (info == NULL)
		return 0;

	info->display = aa_display;
	if (!info->display) {
		printf("wl_display_connect is failed\n");
	}


	*display = info->display;

	info->surface.surface = aa_surface;
	info->surface.shell_surface = aa_shell_surface;


	printf("gl_platform_init before window_create\n");

	info->surface.egl_window = wl_egl_window_create(info->surface.surface,
							960,
						   	720);
	*window = info->surface.egl_window;
	
	printf("gl_platform_init, display:0x%x, window: 0x%x\n", 
		info->display, info->surface.egl_window);
	#endif
	
	//plat_window = wl_egl_window_create(plat_surface, 1280, 720); //640, 480);
	//*display = plat_display;
	//*window = plat_window;
	
	return 0;
}

void gl_platform_finish(void)
{
    //wl_egl_window_destroy(plat_window);
}

#endif

#endif
