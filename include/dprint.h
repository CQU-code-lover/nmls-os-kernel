#ifndef _DPRINT_H_
#define _DPRINT_H_
#include "types.h"
#include "common.h"
#include "console.h"

void printkbasic(char *format_str,char *m); //基础打印函数 

void printk(char *input_str,...);

void printk_color(char *format_str,real_color_t back, real_color_t fore,...);

void insert_str(char *inserted_str,char *inserting_str,uint32_t offset);
#endif
