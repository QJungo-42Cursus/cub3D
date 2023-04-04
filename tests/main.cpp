#include "./gtest/gtest.h"

extern "C" {
#include "../src/cube3D.h"
}
#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XShm.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <unistd.h>

int main(int argc, char **argv) {
  Display *display = XOpenDisplay("");
  printf("i: %p\n", display);
  if (display == NULL) {
    printf("display is null\n");
  } else {
    XCloseDisplay(display);
  }
  //::testing::InitGoogleTest(&argc, argv);
  // return RUN_ALL_TESTS();
}
