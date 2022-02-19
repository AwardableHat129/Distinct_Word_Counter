#include "contenedor.h"


int main()
{
    FILE *file;

    

    file = fopen("texto.txt", "r");

    if(file == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return 0;
    }

    MAP map = map_create(10, hashFunction, equalsFunction);



    while(!feof(file))
    {
        char* string = malloc(sizeof(char) * MAXSIZE);

        if(getWord(file, string))
        {
            printf("\n%s", string);    
            map_put(map, string);                        
        }
    }     

    printf("\n\nEl resultado final es: %d\n", map -> size);

    for(int i = 0; i < 10; i++)
    {
        list_print(map -> hashTable[i], i);
    }
    return 0;
}



