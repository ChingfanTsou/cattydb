#ifndef _CREATETABLE_H
#define _CREATETABLE_H
#endif

#include <stdio.h>
#include <string.h>
#include "buffer.h"

#define TABLE_NAME_LEN 256

void create_table(const char* table_name);
void create_col(const char* col_name,const char* col_type,int num,int is_primary);
void create_table_on_close();
