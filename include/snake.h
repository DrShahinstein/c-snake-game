#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"
#include "timer.h"
#include "working_dir.h"

#define APPLE_TEXTURE_PATH WDIR "assets/apple.png"
#define APPLE_SOUND_PATH   WDIR "assets/apple.wav"
#define APPLE_SPAWN_DELAY 1.0

typedef struct {
  Texture2D texture;
  Sound eating_sound;
  Vector2 pos;
  bool eaten;
  bool first_render;
  Timer timer;
} Apple;

typedef enum {
  LEFT,
  RIGHT,
  UP,
  DOWN,
} Dir;

typedef struct {
  Vector2 pos[100];
  Dir direction;
  int length;
  int score;
} Snake;

void init_snake(Snake *snake);
void draw_snake(Snake *snake);
void init_apple(Apple *apple, Snake *snake, Timer *timer);
void spawn_apple(Apple *apple, Snake *snake);
void draw_textured_rectangle(Vector2 position, Texture2D texture, Color tint);

#endif
