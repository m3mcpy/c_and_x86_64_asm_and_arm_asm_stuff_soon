#include <X11/Xlib.h>
int main(void) {
  Display *display = XOpenDisplay(NULL);
  XEvent event;
  size_t current = 0;
  size_t length = 0;
  XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("Q")), Mod1Mask, DefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
  XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("J")), Mod1Mask, DefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
  XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("K")), Mod1Mask, DefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
  while (1) {
    if (event.xkey.keycode == XKeysymToKeycode(display, XStringToKeysym("Q"))) {
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
    }
  }
}
