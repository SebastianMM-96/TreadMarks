# TreadMarks

TreadMarks es un sistema de memoria compartida distribuida para Unix. Está implementado como una biblioteca del lenguaje C. 
Este sistema permite que varios procesos en diferentes computadoras compartan su memoria para dar la apariencia de tener una memoria local. Así entonces, en lugar de utilizar explícitamente paso de mensajes, el programador tiene que utilizar variables de sincronización. TreadMarks admite la computación paralela en redes de estaciones de trabajo al proporcionar a la aplicación una abstracción de memoria compartida. La memoria compartida facilita la transición de la secuencia a programas paralelos.

***

## Memoria compartida vs Memoria distribuida

_Memoria compartida_

1. Memoria física global igualmente accesible para todos los procesadores
2. Facilidad de programación y portabilidad.
3. El aumento de la contención y las latencias más largas limitan la escalabilidad.

_Memoria distribuida_

1. Múltiples nodos de procesamiento independientes conectados por una red de interconexión general.
2. Escalable, pero requiere pasar el mensaje.
3. Programador gestiona la distribución de datos y la comunicación.

***

## Caso de estudio: TreadMarks

Memoria compartida como una matriz lineal de bytes a través de un modelo de memoria relajado llamado coherencia de publicación.

1. Utiliza hardware de memoria virtual para detectar accesos.
2. Protocolo de escritor múltiple para aliviar problemas causados por desajustes entre el tama~no de pagina y la granularidad de la aplicación
3. Portátil, ejecute a nivel de usuario en la máquina Unix sin modificaciones al kernel
4. Sincronizaciones: bloqueos, barreras
