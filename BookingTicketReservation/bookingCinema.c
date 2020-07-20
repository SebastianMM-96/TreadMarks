#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "Tmk.h"

#define COORDINADOR 0
#define tamanoArreglo 5

//Definimos una matriz dinamica
int **matrix;
//Variables para guardar valores aleatorios dentro de nuestra matriz
int matA[tamanoArreglo]; //--> Filas
int matB[tamanoArreglo]; //--> Columnas

//Funciones a implementar

void createMatrix(int*** array, int row, int col);
void fillMatrix(int** array, int row, int col);
void showMatrix(int** array, int row, int col);
void matrixReservation(int a, int b, int** mat);
void freeMemo(int*** array, int row);
void generateMatrix(int max, int num[tamanoArreglo]);
void cancel(int a, int b, int** mat);

//Implementamos cada una de las funciones antes declaradas

void createMatrix(int*** array, int row, int col){

    *array = (int**)Tmk_malloc(row * sizeof(int*)); //Reservamos memoria para la matriz
    for (int i = 0; i < row; i++)
    {
        /* code */
        (*array)[i] = (int*)Tmk_malloc(col * sizeof(int));
        //Creamos la matriz y a su vez le asignamos la memoria
        //correspondiente
    }
}   

void fillMatrix(int** array, int row, int col){
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            array[i][j] = 0;
            //Llenamos el arreglo dinamico de 0
        }
    }
}

void showMatrix(int** array, int row, int col){
    for (int i = 0; i < row; i++)
    {
        printf("\n");
        for (int j = 0; j < col; j++)
        {
            printf("|%d|", array[i][j]);
            //Mostramos la matriz o la sala del cine
        }
    }
    printf("\n");
}

void matrixReservation(int a, int b, int** mat){
    if (mat[a][b] != 1)
    {
        mat[a][b] = 1;
    }else{
        printf("El lugar |%d| |%d| ya esta ocupado\n", a, b);
    }
}
void freeMemo(int*** array, int row){
    for (int i = 0; i < row; i++)
    {
        Tmk_free((*array)[i]);
    }
    Tmk_free(*array); //Liberamos la memoria previamente asignada de nuestro arreglo
}
void generateMatrix(int max, int num[tamanoArreglo]){
    for (int i = 0; i <= tamanoArreglo - 1; i++)
    {
        num[i] = (rand()%(tamanoArreglo - 1)) + Tmk_proc_id;
        //El numero aleatorio podra variar gracias 
        //A la variable de los procesos creados por el 
        //TreadMarks
    }

    for (int j = 0; j <= tamanoArreglo - 1; j++)
    {
        printf("Se genero el numero aleatorio: %d\n", num[j]);
        //Obtenemos nuestro numero aleatorio
    }
    printf("\n");
}

void cancel(int a, int b, int** mat){
    if (mat[a][b] == 1) //Si el lugar esta ocupado
    {
        mat[a][b] = 0; //Lo desocupa
    }else{
      printf("El lugar |%d| |%d| esta libre\n",a,b);
    }
}


int main(int argc, char **argv)
{
    /* code */
    int c;
    int randomValue[5]; //Esta variable nos ayudara a discretizar cuando
    //Se entra a la cancelacion, y cuando se entra a la reservacion
    extern char *optarg;
    while ( (c = getopt(argc,argv,"d:")) != -1);

    Tmk_startup(argc, argv);

    if (Tmk_proc_id == COORDINADOR){

        createMatrix(&matrix, tamanoArreglo, tamanoArreglo);
        fillMatrix(matrix, tamanoArreglo, tamanoArreglo);
        Tmk_distribute(&matrix, sizeof(matrix));
        printf("La sala esta disponible\n");
        showMatrix(matrix, tamanoArreglo, tamanoArreglo);
    }

    Tmk_barrier(0); //Esperara para llenar

    generateMatrix(tamanoArreglo, matA); //-->Generamos aleatorios para A
    generateMatrix(tamanoArreglo, matB); //-->Generamos aleatorios para B-

    Tmk_barrier(0);

    for (int i = 0; i < tamanoArreglo; i++)
    {
        /* code */
        printf("Fila A: %d\n", matA[i]);
        printf("Columna B: %d\n", matB[i]);

        int a = matA[i];
        int b = matB[i];

        Tmk_lock_acquire(0);
        
        for (int j = 0; j < tamanoArreglo; j++)
        {
            randomValue[j] = (rand()%10)+Tmk_proc_id;
            //Verificamos si es par o es impar. 
        }

        if (randomValue[i]%2 == 0) //Si es par
        {
            matrixReservation(b,a, matrix); //Reservamos
            printf("Usted reservo el asiento: |%d| |%d|\n", a, b);
        } else {
            cancel(b, a, matrix); //Cancelamos
            printf("Usted a cancelado el asiento: |%d| |%d|\n", a, b);
        }

        if (i == 4)
        {
            showMatrix(matrix, tamanoArreglo, tamanoArreglo);
            //Veremos la matriz modificada
        }

        Tmk_lock_release(0);

    }

    Tmk_barrier(0);

    if (Tmk_proc_id == COORDINADOR)
    {
        printf("La pelicula ya comenzo, y la sala actualizada es la siguiente\n");
        showMatrix(matrix, tamanoArreglo, tamanoArreglo);
        freeMemo(&matrix, tamanoArreglo);
    }

    Tmk_exit(0);
}