#include "ALF_std/ALF_db.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <errno.h>

#define ALF_DB_HEADER_SIZE 16
#define HEADER_0_5 "ALFDB\0"
/* Header:
 *  0 'A'
 *  1 'L'
 *  2 'F'
 *  3 'D'
 *  4 'B'
 *  5 '\0'
 *  6 ColumnsAmount
 *  7 Upper half of maxStr. 16 bits.
 *  8 Lower half of maxStr. 16 bits.
 *  9 0
 * 10 0
 * 11 0
 * 12 0
 * 13 0
 * 14 0
 * 15 0
*/


int fgetString(FILE *_file, int _n, char *_dst){
    int i, c = fgetc(_file);
    for(i = 0; i < _n && c != 0 && c != EOF; i++){
        _dst[i] = c;
        c = fgetc(_file);
    }
    _dst[i] = 0;
    return i;
}


ALF_db *ALF_db_init(const char *filename, uint8_t columns, uint16_t max_str_size){
    printf("%i, %i\n", columns, max_str_size);

    ALF_db *handler = malloc(sizeof(ALF_db));
    if(handler == NULL){
        return NULL;
    }
    handler->filename = ALF_allocAndCopy(filename, strlen(filename) + 1);
    if(handler->filename == NULL){
        free(handler);
        return NULL;
    }

    handler->columns = columns;
    handler->columnsName = malloc(sizeof(char *) * (columns + 1));
    if(handler->columnsName == NULL){
        free(handler->filename);
        free(handler);
        return NULL;
    }
    for(int i = 0; i < columns; ++i){
        handler->columnsName[i] = malloc(sizeof(char) * max_str_size);
        if(handler->columnsName[i] == NULL){
            for(; i > 0; ){
                free(handler->columnsName[--i]);
            }
            free(handler->columnsName);
            free(handler->filename);
            free(handler);
            return NULL;
        }
    }
    handler->columnsName[columns] = NULL;

    return handler;
}

ALF_db *ALF_db_create(const char *filename){
    ALF_db *handler = ALF_db_init(filename, 0, 0);
    if(handler == NULL){
        return NULL;
    }

    FILE *dbfile = fopen(filename, "wb");
    if(dbfile == NULL){
        ALF_db_free(handler);
        // fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }
    // Write header.
    // char *header = "ALFDB\0\0\0\0\0\0\0\0\0\0\0";
    char header[ALF_DB_HEADER_SIZE];
    memcpy(header, HEADER_0_5, 6);
    memset(header + 6, 0, 10);
    fwrite(header, sizeof(char), ALF_DB_HEADER_SIZE, dbfile);
    fclose(dbfile);

    return handler;
}

ALF_db *ALF_db_open(const char *filename){
    FILE *dbfile = fopen(filename, "rb");
    if(dbfile == NULL){
        return NULL;
    }
    // Read header.
    char header[ALF_DB_HEADER_SIZE];
    size_t readed = fread(header, sizeof(char), ALF_DB_HEADER_SIZE, dbfile);
    if(readed != ALF_DB_HEADER_SIZE){
        fclose(dbfile);
        return NULL;
    }

    size_t aux = memcmp(header, HEADER_0_5, 6);
    if(aux != 0){
        // This is not an ALFDB file.
        return NULL;
    }
    uint16_t maxString = header[7] << 8 | header[8];

    ALF_db *handler = ALF_db_init(filename, header[6], maxString);
    if(handler == NULL){
        fclose(dbfile);
        return NULL;
    }
    int stringLen;
    char *strAux;
    for(int i = 0; i < handler->columns; ++i){
        stringLen = fgetString(dbfile, maxString, handler->columnsName[i]);
        strAux = realloc(handler->columnsName[i], sizeof(char) * (stringLen + 1));
        if(strAux == NULL){
            // panic
            fclose(dbfile);
            ALF_db_free(handler);
            return NULL;
        }
        handler->columnsName[i] = strAux;
    }
    fclose(dbfile);

    return handler;
}



void ALF_db_free(ALF_db *handler){
    if(handler != NULL){
        for(int i = handler->columns; i > 0; ){
            free(handler->columnsName[--i]);
        }
        free(handler->columnsName);
        free(handler->filename);
        free(handler);
    }
}
