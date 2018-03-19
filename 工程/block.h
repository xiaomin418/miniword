#ifndef __BLOCK_H_
#define __BLOCK_H_

bool copy(void);
bool block_fun(void);//块操作功能
void hotkey(void);
struct Location get_location(void);
char func(void);
bool live_blk(struct Location start,struct Location end);//实时定位块选，方便print变色 
#endif
