#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"
#include "pelis.h"


void printArrayListEmployee(ArrayList* lista)
{
    int i=0;
    for(i=0; i<lista->len(lista); i++)
    {
        movie* pAux = lista->get(lista,i);
        printf("%d) ",i);
        //   printEmployee(pAux);
    }
}

int mostrar(ArrayList* lista)
{
    printf("----------------------------------------\n");
    printf("SIZE: %d\n", al_len(lista));
    printf("rSize: %d\n", lista->reservedSize);
    printf("puntero: %p\n", lista->pElements);

   printf(">>> PELICULAS:\n");

    movie* peliAux2;
    int i;
    printf("[id]\t\ttitulo\t\tgenero\t\tPuntero\n" );

    for(i=0; i<lista->size; i++){
        peliAux2 = al_get(lista, i) ;
        printf("[%d]\t\t%s\t\t%s\t\t%p\n",i, peliAux2->titulo , peliAux2->genero,peliAux2 );

    }
    printf("----------------------------------------\n\n");



}

int abrirArchivo(ArrayList* lista)
{

// movie *peliculasDesdeElArchivo;
    int cantLeidas=0;
    FILE *archivo;
    archivo=fopen("pelas.dat","rb");
    fflush(stdin);
    int i;
    int cuantasPelisHay=0;

    while(fread(lista->pElements, sizeof( movie), 1, archivo) !=0)
    {
        cuantasPelisHay++;
    }


    printf("Se cargaron %d peliculas del archivo\n", cuantasPelisHay);


    system("pause");
    menu(lista, cuantasPelisHay);

    return cuantasPelisHay;
}

int menu(ArrayList* lista)
{
    printf("1-agregar peli\n");
    printf("2-modificar peli\n");
    printf("3-borrar peli\n");
    printf("4-buscar\n");
    printf("5-mostrar pelis\n");

    printf("6-agregar peli en una posicion determinada\n");


    printf("7-borrar toda la lista\n");
     printf("8-vaciar toda la lista\n");
  printf("9-ordenar alfabeticamente por titulo\n");


    printf("0-salir y guardar\n");
    fflush(stdin);
    int cual;
    scanf("%d", &cual);

    return cual;

}

int agregarPeli(ArrayList* lista)
{
    fflush(stdin);

    int id;
    char titulo[50];
    char genero[50];


    printf("titulo:");
    gets(titulo);

    printf("genero:");
    gets(genero);

    movie* peliAux=(movie*) malloc(sizeof(movie));
    strcpy(peliAux->genero, genero);
    strcpy(peliAux->titulo, titulo);
  //  peliAux.id=(lista->size);
    al_add(lista, peliAux);
    movie* peliAux2 =al_get(lista, lista->size-1);


    printf("#### acabas de agregar la peli [%d] %s\n", lista->size-1, peliAux2->titulo );
    mostrar(lista);



}
int agregarPush(ArrayList* lista){
 fflush(stdin);

    int id;
    char titulo[50];
    char genero[50];


    printf("titulo:");
    gets(titulo);

    printf("genero:");
    gets(genero);

    printf("en q numero de indice:");
    scanf("%d", &id);
    if ((lista->size) == (lista->reservedSize))  resizeUp(lista);

    movie* peliAux =malloc(sizeof(movie));
    strcpy(peliAux->genero, genero);
    strcpy(peliAux->titulo, titulo);
    al_push(lista, id, peliAux);



    movie* peliAux2 =al_get(lista, id);
    printf("acabas de agregar la peli [%d] %s\n", id, peliAux2->titulo );



}



int comparar(movie* peli1, movie* peli2) //esto es un comparador de titulos de peliculas
{

// ¬¬
//esta carita!

  if(peli1==NULL || peli2==NULL) return NULL;
   int resp;
    char titulo1[50];
     char titulo2[50];
     strcpy(titulo1,((movie*)peli1)->titulo );
     strcpy(titulo2,((movie*)peli2)->titulo );

   resp = strcmp(titulo1, titulo2);
  // printf("RESPUESTA %d\n", resp);
 //   system("pause");

    return resp ;


}

