/** \file ALF_db.h
* Database.
**/

#ifndef ALF_db_h
#define ALF_db_h

#include "ALF_common.h"

#include <stdint.h>
// #include <stdbool.h>
// #include <stddef.h>

typedef struct{
    char *filename;
    uint8_t columns;
    char **columnsName;

} ALF_db;


ALF_db *ALF_db_create(const char *name);
ALF_db *ALF_db_open(const char *name);
void ALF_db_free(ALF_db *handler);

#endif /* ALF_db_h */
