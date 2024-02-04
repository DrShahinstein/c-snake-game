#ifndef SCORE_H
#define SCORE_H

#include "working_dir.h"

#define SCORE_DIR_PATH WDIR "data/"
#define SCORE_TXT_PATH WDIR "data/highest_score.txt"
#define SCORE_POSX 10
#define SCORE_POSY 8
#define SCORE_FONTSIZE 20

#define IO_WARNING_1 "ERROR: Error while initializing score\n"
#define IO_WARNING_2 "WARNING: Error while reading score\n"
#define IO_WARNING_3 "WARNING: Error while writing score\n"

void init_score(void);
int load_highest_score(void);
void save_highest_score(int score);
void draw_score(int current_core, int highest_core);

#endif
