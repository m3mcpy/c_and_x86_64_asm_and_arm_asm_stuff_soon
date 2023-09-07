#include <X11/Xlib.h>
int main(void) {
  Display *display = XOpenDisplay(NULL);
  XEvent event;
  XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("Q")), Mod1Mask, DefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
  while (1) {
    if (event.xkey.keycode == XKeysymToKeycode(display, XStringToKeysym("Q"))) {
      XCloseDisplay(display);
      return 1;
    }
  }
}
