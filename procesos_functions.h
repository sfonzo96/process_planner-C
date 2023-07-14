#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Defines process structure (struct ~ object/class)
struct Process {
	char title[20];
	float timeLeft;
	char status[10];
	int priority;
};

//  -- Function Prototypes -- 
// Clears input buffer
void clearInputBuffer();
// Manages the cration of processes lists and algorithm choosing
void initProcessPlanner();
// Asks the user for project values and creates it
struct Process createProcessByUserInput();
// Populates the processesList, requires the list to be created with a specified size previously
void populateProcessesListByUserInput(struct Process processesList[], int initialProcessesQuantity);
// Populates the processesList getting the data from a .txt file (previously created)
void populateProcessesListByTxt(struct Process processesList[], int initialProcessesQuantity);
// Adds a process to the list by replacing a completed one - Not in use currently
void addNewProcess();
// Starts processes planner with the selected algorithm
void runProcessesPlanner(struct Process processesList[], int processesQuantity, int algorithm);
// Runs processes sequentially
void runProcesses(struct Process processesList[], int processesQuantity);
// Sorts the array by priority value (1 is most precedent)
void sortByPriority(struct Process processesList[], int processesQuantity);
// Runs Round Robin algorithm
void roundRobin(struct Process processesList[], int processesQuantity);
// Runs Priority algorithm
void priority(struct Process processesList[], int processesQuantity);
// Runs FIFO (First In First Out) algorithm
void fifo(struct Process processesList[], int processesQuantity);
// Prints all processes status
void printStatus(struct Process processesList[], int processesQuantity);
// Checks if all processes are completed (only for RR)
bool checkCompletion(struct Process processesList[], int length);
