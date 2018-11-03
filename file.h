#pragma once
#ifndef __FILE_H_
#define __FILE_H_
void openfile(void);
void newfile(void);//新建文件
void welcome(void);
void savefile(void);
void repl(void);
void searc(void);
bool exitn(void);
bool mouseopen(int x, int y);
bool mousenew(int x, int y);
bool mouseexit(int x, int y);

bool mousesave(int x, int y);
bool mousesaveas(int x, int y);
bool mousenotsave(int x, int y);
bool backmain(int x, int y);

bool save(void);
void route(void);//保存文件路径
#endif