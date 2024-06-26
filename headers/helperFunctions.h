#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <iostream>
#include <string>
#include <ctime>
#include "../headers/TaskList.h"

using namespace std;

void printMainMenu();
void displayTasks(TaskList *);
void taskToAdd(TaskList *);
void subtaskToAdd(MainTask *);
void subtaskToDelete(MainTask *, TaskList *);
void taskToDelete(TaskList *);
void taskToEdit(TaskList *);
void subtaskToEdit(MainTask *, TaskList *);
void sortTasks(TaskList *);
time_t _addRecurring(time_t oldDeadLine, uint recurringDay);
int getUserInputInteger();
time_t getUserInputDdl();
int getUserInputIntegerForMinute();
std::string getUserInputString();
void exportTaskListToTxt(TaskList *taskList, const std::string &file_path);

#endif