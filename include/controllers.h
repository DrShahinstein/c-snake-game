#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include "snake.h"
#include "timer.h"

#define RESTART_MSG "Press enter to restart"
#define PAUSE_MSG "Game paused"
#define PAUSE_OVERLAY (Color) { 128, 128, 128, 128 }
#define FONT_SIZE 40

typedef enum {
  PLAYING,
  PAUSE,
  OVER,
} GameState;

void draw_grid(int cols, int rows, float cell_width, float cell_height);
void init_snake(Snake *snake);
void handle_keys(Snake *snake, GameState *state);
void update_game(Snake *snake, Apple *apple, GameState *state);
void restart_game(Snake *snake, GameState *state);

#endif
