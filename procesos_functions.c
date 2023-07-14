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
	int processesQuantity;
	int arraySize;
	int chosenAlgorithm;
	int chosenLoadingMethod;
	
	// Asks the user for the amount of process the planner should start executing
	printf("Ingresa una cantidad inicial de procesos para que el sistema ejecute:\n");
	while (scanf("%d", &processesQuantity) != 1) {
		printf("El valor ingresado no es válido, ingresa otro...\n");
		clearInputBuffer();
	};
	clearInputBuffer();
	
	system("cls");
	
	// Asks for the desired loading method
	printf("Puedes cargar los procesos manualmente o mediante un archivo txt (previamente creado con formato similar a csv).\nIngresa el valor correspondiente:\n1- Manualmente\n2- Archivo .txt\n");
	while (scanf("%d", &chosenLoadingMethod) != 1 || chosenLoadingMethod < 0 || chosenLoadingMethod > 2) {
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
			printf("Elegiste el algoritmo Round Robin.\nEste asigna a cada proceso una porción de tiempo equitativa y ordenada, tratando a todos los procesos con la misma prioridad.\nPresiona cualquier tecla para continuar...\n");
			getch();
			break;
		case 2:
			printf("Elegiste el algoritmo por prioridad.\nEste ejecuta los procesos por completo en el orden de prioridad asignado.\nPresiona cualquier tecla para continuar...\n");
			getch();
			break;
		default:
			printf("Elegiste el algoritmo FIFO (First In First Out).\nEste ejecuta los procesos por completo en el orden que ingresan.\nPresiona cualquier tecla para continuar...\n");
			getch();
	};
	
	// Starts process planner
	struct Process processesList[processesQuantity];
	
	if (chosenLoadingMethod == 1 ) {
		populateProcessesListByUserInput(processesList, processesQuantity);
	} else {
		populateProcessesListByTxt(processesList, processesQuantity);
	}
	
	runProcessesPlanner(processesList, processesQuantity, chosenAlgorithm);
};

