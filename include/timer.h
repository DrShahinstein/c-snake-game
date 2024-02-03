#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>

typedef struct {
  double lifetime;
  bool active;
} Timer;

void start_timer(Timer *timer, double lifetime);
void reset_timer(Timer *timer, double duration);
void update_timer(Timer *timer);
bool timer_done(Timer *timer);
double get_elapsed(Timer *timer);

#endif
