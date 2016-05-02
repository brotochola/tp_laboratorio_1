#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 20

typedef struct {

char name[50];
int age;
int dni;
int isEmpty;

} employee;









int initEmployees(employee* pEmployee, int length)
{
    int salida=-1;
    int i;
    if (!(pEmployee==NULL || length<1 )) {

        for(i=0;i<length;i++){
          pEmployee[i].isEmpty=1;
            salida=0;
        }
    }

//  return 0;
    return salida;

}

int addEmployee(employee* pEmployee, int length,  char name[], int dni, int age )
{

    int salida=-1;
    int i;
    if (pEmployee!=NULL && length>1  ) {

        for(i=0;i<length;i++){
           if( pEmployee[i].isEmpty==1 ) {

                 pEmployee[i].dni = dni;
                pEmployee[i].age = age;
                 strcpy( pEmployee[i].name, name);

                 pEmployee[i].isEmpty=0;
                 salida=0;
                break;
           } //fin if

        } //fin for
    } //fin if principal

//  return 0;
    return salida;




}


int removeEmployee(employee* gente, int length )
{
    int dni;
    printf("ingrese DNI a borrar");
        scanf("%d",&dni);

    int salida=-1;
    int i;
    if (!(gente==NULL || length<1 )) {

        for(i=0;i<length;i++){
            if(gente[i].dni==dni){
                gente[i].isEmpty=1;
                salida=i;
                break;

            }

        }
        if(salida==-1){
               printf("no se encontro el dni, asi q no se borro nada.");
               system("pause");
               menu(gente);

        }else{
                printf("se encontro y borro el DNI en la posicion %d ",i);
               system("pause");
               menu(gente);

        }
    }


    return salida;
}


int sortEmployeeByName(employee* gente, int length, int order)
{

    employee aux;
    int salida=-1;
    int i, j;
    if (!(gente==NULL || length<1 )) {
        if(order!=0 || order!=1){
            for(i=0;i<length;i++){
                for(j=i+1;j<length;j++){
                    if (order==1){
                        if(strcmp(gente[i].name, gente[j].name )>0 ){
                            aux=gente[i];
                            gente[i] = gente[j] ;
                            gente[j] = aux;

                        } //fin if strcmp
                    } else if (order==0){
                        if(strcmp(gente[i].name, gente[j].name )<0 ){
                            aux=gente[i];
                            gente[i] = gente[j] ;
                            gente[j] = aux;

                        } //fin if strcmp
                    } //fin if segun order
                } //fin for j

            }//fin for i
              salida=0;
        }//fin if order
    }//fin if chequeo general

    return salida;


}

int printEmployees(employee* gente, int length)
{
    int i;

    for(i=0; i< length; i++)
    {
        if(!gente[i].isEmpty){
                printf("\n[%d] %d, %s, %d",i,gente[i].dni, gente[i].name, gente[i].age );
        }
    }
    printf("\n");
   system("pause");
   menu(gente);
}



int menu(employee* gente){
    int opcion;
    system("cls");
    printf("1- agregar persona\n");
    printf("2- borrar persona\n");
    printf("3- imprimir ordenando por nombre\n");
    printf("4- imprimir grafico de edades\n");
    printf("5- salir\n");
    scanf("%d",&opcion);


     switch(opcion)
        {
            case 1:
                agregarPersona(gente, TAM);
                break;
            case 2:
                removeEmployee(gente, TAM);
                break;
            case 3:
                sortEmployeeByName(gente, TAM, 1);
                printEmployees(gente, TAM);
                break;
            case 4:
                graph(gente, TAM);
                break;

            case 5:
                break;

        }
    return 0;


}




void agregarPersona(employee* gente, int length)
{

    char nombre[50];
    int dni=0;
    int age=0;
     int salida=-1;
    int i;

    printf("nombre:");
     fflush(stdin);
    gets(nombre);
    printf("dni:");
    scanf("%d",&dni);

    printf("edad:");
     scanf("%d",&age);


        for(i=0;i<length;i++){
           if( gente[i].isEmpty==1 ) {
                 gente[i].dni = dni;
                gente[i].age = age;
                 strcpy( gente[i].name, nombre);

                 gente[i].isEmpty=0;
                 salida=i;
                break;
           } //fin if

        } //fin for


//  return 0;

 printf("se agrego %s en el indice %d ",nombre,i);


 system("pause");
  menu(gente);
   // return salida;




}


void graph(employee* gente, int length){
    system("cls");
    int val1=18; //limite 1;
    int val2=35; //limite 2
    int i;
    int cantRango1=0;
    int cantRango2=0;
    int cantRango3=0;
    int cualEsElMayor=0;
    char grafico[10];

    for(i=0; i<length;i++){
        if(gente[i].age<=val1) cantRango1++;
        if(gente[i].age>val2 && gente[i].age<=val2 ) cantRango2++;
        if(gente[i].age>val2) cantRango3++;
    }

     if(cantRango1> cantRango2 && cantRango1>cantRango3) cualEsElMayor=cantRango1;
    if(cantRango2> cantRango1 && cantRango2>cantRango3) cualEsElMayor=cantRango2;
    if(cantRango3> cantRango2 && cantRango3>cantRango1) cualEsElMayor=cantRango3;

   for(i=cualEsElMayor; i>0; i--){

        if(cantRango1>=i) printf("*");
        if(cantRango2>=i) printf("*");
        if(cantRango3>=i) printf("*");
        printf("\n");

    }

    printf("%d %d %d", cantRango1, cantRango2, cantRango3);
    system("pause");
    menu(gente);
}


int main()
{
    employee gente[TAM];
    initEmployees(gente, TAM);
   // menu();
    menu(gente);
    return 0;
}