struct Process createProcessByUserInput() {
	
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

void populateProcessesListByUserInput(struct Process processesList[], int initialProcessesQuantity) {	
	
	// Calls for createProcess() times initialProcessesQuantity
	int i;
	for (i = 0; i < initialProcessesQuantity; i++) {	
		processesList[i] = createProcessByUserInput(); 
	};
};

void populateProcessesListByTxt(struct Process processesList[], int initialProcessesQuantity) {
	// https://www.tutorialspoint.com/c_standard_library/c_function_fgets.htm
	// https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
	// Trabajando con punteros y malloc se puede crear un array de manera dinámica sin necesidad de pedir al usuario la cantidad de procesos
	// Para ello se debe recorrer el .txt calculando la cantidad de saltos de línea que hay presentes
	FILE* processesListTxt = fopen(".\\processesList.txt", "r");
	
	if (processesListTxt == NULL) {
        printf("No se pudo cargar el archivo. Deberás ingresar los datos manualmente...\n");
        populateProcessesListByUserInput(processesList, initialProcessesQuantity);
    } else {
    	char line[1024];
    	int i = 0;
    	while(fgets(line, sizeof(line), processesListTxt) != NULL) {
    		// splits the string into tokens (substrings)
	    	char *token = strtok(line, ",");
	    	
	    	// Checks for token
			if (token != NULL) {
				strcpy(processesList[i].title, token);
				// Moves to next token
				token = strtok(NULL, ",");
			}
			
			if (token != NULL) {
				processesList[i].timeLeft = atof(token);
				token = strtok(NULL, ",");
			}
			
			if (token != NULL) {
				strcpy(processesList[i].status, token);
				token = strtok(NULL, ",");
			}
			
			if (token != NULL) {
				processesList[i].priority = atoi(token);
				token = strtok(NULL, ",");
			}
	        
	        i++;
		};
		
		// Closes file access
		fclose(processesListTxt);
		
		// If the same, data should have been asigned correctly, asumming correct csv order
		if (i!= initialProcessesQuantity) {
			printf("%d , %d", i, initialProcessesQuantity);
			printf("La cantidad de procesos en el archivo no coincide con la que elegiste inicialmente.\nReinicia el programa.");
			exit(1);
		}
	}; 
}

void addNewProcess(struct Process processesList[], int processesQuantity) {
	// Not used currently
	int i;
	for (i = 0; i < processesQuantity; i++) {
		if (strcmp(processesList[i].status, "Completed") == 0) {
			processesList[i] = createProcessByUserInput();
		};
		
		if (i == processesQuantity - 1) {
			printf("Memory is full now. Trya later.\n");
		}
		
		break;
	}
};

void runProcessesPlanner(struct Process processesList[], int processesQuantity, int algorithm) {
	// Defines which algorithm will be executed on user's choice
	switch (algorithm) {
		case 1:
			roundRobin(processesList, processesQuantity);
			break;
		case 2:
			priority(processesList, processesQuantity);
			break;
		default: // FIFO 
			fifo(processesList, processesQuantity);
	};
};

void roundRobin(struct Process processesList[], int processesQuantity) {
	float quantum;
	clock_t startTime, currentTime;
	
	system("cls");
	
	printf("Ingresá la cantidad de tiempo que quieres asignar a cada proceso:\n");
	while (scanf("%f", &quantum) != 1 || quantum < 0) {
		printf("El valor ingresado no es válido, ingresa otro...\n");
		clearInputBuffer();
	};
	clearInputBuffer();
		
	while (!checkCompletion(processesList, processesQuantity)) {
		system("cls");
		printf("\nNew Round:\n");

		for (int i = 0; i < processesQuantity; i++) {
			// Skips the process if status == Completed
			if (strcmp(processesList[i].status, "Completed") == 0) {
				continue;
			}
			
			strcpy(processesList[i].status, "Running");
			
			printStatus(processesList, processesQuantity);
						
			// Resets the passed time
			float passedTime = 0;
			
			// Gets the starting clock time
			startTime = clock();
			
			while (passedTime < quantum) {
				// Sets the current clock time
				currentTime = clock();
				
				// Calculated the time passed in ms
    			passedTime = (float)(currentTime - startTime) / CLOCKS_PER_SEC * 1000;
			};
			// Subtracts the quantum from the time left and completes the process or puts in a waiting state
			if ((processesList[i].timeLeft -= quantum) <= 0) {
				strcpy(processesList[i].status, "Completed");	
			} else {
				strcpy(processesList[i].status, "Waiting");
			};
		}
		
		printStatus(processesList, processesQuantity);
	}
	
	printf("\nSe completaron todos los procesos en cola...\n");
}

void priority(struct Process processesList[], int processesQuantity) {	
	system("cls");
	
	// Sorts by priority value (asc)
	sortByPriority(processesList, processesQuantity);
	// Runs processes sequentially
	runProcesses(processesList, processesQuantity);
	
	printf("\nSe completaron todos los procesos en cola...\n");
}

void fifo(struct Process processesList[], int processesQuantity) {
	system("cls");
	
	// Runs processes sequentially
	runProcesses(processesList, processesQuantity);
	
	printf("\nSe completaron todos los procesos en cola...\n");
}

void runProcesses(struct Process processesList[], int processesQuantity) {
	int i;
	for (i = 0; i < processesQuantity; i++) {
		float passedTime = 0;
		clock_t startTime, currentTime;
		
		printStatus(processesList, processesQuantity);
		
		// Gets the starting clock time
		startTime = clock();
		// Loops until passed time is equal to timeLeft (i.e. process complete)
		while (passedTime < processesList[i].timeLeft) {
			currentTime = clock();
			passedTime = (float)(currentTime - startTime) / CLOCKS_PER_SEC * 1000;
		}
		
		strcpy(processesList[i].status, "Completed");
		
		printStatus(processesList, processesQuantity);
	}
}

void printStatus(struct Process processesList[], int processesQuantity) {
	system("cls");
	for (int j = 0; j < processesQuantity; j++) {
		printf("\nEl proceso %s está en ejecución. Estado: %s.\n", processesList[j].title, processesList[j].status);
	}
}

void sortByPriority(struct Process processesList[], int processesQuantity) {
	int i, j;
	struct Process aux;
	
	// For each element, checks all of the others to the right, and swaps if priority is precendent (1 is most)
	for (i = 0; i < processesQuantity; i++) {
        for (j = i + 1; j < processesQuantity; j++) {
            if (processesList[i].priority > processesList[j].priority) {
                aux = processesList[i];
				processesList[i] = processesList[j];
				processesList[j] = aux;
            }
        }
    };
};

bool checkCompletion(struct Process processesList[], int processesQuantity) {
	int i;
	
	// Looks for a process that's not already completed, if there isn't any will return true and the RR algorithm will end
	for (i = 0; i < processesQuantity; i++) {
		if (strcmp(processesList[i].status, "Completed") != 0) {
			return false;
		}
	};
	
	return true;
}

