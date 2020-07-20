#include <stdio.h>
#include <stdlib.h>
#include <Tmk.h>


int main(int argc, char **argv) 
{
   int c;
           
   // Necesario para obtener parámetros que no usarán en el programa.
   extern char *optarg;
   while ( (c = getopt(argc,argv,"d:")) != -1);


   Tmk_startup(argc,argv);
    
   printf("\nTodo funciona bien :) \n");
    
   Tmk_exit(0);
}



