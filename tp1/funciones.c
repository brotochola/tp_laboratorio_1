//las variables globales las defino aca, no en el main

int opcion=0; //la opcion que se ingresa en el menu
int operA; //numero1
int operB; //numero2
int flag1=0; //bandera para ver si se seteó el operador A
int flag2=0;//bandera para ver si se seteó el operador B

void mostrar_opciones(){

//esta funcion muestra las opciones y ejecuta las demas segun la opcion ingresada

    system("cls"); //nota mental: no es lo mismo comillas simples que dobles
    printf(">>>>> MENU >>>>\n");
    printf("1- Ingresar 1er operando (A=%d)\n", operA);
    printf("2- Ingresar 1er operando (B=%d)\n", operB);
    printf("3- Calcular la suma (A+B)\n");
    printf("4- Calcular la resta (A-B)\n");
    printf("5- Calcular la division (A/B)\n");
    printf("6- Calcular la multiplicacion (A*B)\n");
    printf("7- Calcular el factorial (A!)\n");
    printf("8- Calcular todas las operaciones\n");
    printf("9- Salir\n");
    printf(">>>>> OPCION: ");
    scanf("%d",&opcion);


     switch(opcion)
        {
            //todas las opciones operan y despues vuelven al menu inicial
            //preferi hacer funciones que se llamen mutuamente, en vez de un do while
            //de todas formas hay un loop que se da entre funciones que se llaman entre si:
            // mostrar_opciones -> otras funciones ->mostrar_opciones
            case 1:
                printf("INGRESE NUMERO:");
                scanf("%d",&operA);
                flag1=1; //flag para evaluar si se ingreso o no el numero
                mostrar_opciones();
                break;
            case 2:
                printf("INGRESE NUMERO:");
                scanf("%d",&operB);
                flag2=1;//flag para evaluar si se ingreso o no el numero
                mostrar_opciones();
                break;
            case 3:
                //cada funcion (sumar, restar, dividir, etc) calcula y muestra
                //el system(pause) y la vuelta al menu estan aparte
                //de esta forma puedo usar la funcion todas() sin tener muchos pauses :)
                sumar(operA, operB);
                  system("pause");
                mostrar_opciones();
                break;
            case 4:
                restar(operA, operB);
                  system("pause");
                mostrar_opciones();
                break;
            case 5:
                dividir(operA, operB);
                  system("pause");
                    mostrar_opciones();
                break;
            case 6:
                multiplicar(operA, operB);
                  system("pause");
                mostrar_opciones();
                break;
            case 7:
                factorial(operA);
                  system("pause");
            mostrar_opciones();
                break;
            case 8:
                todas(operA, operB);
                  system("pause");
                mostrar_opciones();
                break;
            case 9:
                return 0;
                break;
            default:
                mostrar_opciones(); //si tocas cualquiera, vuelve a mostrar el menu

        } //cierra switch


} //cierra mostrar_opciones


int dividir(int num1, int num2){
    float resultado;
    if(flag1==1 && flag2==1) { //solo hace la cuenta si se setearon los dos valores
        if(num2==0){
            printf("division por cero!!!\n");

        }else{
            resultado = num1/num2;
            printf("%d/%d=%f\n",num1,num2,resultado);

        }


    }else{ //sino te muestra error
        printf("tenes que setear ambos valores para hacer las cuentas\n");


    }
    return 0;
} //cierra dividir

int multiplicar(int num1, int num2){
     int resultado;
    if(flag1==1 && flag2==1) { //solo hace la cuenta si se setearon los dos valores
        resultado = num1*num2;
        printf("%d*%d=%d\n",num1,num2,resultado);


    }else{ //sino te muestra error
        printf("tenes que setear ambos valores para hacer las cuentas\n");


    }
    return 0;
} //cierra multiplicar

int factorial(int num1){
    int i;
    int val=num1;
      if(flag1==1){
        for(i=val-1;i>0;i--){
            val=val*i;
        }//cierra for
            printf("%d!=%d\n",num1, val);

      }else{
        printf("tenes q setear el primer valor\n");

      }//cierra if...else
    return 0;
} //cierra factorial



int todas(int num1, int num2){
    sumar(num1, num2);
    restar(num1, num2 );
     dividir(num1, num2);
      multiplicar(num1, num2);
     factorial(num1);
     return 0;
} //cierra factorial

int restar(int num1, int num2){
    int resultado;
    if(flag1==1 && flag2==1) { //solo hace la cuenta si se setearon los dos valores
        resultado = num1-num2;
        printf("%d-%d=%d\n",num1,num2,resultado);


    }else{ //sino te muestra error
        printf("tenes que setear ambos valores para hacer las cuentas\n");


    }
    return 0;
}

int sumar(int num1, int num2){
    int resultado;
    if(flag1==1 && flag2==1) { //solo hace la cuenta si se setearon los dos valores
        resultado = num1+num2;
        printf("%d+%d=%d\n",num1,num2,resultado);


    }else{ //sino te muestra error
        printf("tenes que setear ambos valores para hacer las cuentas\n");

    }
    return 0;

} //cierra sumar
