#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>
#define TAM 20



typedef struct
{


    char titulo[50];
    char genero[50];
    char duracion[3];
    char descripcion[128];
    char puntaje[2];
    char link[128];
    int ocupado;


} movie;


int genWeb(movie* pelis,  int cantPelis);
int menu(movie* pelis, int cantPelis);
int addPeli(movie* pelis, int cantPelis);
int removePeli(movie* pelis, int cantPelis);
int showPelis(movie* pelis, int cantPelis);
int file2p(movie* pelis);
int p2file(movie* pelis, int cantPelis);

