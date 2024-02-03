#include "controllers.h"
#include "snake.h"
#include "timer.h"
#include "window.h"
#include <raylib.h>
#include <stdbool.h>

void draw_grid(int cols, int rows, float cell_width, float cell_height) {
  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      DrawRectangleLines(i * cell_width, j * cell_height, cell_width,
                         cell_height, LIGHTGRAY);
    }
  }
}

void handle_keys(Snake *snake, GameState *state) {
  if (IsKeyDown(KEY_SPACE)) {
    *state = PAUSE;
  } else if (IsKeyDown(KEY_RIGHT) && snake->direction != LEFT) {
    snake->direction = RIGHT;
  } else if (IsKeyDown(KEY_LEFT) && snake->direction != RIGHT) {
    snake->direction = LEFT;
  } else if (IsKeyDown(KEY_UP) && snake->direction != DOWN) {
    snake->direction = UP;
  } else if (IsKeyDown(KEY_DOWN) && snake->direction != UP) {
    snake->direction = DOWN;
  }
}

void update_game(Snake *snake, Apple *apple, GameState *state) {
  Vector2 *snake_head = &snake->pos[0];

  for (int i = snake->length - 1; i > 0; i--) {
    snake->pos[i] = snake->pos[i - 1];
  }

  switch (snake->direction) {
  case UP:
    snake_head->y -= 1;
    break;
  case DOWN:
    snake_head->y += 1;
    break;
  case LEFT:
    snake_head->x -= 1;
    break;
  case RIGHT:
    snake_head->x += 1;
    break;
  default:
    break;
  }

  // Apple eaten?
  if (snake_head->x == apple->pos.x && snake_head->y == apple->pos.y) {
    start_timer(&apple->timer, apple->timer.lifetime);
    PlaySound(apple->eating_sound);
    snake->score++;
    snake->length++;
    apple->eaten = true;
  }

  // Collusion happened?
  if (snake_head->x < 0     ||
      snake_head->x >= COLS ||
      snake_head->y < 0     ||
      snake_head->y >= ROWS)
  {
    *state = OVER;
    return;
  }

  // Self collusion?
  for (int i = 1; i < snake->length; i++) {
    if (snake_head->x == snake->pos[i].x && snake_head->y == snake->pos[i].y) {
      *state = OVER;
      return;
    }
  }

  update_timer(&apple->timer);
  draw_snake(snake);
}

void restart_game(Snake *snake, GameState *state) {
  init_snake(snake);
  *state = PLAYING;
}
