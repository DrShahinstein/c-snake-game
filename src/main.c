#include "controllers.h"
#include "score.h"
#include "snake.h"
#include "timer.h"
#include "window.h"
#include "raylib.h"
#include <stdbool.h>
#include <time.h>

static void draw_overlay(Color color) {
  DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color);
}

int main(void) {
  init_score();                               // To load highest score properly
  InitAudioDevice();                          // To load sounds properly
  ChangeDirectory(GetApplicationDirectory()); // To load assets properly

  GameState state = PLAYING;

  Timer apple_spawn_delay;
  apple_spawn_delay.lifetime = APPLE_SPAWN_DELAY;
  apple_spawn_delay.active = false;

  Snake snake;
  init_snake(&snake);

  Apple apple;
  init_apple(&apple, &snake, &apple_spawn_delay);
  apple.first_render = true;
  apple.eaten = true;

  SetRandomSeed((unsigned)time(NULL));
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(20);

  apple.texture = LoadTexture(APPLE_TEXTURE_PATH);
  apple.eating_sound = LoadSound(APPLE_SOUND_PATH);

  SetSoundVolume(apple.eating_sound, 0.6); // 0.0 - 1.0

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    draw_grid(COLS, ROWS, CELL_WIDTH, CELL_HEIGHT);

    switch (state) {
    case PAUSE:
      draw_overlay(PAUSE_OVERLAY);
      draw_snake(&snake);          // snake's last position
      spawn_apple(&apple, &snake); // apple's last position

      draw_score(snake.score, load_highest_score());

      DrawText(PAUSE_MSG, HALF_SCREEN_W - MeasureText(PAUSE_MSG, FONT_SIZE) / 2,
               HALF_SCREEN_H - 35, FONT_SIZE, BLACK);

      if (IsKeyPressed(KEY_ENTER))
        state = PLAYING;
      break;

    case OVER:
      draw_snake(&snake);
      save_highest_score(snake.score);

      DrawText(RESTART_MSG,
               HALF_SCREEN_W - MeasureText(RESTART_MSG, FONT_SIZE) / 2,
               HALF_SCREEN_H - 35, FONT_SIZE, RED);

      if (IsKeyPressed(KEY_ENTER))
        restart_game(&snake, &state);
      break;

    case PLAYING:
      handle_keys(&snake, &state);
      update_game(&snake, &apple, &state);
      spawn_apple(&apple, &snake);
      break;
    }

    EndDrawing();
  }

  save_highest_score(snake.score);

  UnloadTexture(apple.texture);
  UnloadSound(apple.eating_sound);

  CloseWindow();

  return 0;
}
