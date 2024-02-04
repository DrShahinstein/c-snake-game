#include "score.h"
#include "raylib.h"
#include <stdio.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#endif

void ensure_dir_exists(const char *dir) {
#ifdef _WIN32
  if (_mkdir(dir) == 0) {
    printf("INFO: Directory %s created\n", dir);
  }
#else
  struct stat st = {0};
  if (stat(dir, &st) == -1) {
    mkdir(dir, 0700);
    printf("INFO: Directory %s created\n", dir);
  }
#endif
}

void init_score(void) {
  FILE *f = fopen(SCORE_TXT_PATH, "a+");

  if (f != NULL) {
    fseek(f, 0, SEEK_END);
    long size = ftell(f);

    if (size == 0 || (size == 1 && fgetc(f) == '\n')) {
      fprintf(f, "0");
    }

    fclose(f);
    printf("INFO: %s initialized\n", SCORE_TXT_PATH);
  } else {
    ensure_dir_exists(SCORE_DIR_PATH);

    f = fopen(SCORE_TXT_PATH, "a+");

    if (f != NULL) {
      fseek(f, 0, SEEK_END);
      long size = ftell(f);

      if (size == 0 || (size == 1 && fgetc(f) == '\n')) {
        fprintf(f, "0");
      }

      fclose(f);
      printf("INFO: %s initialized\n", SCORE_TXT_PATH);
    } else {
      fprintf(stderr, IO_WARNING_1);
    }
  }
}

int load_highest_score(void) {
  FILE *f = fopen(SCORE_TXT_PATH, "r");

  if (f == NULL) {
    fprintf(stderr, IO_WARNING_2);
    return 0;
  }

  int highest_score = 0;
  if (fscanf(f, "%d", &highest_score) != 1) {
    fprintf(stderr, IO_WARNING_2);
    highest_score = -1;
  }
  fclose(f);

  return highest_score;
}

void save_highest_score(int score) {
  int highest = load_highest_score();

  FILE *f = fopen(SCORE_TXT_PATH, "w");

  if (f == NULL) {
    fprintf(stderr, IO_WARNING_3);
    return;
  }

  if (score > highest)
    fprintf(f, "%d", score);
  else
    fprintf(f, "%d", highest);

  fclose(f);
}

void draw_score(int current_score, int highest_score) {
  DrawText(TextFormat("Current Score: %d", current_score), SCORE_POSX,
           SCORE_POSY, SCORE_FONTSIZE, BLACK);

  if (highest_score == -1) {
    DrawText(TextFormat("Highest Score: (-1) => \n\n%s is invalid", SCORE_TXT_PATH),
             SCORE_POSX, SCORE_POSY + 30, SCORE_FONTSIZE, RED);
  } else {
    DrawText(TextFormat("Highest Score: %d", highest_score), SCORE_POSX,
             SCORE_POSY + 30, SCORE_FONTSIZE, BLACK);
  }
}
