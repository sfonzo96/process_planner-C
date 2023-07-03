#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "procesos_functions.h"

// Functions
void clearInputBuffer() {
	while (getchar() != '\n');
};

void initProcessPlanner() {
	int initialProcessesQuantity;
	int arraySize;
	int chosenAlgorithm;
	
	// Asks the user for the amount of process the planner should start executing
	printf("Ingresa una cantidad inicial de procesos para que el sistema ejecute:\n");
	while (scanf("%d", &initialProcessesQuantity) != 1) {
		printf("El valor ingresado no es válido, ingresa otro...\n");
		clearInputBuffer();
	};
	clearInputBuffer();
	
	system("cls");
	
	printf("Ingresa el valor del algoritmo deseado para ejecutar los procesos:\n1- Round Robin\n2- Por priodidad\n3- FIFO\n");
	while (scanf("%d", &chosenAlgorithm) != 1 || chosenAlgorithm < 0 || chosenAlgorithm > 3) {
		printf("El valor ingresado no es válido, ingresa otro...\n");
		clearInputBuffer();
	};
	clearInputBuffer();
	
	system("cls");
	
	switch (chosenAlgorithm) {
		case 1: 
			printf("Elegiste el algoritmo Round Robin.\nEste asigna a cada proceso una porción de tiempo equitativa y ordenada, tratando a todos los procesos con la misma prioridad.\n\n");
			break;
		case 2:
			printf("Elegiste el algoritmo por prioridad.\nEste ejecuta los procesos por completo en el orden de prioridad asignado.\n\n");
			break;
		default:
			printf("Elegiste el algoritmo FIFO (First In First Out).\nEste ejecuta los procesos por completo en el orden que ingresan.\n\n");
	};
	
	struct Process processesList[initialProcessesQuantity];
	arraySize = sizeof(processesList) / sizeof(processesList[0]);
	populateProcessesList(processesList, arraySize);
	runProcessesPlanner(processesList, arraySize, chosenAlgorithm);
};

struct Process createProcess() {
	
	struct Process process;
	char auxTitle[20];
	
	// Asks the proces title
	printf("Ingresa el nombre del proceso:\n");
	while (scanf("%s", &auxTitle) != 1) {
		printf("El valor ingresado no es válido, ingresa otro...\n");
		clearInputBuffer();
	};
	clearInputBuffer();
	
	// Sets the process title
	strcpy(process.title, auxTitle);
	
	// Asks the proces time and sets it
	printf("\nIngresa la duración del proceso en milisegundos:\n");
	while (scanf("%f", &process.timeLeft) != 1 && process.timeLeft <= 0) {
		printf("El valor ingresado no es válido, ingresa otro...\n");
		clearInputBuffer();
	};
	clearInputBuffer();
	
	// Asks the process priority and sets it
	printf("\nIngresa la prioridad del proceso representada como un número de 1 a 5, siendo 1 el de mayor precedencia:\n");
	while (scanf("%f", &process.priority) != 1 && process.timeLeft <= 0) {
		printf("El valor ingresado no es válido, ingresa otro...\n");
		clearInputBuffer();
	};
	clearInputBuffer();
	
	// Sets the process initial status
	strcpy(process.status, "Ready");
	system("cls");
	return process;
};

void populateProcessesList(struct Process processesList[], int initialProcessesQuantity) {	
	
	// Calls for createProcess() times initialProcessesQuantity
	int i;
	for (i = 0; i < initialProcessesQuantity; i++) {	
		processesList[i] = createProcess(); 
	};
};

void addNewProcess(struct Process processesList[], int arraySize) {
	int i;
	for (i = 0; i < arraySize; i++) {
		if (strcmp(processesList[i].status, "Completed") == 0) {
			processesList[i] = createProcess();
		};
		
		if (i == arraySize - 1) {
			printf("Memory is full now. Trya later.\n");
		}
		
		break;
	}
};

void runProcessesPlanner(struct Process processesList[], int arraySize, int algorithm) {
	switch (algorithm) {
		case 1:
			roundRobin(processesList, arraySize);
			break;
		case 2:
			priority(processesList, arraySize);
			break;
		default: // FIFO 
			fifo(processesList, arraySize);
	};
};

void roundRobin(struct Process processesList[], int arraySize) {
	int i;
	float quantum;
	clock_t startTime, currentTime;
	
	system("cls");
	
	printf("Ingresá la cantidad de tiempo que quieres asignar a cada proceso:\n");
	while (scanf("%f", &quantum) != 1 || quantum < 0) {
		printf("El valor ingresado no es válido, ingresa otro...\n");
		clearInputBuffer();
	};
	clearInputBuffer();
		
	while (!checkCompletion(processesList, arraySize)) {
		printf("\nNew Round:\n");

		for (i = 0; i < arraySize; i++) {
			if (strcmp(processesList[i].status, "Completed") == 0) {
				continue;
			}
			
			strcpy(processesList[i].status, "Running");

			startTime = clock();
			float passedTime = 0;
			
			int j = 0;
			while (passedTime < quantum) {
				currentTime = clock();
    			passedTime = (float)(currentTime - startTime) / CLOCKS_PER_SEC * 1000;
				if (j == 0) {
					printf("El proceso %s está en ejecución. Estado: %s.\n", processesList[i].title, processesList[i].status);
				}
				
				j++;
			};
			
			processesList[i].timeLeft -= quantum;
			
			if (processesList[i].timeLeft <= 0) {
				strcpy(processesList[i].status, "Completed");
				printf("\nEl proceso %s se ha completado. Estado: %s.\n", processesList[i].title, processesList[i].status);
			} else {
				strcpy(processesList[i].status, "Waiting");
				printf("\nEl proceso %s no se pudo completar. Estado: %s.\nCorriendo el siguiente en cola.\n", processesList[i].title, processesList[i].status);
			};
		}
	}
	
	printf("\nSe completaron todos los procesos en cola...\n");
}

void priority(struct Process processesList[], int arraySize) {	
	system("cls");

	sortByPriority(processesList, arraySize);
	runProcesses(processesList, arraySize);
	
	printf("\nSe completaron todos los procesos en cola...\n");
}

void fifo(struct Process processesList[], int arraySize) {
	system("cls");

	runProcesses(processesList, arraySize);
	
	printf("\nSe completaron todos los procesos en cola...\n");
}

void runProcesses(struct Process processesList[], int arraySize) {
	int i;
	for (i = 0; i < arraySize; i++) {
		float passedTime = 0;
		clock_t startTime, currentTime;
		
		startTime = clock();
		int j = 0;
		while (passedTime < processesList[i].timeLeft) {
			currentTime = clock();
			passedTime = (float)(currentTime - startTime) / CLOCKS_PER_SEC * 1000;
			if (j == 0) {
				printf("El proceso %s está en ejecución.\n", processesList[i].title);
			}
			j++;
		}
		
		strcpy(processesList[i].status, "Completed");
		printf("El proceso %s se ha completado.\n", processesList[i].title);
	}
}

void sortByPriority(struct Process processesList[], int arraySize) {
	int i, j;
	struct Process aux;
	
	for (i = 0; i < arraySize; i++) {
        for (j = i + i; j < arraySize; j++) {
            if (processesList[i].priority > processesList[j].priority) {
                aux = processesList[i];
				processesList[i] = processesList[j];
				processesList[j] = aux;
            }
        }
    };
};

bool checkCompletion(struct Process processesList[], int arraySize) {
	int i;
	
	for (i = 0; i < arraySize; i++) {
		if (strcmp(processesList[i].status, "Completed") != 0) {
			return false;
		}
	}
	
	return true;
}

