#include "timer.h"
#include "raylib.h"
#include <stdbool.h>

void start_timer(Timer *timer, double duration) {
  timer->lifetime = duration;
  timer->active = true;
}

void reset_timer(Timer *timer, double duration) {
  timer->active = false;
  timer->lifetime = duration;
}

void update_timer(Timer* timer) {
  if (timer->active && timer->lifetime > 0) {
    timer->lifetime -= GetFrameTime();
  }
}

bool timer_done(Timer *timer) {
  return timer->lifetime <= 0;
}

