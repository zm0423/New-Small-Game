#ifndef SL_H
#define SL_H

#include "table.h"
#include "../file.h"

namespace miner
{

void miner_main(data_use &du);

int menu(void);

void instruction(void);

void about(void);

const int DIFF_EXIT = -1;
enum{NORMAL, EASY, HARD, C_ONE, C_TWO};
const int DIFF_NUM[5] = {19, 14, 24, 29, 34};

int difficulty(void);

void print_all(const table &ta);

int operatekey(table &ta, int key);

int end(const table &ta, data_use &du, bool win);

bool pause(const table &ta);

} //namespace miner


#endif
