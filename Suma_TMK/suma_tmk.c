#include <stdio.h>
#include "Tmk.h"

#define COORDINADOR 0

struct shared { 
   int sum;    // Acumulador para la suma global
   int turn;   // Controlar los turnos de ejecución entre procesos
   int* array; // Arreglo dinámico
} *shared; 

int main(int argc, char **argv) 
{  
   int start, end, i, p, arrayDim = 100000;     

   // Necesario para obtener parámetros que no usarán en el programa.   
   int c;
   extern char *optarg;
   while ( (c = getopt(argc,argv,"d:")) != -1);

   
   Tmk_startup(argc, argv); 
   
   /* El proceso 0 inicializa las estructuras de datos */   
   if (Tmk_proc_id == COORDINADOR) {
      
      // Memoria para toda la estructura 'shared'
      shared = (struct shared *) Tmk_malloc(sizeof(shared));        
      if (shared == NULL)            
         Tmk_exit(-1);
      
      // Memoria para el arreglo dentro de 'shared'
      shared->array = (int *) Tmk_malloc(arrayDim * sizeof(int));        
      if (shared->array == NULL)  
         Tmk_exit(-1);  
      
      /* Se inicializa el arreglo */   
      //printf("\nDame los %d números uno por uno: ", arrayDim);
      for (i = 0; i < arrayDim; i++)
         shared->array[i] = i+1;
      
      shared->turn = 0;       
      shared->sum = 0;        
      /* Y comparte el apuntador común con todos los procesos */        
      Tmk_distribute(&shared, sizeof(shared));    
   } // FIN if 
     
   Tmk_barrier(0);  
   
   
   /* Cada proceso determina su intervalo del arreglo */    
   {  
      int id0 = Tmk_proc_id, id1 = Tmk_proc_id+1;        
      int perProc = arrayDim / Tmk_nprocs;        
      int leftOver = arrayDim % Tmk_nprocs;        
      start = id0 * perProc + id0 * leftOver / Tmk_nprocs;       
      end   = id1 * perProc + id1 * leftOver / Tmk_nprocs;    
   }  
   
   /* Imprime los elementos del arreglo en el orden natural de salida */    
//    for (p = 0; p < Tmk_nprocs; p++)   {        
//       if (shared->turn == Tmk_proc_id) {
//          printf("\nMis elementos son:\n");
//          for (i = start; i < end; i++)                
//             printf("a[%d]: %d\n", i, shared->array[i]);            
//          shared->turn++;        
//       }        
//       Tmk_barrier(0);    
//    }  
   
   /* Calcula la suma local y se la agrega a la suma global */ 
   {   
      int mySum = 0;        
      for (i = start; i < end; i++)            
         mySum += shared->array[i];
      
      /*  Modificación de la suma global */        		                     
      Tmk_lock_acquire(0);        
      shared->sum += mySum;        
      Tmk_lock_release(0);    
   }
   
   Tmk_barrier(0);
   
   if (Tmk_proc_id == COORDINADOR) {        
      printf("\nLa suma es: %d\n", shared->sum);          
      Tmk_free(shared->array);        
      Tmk_free(shared);        
   }     
   
   Tmk_exit(0);
}    
