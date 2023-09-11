#include <X11/Xlib.h>
#include <stdlib.h>
#include <unistd.h>
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
  XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("X")), Mod1Mask, DefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
  XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("H")), Mod1Mask, DefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
  XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("S")), Mod1Mask, DefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
  while (1) {
    XNextEvent(display, &event);
    if (event.xkey.keycode == XKeysymToKeycode(display, XStringToKeysym("Q"))) {
      free(windows);
      XCloseDisplay(display);
      return 1;
    } else if (event.xkey.keycode == XKeysymToKeycode(display, XStringToKeysym("J")) && length > 0) {
      if (current > 0) {
        current--;
      } else {
        current = length - 1;
      }
    } else if (event.xkey.keycode == XKeysymToKeycode(display, XStringToKeysym("K")) && length > 0) {
      if (current < length - 1) {
        current++;
      } else {
        current = 0;
      }
    } else if (event.xkey.keycode == XKeysymToKeycode(display, XStringToKeysym("Return"))) {
      Window window = XCreateSimpleWindow(display, root, 0, 0, DisplayWidth(display, DefaultScreen(display)), DisplayHeight(display, DefaultScreen(display)), 1, BlackPixel(display, 0), WhitePixel(display, 0));
      XMapWindow(display, window);
      pid_t pid = fork();
      if (pid == 0) {
        execlp("st", "st", NULL);
      } else if (pid > 0) {
        windows = realloc(windows, (length + 1) * sizeof(Window));
        windows[length++] = window;
      }
    } else if (event.xkey.keycode == XKeysymToKeycode(display, XStringToKeysym("X"))) {
      for (size_t i = current; i < length; i++) {
        windows[i] = windows[i + 1];
      }
      XDestroyWindow(display, windows[current]);
      length--;
      windows = realloc(windows, (length + 1) * sizeof(Window));
    } else if (event.xkey.keycode == XKeysymToKeycode(display, XStringToKeysym("H")) && length > 0) {
      XUnmapWindow(display, windows[current]);
    } else if (event.xkey.keycode == XKeysymToKeycode(display, XStringToKeysym("S")) && length > 0) {
      XMapWindow(display, windows[current]);
    }
    XFlush(display);
  }
}
