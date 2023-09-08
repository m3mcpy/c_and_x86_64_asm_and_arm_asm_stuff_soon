#include <X11/Xlib.h>
#include <stdlib.h>
int main(void) {
  Display *display = XOpenDisplay(NULL);
  Window root = DefaultRootWindow(display);
  XEvent event;
  size_t current = 0;
  size_t length = 0;
  Window *windows = NULL;
  XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("Q")), Mod1Mask, DefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
  XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("J")), Mod1Mask, DefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
  XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("K")), Mod1Mask, DefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
  XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("Return")), Mod1Mask, DefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
  while (1) {
    if (event.xkey.keycode == XKeysymToKeycode(display, XStringToKeysym("Q"))) {
      free(windows);
      XCloseDisplay(display);
      return 1;
    } else if (event.xkey.keycode == XKeysymToKeycode(display, XStringToKeysym("J"))) {
      if (current > 0) {
        current--;
      } else {
        current = length;
      }
    } else if (event.xkey.keycode == XKeysymToKeycode(display, XStringToKeysym("K"))) {
      if (current < length) {
        current++;
      } else {
        current = 0;
      }
    } else if (event.xkey.keycode == XKeysymToKeycode(display, XStringToKeysym("Return"))) {
      Window window = XCreateSimpleWindow(display, root, 100, 100, 400, 300, 1, BlackPixel(display, 0), WhitePixel(display, 0));
      XMapWindow(display, window);
      windows = realloc(windows, (length + 1) * sizeof(Window));
    }
  }
}
