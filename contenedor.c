#include "contenedor.h"

int hashFunction(TYPE data)
{
    char* string = data;
    return (int)string[0];
}

bool equalsFunction(TYPE data1, TYPE data2)
{
    char* charPointer1 = data1;
    char* charPointer2 = data2;

    //printf("\n\nComparando %s y %s. Resultado: %d", charPointer1, charPointer2, strcmp(charPointer1, charPointer2));

    int result = strcmp(charPointer1, charPointer2);

    return result == 0;
}

bool checkForLetter(unsigned char c)
{
    if((c >= 65 && c <= 90) || ((c >= 97 && c <= 122)))
        return true;
    switch(c)
    {
        case(193): case(201): case(205): case(211): case(218): //Mayusculas con acento
        case(225): case(233): case(237): case(243): case(250): //Minusculas con acento
        case(209): case(241): //Letra ñ
        case(220): case(252): //U con dieresis
            return true;
            break;
    }

    return false;
}

bool getWord(FILE* file, char* array)
{
    unsigned char c = fgetc(file);
    while(true)
    {        
        if(checkForLetter(c))
        {       
            for(int i = 0; i < MAXSIZE; i++)
            {
                array[i] = convertLetter(c);

                c = fgetc(file);

                if(!checkForLetter(c))
                {
                    array[i+1] = '\0';
                    return true;
                }
                    

                if(feof(file))
                {
                    array[i+1] = '\0';
                    return true;
                }
                
            }
            
        } else 
        {
            if(feof(file))
                return false;

            c = fgetc(file);            
        }
    }

}

unsigned char convertLetter(unsigned char c)
{
    switch(c)
    {
        case 193: case 225: case 65: //Letras A
            return 97;
            break;

        case 201: case 233: case 69: //Letras E
            return 101;
            break;

        case 205: case 237: case 73: //Letras I
            return 105;
            break;

        case 211: case 243: case 79: //Letras O
            return 111;
            break;

        case 218: case 250: case 85: case 220: case 252: //Letras U
            return 117;
            break;

    }

    if(c >= 65 && c <= 90)
        return c + 32;
    

    return c;
}

LIST list_create()
{
    LIST list = malloc(sizeof(struct STRLIST));

    list -> first = NULL;
    list -> last = NULL;
    list -> size = 0;

    return(list);
}

void list_insert(LIST list, TYPE data)
{
    NODE node = malloc(sizeof(struct STRNODE));

    node -> data = data;
    node -> next = NULL;    

    if(list -> first == NULL)
    {
        list -> first = node;
        list -> last = node;
        list -> size++;
    }
    else
    {
        list -> last -> next = node;
        list -> last = node;
        list -> size++;
    }   
    
}

void list_print(LIST list, int position)
{
    NODE nodePointer = list -> first;

    printf("\n%d: ", position);

    while(nodePointer != NULL)
    {
        printf("<%s> ", nodePointer -> data);
        nodePointer = nodePointer -> next;
    }


}

MAP map_create(int M, HASHFUNC hashFunction, EQUALSFUNC equalsFunction)
{
    MAP map = malloc(sizeof(struct STRMAP));

    map -> equalsFunction = equalsFunction;
    map -> hashFunction = hashFunction;
    map -> size = 0;
    map -> M = M;
    map -> hashTable = malloc(sizeof(struct STRLIST) * M);

    for(int i = 0; i < M; i++)
        map -> hashTable[i] = list_create();

    return(map);
}

bool map_get(MAP map, TYPE data)
{
    int hashCode = map -> hashFunction(data);
    //printf(" %d ", hashCode);
    hashCode = hashCode % (map -> M);

    NODE nodePointer = map -> hashTable[hashCode] -> first;

    while(nodePointer != NULL)
    {
        if(map -> equalsFunction(data, nodePointer -> data))
        {
            //printf("\n%s    %s    %d\n", data, nodePointer -> data, map -> equalsFunction(data, nodePointer -> data));
            return true;
        }

        nodePointer = nodePointer -> next;
    }

    return false;
}

bool map_put(MAP map, TYPE data)
{
    int hashCode = map -> hashFunction(data);
    hashCode = hashCode % (map -> M);
    
    if(map_get(map, data))
    {
        //printf("\nSe denego: %s", data);
    } 
    else 
    {
        map -> size++;
        //printf("\nSe inserto con exito: %s", data);
        list_insert(map -> hashTable[hashCode], data);
    }

}