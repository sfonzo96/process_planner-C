# Simulador de planeador de proceos en C

La idea de esta propuesta fue simular un planeador de procesos de un sistema operativo, que pueda trabajar con distintos algoritmos y tiempos de ejecución a definir por el usuario.

## Consigna

Desarrollar un programa en C que simule el funcionamiento de un sistema operativo con un planificador de procesos seleccionado. El programa debe tener las siguientes características:

-   El usuario debe poder crear y agregar procesos al sistema, ingresando su identificador, tiempo de llegada y duración de ejecución.
-   El programa debe simular el funcionamiento del planificador de procesos elegido, asignando una prioridad o algoritmo específico para determinar el orden de ejecución de los procesos.
-   El programa debe mostrar el estado del sistema en cada instante de tiempo, indicando qué proceso está en ejecución, cuáles están en espera y cuáles han finalizado.
-   El programa debe tener la capacidad de gestionar eventos como la llegada de nuevos procesos, la finalización de procesos en ejecución y cambios en las prioridades o algoritmos de planificación.
-   El usuario debe tener la opción de detener la simulación en cualquier momento.
-   Utilizar estructuras de datos adecuadas para representar los procesos y su estado en el sistema. El programa debe ser intuitivo y mostrar información clara sobre el estado de los procesos en cada momento.

## Carga de procesos con archivo .txt

El programa permite cargar los procesos iniciales a través de un archivo .txt o de manera manual a través de la terminal. Para el primer caso, el archivo DEBE llamarse processesList, existir antes de seleccionar la opción de carga de archivos y debe tener un formato de valores separados por coma (csv). Ver [ejemplo](https://github.com/sfonzo96/process_planner-C/blob/main/processesList.txt).

## Compilación

### Utilizando una terminal

Será necesario tener instalado en el sistema GCC (GNU Compiler Collection) u otro compilador de preferencia para lenguaje C.
Para verificar si está disponible en el equipo ingresá en la terminal:

```
    gcc --version
```

Si lo está, abre la terminal de preferencia en la ubicación en la que hayas guardado los archivos fuente de este repositorio e ingresa lo siguiente en la terminal:

```
    gcc main.c procesos_functions.c procesos_functions.h -o process_planner
```

Esto generará un archivo ejecutable (.exe) llamado process_planner para que se pueda ejecutar y probar el programa ingresando en terminal:

```
    ./process_planner
```

### Utilizando un IDE

Esto varía de acuerdo al IDE que se quiera utilizar. En términos generales, para ejecutarlo, es necesario crear un proyecto vacío y añadir al directorio del mismo los archivos fuente. Luego se presiona el botón de compilación que ofrezca el IDE. Para ejecutar se presiona el botón de ejecución que ofrezca el IDE.
Este proyecto se creo utilizando [Dev C++](https://sourceforge.net/projects/orwelldevcpp/). En el se pueden presionar dichos botones o la tecla F9 (compilar), seguida de la tecla F10 (ejecutar), o F11 (compilar y ejecutar).

## Licencia

Este repositorio está licenciado bajo la [Licencia MIT](LICENSE).
