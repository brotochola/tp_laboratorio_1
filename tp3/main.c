#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>
#define TAM 20
#include "tp3.h"

int main()
{

    int cantPelis =0;

    movie pelis[TAM];
    char resp[1];
    fflush(stdin);
    printf("cargar datos? S/N");
    gets(resp);
    if(strcmp(resp, "s") == 0 || strcmp(resp, "S") == 0)
    {
        file2p(pelis);
    }

    // system("pause");
    menu(pelis, cantPelis);
    return 0;


}

