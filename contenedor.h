#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef CONTENEDOR_H_


#define MAXSIZE 50

typedef void* TYPE;


struct STRNODE
{
    TYPE data;
    struct STRNODE* next;
};

typedef struct STRNODE* NODE;

struct STRLIST
{
    NODE first, last;
    int size;
};

typedef struct STRLIST* LIST;

typedef int (*HASHFUNC)(TYPE);
typedef bool (*EQUALSFUNC)(TYPE,TYPE);

struct STRMAP
{
    HASHFUNC hashFunction;
    EQUALSFUNC equalsFunction;
    int M, size;
    LIST *hashTable;
};

typedef struct STRMAP* MAP;

MAP map_create(int M, HASHFUNC hashFunction, EQUALSFUNC equalsFunction);
bool map_get(MAP map, TYPE data);
bool map_put(MAP map, TYPE data);

LIST list_create();
void list_insert(LIST list, TYPE data);
void list_print(LIST list, int position);

bool checkForLetter(unsigned char c);
bool getWord(FILE* file, char* array);
unsigned char convertLetter(unsigned char c);

int hashFunction(TYPE data);
bool equalsFunction(TYPE data1, TYPE data2);

#endif