int buscar(ArrayList* lista){
    fflush(stdin);
    printf(">>>> sistema de busqueda <<<<\n");
    movie* movieAux = malloc(sizeof(movie));
    char titulo[50];
    printf("ingrese titulo a buscar: ");
    gets(titulo);

    int i;
    for(i=0;i<al_len(lista);i++){
        movieAux=al_get(lista, i);
        if(strcmp(movieAux->titulo, titulo)==0){
            printf("el indice %d tiene la peli %s\n", i, titulo);
            break;
        }
        printf("no se encontró la peli \n");

    }



    system("pause");

}

int borrar(ArrayList* lista){
    movie* peliAux = malloc(sizeof(movie));
    int cual;
    fflush(stdin);
    printf("q item queres borrar?");
    scanf("%d", &cual);
    peliAux=al_get(lista, cual);
    printf("\nestas por borrar la peli titulada %s ", peliAux->titulo);
    char seguro[1];
    printf("\nseguro? [S/N]");
    fflush(stdin);
    gets(seguro);
    if(strcmp(seguro, "s")==0 || strcmp(seguro, "S")==0 ) peliAux = al_pop(lista, cual);
    return 0;


}

int file2p(ArrayList* lista)
{
    if(lista!=NULL )
    {
        FILE *archivo;
        archivo=fopen("pelasTP4.dat","rb");

        if(archivo==NULL){
            printf("el archivo pelasTP4.dat no se encontró\n");
            return NULL;
        }

        fflush(stdin);
        int i;
        int cuantasPelisHay=0;
        fread(&cuantasPelisHay, sizeof(int), 1, archivo) ; //esto lee el encabezado del archivo, q es un unico int, con la cantidad de pelis q hay

        //recorro el archivo, desde despues de ese primer valor int..
        for(i=0; i<cuantasPelisHay; i++){
            movie* peliAux = malloc(sizeof(movie)); //creo el espacio para poner cada pelicula
        //a estos espacios de memoria va a puntar la secuencia de elementos de lista->pElements
            fread(peliAux, sizeof(movie), 1, archivo) ;
            al_add(lista, peliAux);


        }


      printf("Se cargaron %d peliculas del archivo\n", cuantasPelisHay);

   fclose(archivo);




        return cuantasPelisHay;
    }
}

int p2file(ArrayList* lista)
{
    if(lista!=NULL )
    {

        FILE *ptr_myfile;
        ptr_myfile=fopen("pelasTP4.dat","wb"); //primero lo abro en modo write binary, para borrar lo que sea que haya

        int cantItems=lista->size;
        fwrite(&cantItems, sizeof(int), 1, ptr_myfile); //le meto la cantidad de items q hay
        fclose(ptr_myfile);

        ptr_myfile=fopen("pelasTP4.dat","ab"); //lo vuelvo a abrir en modo append para meterle las peliculas
        movie* movieAux;
        int i;

        for(i=0; i<lista->size; i++){
            movieAux=al_get(lista, i);
            fwrite(movieAux, sizeof(movie), 1, ptr_myfile);
        }

       // fwrite(al_get(lista, i), sizeof(movie), lista->size, ptr_myfile);



        fclose(ptr_myfile);




        return 0;
    }
}

int main(void)
{
    ArrayList* lista ;
    lista=al_newArrayList();



    file2p(lista);

    //mostrar(lista);
    int resp;

    do
    {
        resp=menu(lista);
        switch(resp)
        {
        case 1:

            agregarPeli(lista);
            break;
        case 2:
            break;

        case 3:
            borrar(lista);
            break;

        case 4:
            buscar(lista);
            break;

        case 5:
            mostrar(lista);
            break;

        case 6:
            agregarPush(lista);
            break;
        case 7:
         al_deleteArrayList(lista);
          break;
              case 8:
            al_clear(lista);
            break;

            case 9:
            al_sort(lista, comparar, 1); //0 de z-a
                                        //1 de a-z
            break;

        case 0:
            p2file(lista);
            break;





        }


    }
    while (resp!=0);

    return 0;
}
