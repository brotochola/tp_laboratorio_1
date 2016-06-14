
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"


int menu(movie* pelis, int cantPelis)
{
    if(pelis!=NULL && cantPelis>=0)
    {

        int i;
        int opcion;
        system("cls");
        printf("ahora hay %i pelis\n", cantPelis);
        printf("1- agregar peli\n");
        printf("2- borrar peli\n");
        printf("3- generar html\n");
        printf("4- Salir\n");
        printf("5- ver pelis q hay\n");
        printf("6- cargar\n");
        printf("7- guardar\n");
        scanf("%d",&opcion);


        switch(opcion)
        {
        case 1:

            addPeli(pelis, cantPelis);


            break;
        case 2:
            removePeli(pelis, cantPelis);
            break;
        case 3:

            genWeb(pelis,  cantPelis);
            break;
        case 4:
            printf("chau");
            break;

        case 5:
            showPelis(pelis, cantPelis);
            break; //sale de la app

        case 6:
            file2p(pelis);
            break; //sale de la app

        case 7:
            p2file(pelis, cantPelis);
            break; //sale de la app

        }
        return 0;


    }

}


int addPeli(movie* pelis, int cantPelis)
{

    // pelis+=cantPelis;
//char numero[20];
//char peli[50];
//strcat(peli,"peli: ");
//itoa(cantPelis,numero,10);
//strcat(peli,numero);
    if(pelis!=NULL && cantPelis>=0)
    {

        fflush(stdin);
        char titulo[50];
        char genero[50];
        char duracion[3];
        char descripcion[128];
        char puntaje[2];
        char link[128];
        printf("TITULO: ");
        gets(titulo);
        printf("\nGENERO: ");
        gets(genero);
        printf("\nDESCRIPCION: ");
        gets(descripcion);
        printf("\nPUNTAJE:");
        gets(puntaje);
        printf("\n: LINK A IMAGEN:");
        gets(link);

        strcpy((pelis+cantPelis)->titulo, titulo);
        strcpy((pelis+cantPelis)->genero, genero);
        strcpy((pelis+cantPelis)->descripcion,descripcion);
        strcpy((pelis+cantPelis)->link, link);
        strcpy((pelis+cantPelis)->puntaje, puntaje);
        strcpy((pelis+cantPelis)->duracion, duracion);
        (pelis+cantPelis)->ocupado=1;


        cantPelis++;
        ///////////////////////////////////
        ///////////////////////////////////


        menu(pelis, cantPelis);
        return 0;
    }
}

int file2p(movie* pelis)
{
    if(pelis!=NULL )
    {


// movie *peliculasDesdeElArchivo;
        int cantLeidas=0;
        FILE *archivo;
        archivo=fopen("pelas.dat","rb");
        fflush(stdin);
        int i;
        int cuantasPelisHay=0;

        fread(pelis, sizeof( movie), TAM, archivo)  ;

        for(i=0; i<TAM; i++)
        {
            if(((pelis+i)->ocupado)==1)
            {
                cuantasPelisHay++;
            }
        }
        printf("Se cargaron %d peliculas del archivo", cuantasPelisHay);


        system("pause");
        menu(pelis, cuantasPelisHay);

        return cuantasPelisHay;
    }
}

int p2file(movie* pelis, int cantPelis)
{
    if(pelis!=NULL && cantPelis>=0)
    {

        FILE *ptr_myfile;
        ptr_myfile=fopen("pelas.dat","wb"); //voy a guardar al final, append

        fwrite(pelis, sizeof(movie), TAM, ptr_myfile);
        fclose(ptr_myfile);
        menu(pelis, cantPelis);

        return 0;
    }
}

int showPelis(movie* pelis, int cantPelis)
{

    if(pelis!=NULL && cantPelis>=0)
    {

        int i;


        for(i=0; i<cantPelis; i++)
        {
            // peliculasDesdeElArchivo+=i;

            printf("\npelis %d: %s, %s",  i, pelis[i].titulo, pelis[i].genero);


        }
        printf("\n");
        system("pause");
        menu(pelis, cantPelis);
        return 0;
    }

}
int removePeli(movie* pelis, int cantPelis)
{
    if(pelis!=NULL && cantPelis>=0)
    {

        fflush(stdin);
        printf("cual pelicula queres borrar?");
        int cual;
        scanf("%d", &cual);
        (pelis+cual)->ocupado=0;
        int i;
        for (i=cual; i<cantPelis-1; i++)
        {

            strcpy((pelis+i)->titulo, (pelis+i+1)->titulo);
            strcpy((pelis+i)->genero, (pelis+i+1)->genero);
            strcpy((pelis+i)->descripcion, (pelis+i+1)->descripcion);
            strcpy((pelis+i)->link, (pelis+i+1)->link);
            strcpy((pelis+i)->puntaje, (pelis+i+1)->puntaje);
            strcpy((pelis+i)->duracion, (pelis+i+1)->duracion);
            (pelis+i)->ocupado=1;
        }
        (pelis+cantPelis)->ocupado=0;
        cantPelis--;



        menu(pelis, cantPelis);
        return 0;
    }
}

int genWeb(movie* pelis, int cantPelis)
{
    if(pelis!=NULL && cantPelis>=0)
    {

        int i;


        FILE *htmlFile;
        htmlFile=fopen("index.html","w");
        char html[99999];


        for(i=0; i<cantPelis; i++)
        {


            strcat(html, "<!-- Repetir esto para cada pelicula --><article class='col-md-4 article-intro'><a href='#'><img class='img-responsive img-rounded' src='");

            strcat(html, (pelis+i)->link);
            strcat(html, "' alt=''> </a> <h3> <a href='#'>");
            strcat(html,(pelis+i)->titulo );
            strcat(html, "</a> </h3><ul><li>Género:");
            strcat(html, (pelis+i)->genero);
            strcat(html, "</li><li>Puntaje:");
            strcat(html, (pelis+i)->puntaje);
            strcat(html, "</li><li>Duración:");
            strcat(html, pelis->duracion);
            strcat(html, "</li></ul> <p>");
            strcat(html, (pelis+i)->descripcion);
            strcat(html, "</p></article><!-- Repetir esto para cada pelicula -->");





        }

        //  printf("%s", html);

        fwrite(&html, strlen(html), 1, htmlFile);
        fclose(htmlFile);

        system("pause");
        menu(pelis, cantPelis);
        return 0;
    }
}
