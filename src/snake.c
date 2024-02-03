#include "snake.h"
#include "timer.h"
#include "window.h"
#include "raylib.h"
#include <stdbool.h>

void init_snake(Snake *snake) {
  snake->length = 2;
  snake->score = 0;
  snake->direction = (Dir)GetRandomValue(0, 3);
  snake->pos[0].x = GetRandomValue(8, 24);
  snake->pos[0].y = GetRandomValue(6, 18);
}

void draw_snake(Snake *snake) {
  Vector2 *head = &snake->pos[0];

  // Draw body
  for (int i = 1; i < snake->length; i++) {
    DrawRectangle(snake->pos[i].x * CELL_WIDTH, snake->pos[i].y * CELL_HEIGHT,
                  CELL_WIDTH, CELL_HEIGHT, LIME);
  }

  // Draw head
  DrawRectangle(head->x * CELL_WIDTH, head->y * CELL_HEIGHT, CELL_WIDTH,
                CELL_HEIGHT, DARKGREEN);
}

void init_apple(Apple *apple, Snake *snake, Timer *timer) {
  apple->timer = *timer;

  do {
    apple->pos.x = GetRandomValue(0, COLS - 1);
    apple->pos.y = GetRandomValue(0, ROWS - 1);

    bool valid_pos = true;

    for (int i = 0; i < snake->length; i++) {
      if (apple->pos.x == snake->pos[i].x && apple->pos.y == snake->pos[i].y) {
        valid_pos = false;
        break;
      }
    }

    if (valid_pos) {
      break;
    }

  } while (true);
}

void spawn_apple(Apple *apple, Snake *snake) {
  if (apple->first_render) {
    init_apple(apple, snake, &apple->timer);
    apple->first_render = false;
    apple->eaten = false;
  } else {
    if (apple->eaten && timer_done(&apple->timer)) {
      reset_timer(&apple->timer, APPLE_SPAWN_DELAY);
      init_apple(apple, snake, &apple->timer);
      apple->eaten = false;
    }
  }

  if (!apple->timer.active && !timer_done(&apple->timer))
    draw_textured_rectangle(apple->pos, apple->texture, WHITE);
}

void draw_textured_rectangle(Vector2 position, Texture2D texture, Color tint) {
  Rectangle dest_rect = {position.x * CELL_WIDTH, position.y * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT};
  Rectangle source_rect = {0, 0, texture.width, texture.height};
  Vector2 origin = {0, 0};
  DrawTexturePro(texture, source_rect, dest_rect, origin, 0, tint);
}
