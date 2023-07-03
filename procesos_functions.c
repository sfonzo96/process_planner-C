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
	
	// Asks for the desired algorithm
	printf("Ingresa el valor del algoritmo deseado para ejecutar los procesos:\n1- Round Robin\n2- Por priodidad\n3- FIFO\n");
	while (scanf("%d", &chosenAlgorithm) != 1 || chosenAlgorithm < 0 || chosenAlgorithm > 3) {
		printf("El valor ingresado no es válido, ingresa otro...\n");
		clearInputBuffer();
	};
	clearInputBuffer();
	
	system("cls");
	
	// Shows info on the chosen algorithm
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
	
	// Starts process planner
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
	// Not used currently
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
	// Defines which algorithm will be executed on user's choice
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
			// Skips the process if status == Completed
			if (strcmp(processesList[i].status, "Completed") == 0) {
				continue;
			}
			
			strcpy(processesList[i].status, "Running");

			// Gets the starting clock time
			startTime = clock();
			
			// Resets the passed time
			float passedTime = 0;
			
			int j = 0;
			while (passedTime < quantum) {
				// Sets the current clock time
				currentTime = clock();
				
				// Calculated the time passed in ms
    			passedTime = (float)(currentTime - startTime) / CLOCKS_PER_SEC * 1000;
				if (j == 0) {
					printf("El proceso %s está en ejecución. Estado: %s.\n", processesList[i].title, processesList[i].status);
				}
				
				j++;
			};
			// Subtracts the quantum from the time left and completes the process or puts in a waiting state
			if ((processesList[i].timeLeft -= quantum) <= 0) {
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
	
	// Sorts by priority value (asc)
	sortByPriority(processesList, arraySize);
	// Runs processes sequentially
	runProcesses(processesList, arraySize);
	
	printf("\nSe completaron todos los procesos en cola...\n");
}

void fifo(struct Process processesList[], int arraySize) {
	system("cls");
	
	// Runs processes sequentially
	runProcesses(processesList, arraySize);
	
	printf("\nSe completaron todos los procesos en cola...\n");
}

void runProcesses(struct Process processesList[], int arraySize) {
	int i;
	for (i = 0; i < arraySize; i++) {
		float passedTime = 0;
		clock_t startTime, currentTime;
		
		// Gets the starting clock time
		startTime = clock();
		int j = 0;
		// Loops until passed time is equal to timeLeft (i.e. process complete)
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
	
	// For each element, checks all of the others to the right, and swaps if priority is precendent (1 is most)
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
	
	// Looks for a process that's not already completed, if there isn't any will return true and the RR algorithm will end
	for (i = 0; i < arraySize; i++) {
		if (strcmp(processesList[i].status, "Completed") != 0) {
			return false;
		}
	};
	
	return true;
}

