#include "gtest/gtest.h"
#include "../headers/TaskList.h"
#include <time.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include "../headers/MainTask.h"
#include "../headers/dfs.h"
using namespace std;

TEST(TaskList, TestSortbyPriority)
{

    TaskList tasklist = TaskList();
    MainTask *task1 = new MainTask();
    MainTask *task2 = new MainTask();
    MainTask *task3 = new MainTask();

    task1->editPriority(3);
    task2->editPriority(2);
    task3->editPriority(1);

    tasklist.addTask(task1);
    tasklist.addTask(task2);
    tasklist.addTask(task3);
    tasklist.sort(1);

    EXPECT_EQ(tasklist.getAllTasks().at(0)->getPriority(), 1);
    EXPECT_EQ(tasklist.getAllTasks().at(1)->getPriority(), 2);
    EXPECT_EQ(tasklist.getAllTasks().at(2)->getPriority(), 3);
}

TEST(TaskList, TestSortbyDdl)
{

    time_t timep1;
    time_t timep2;
    time_t timep3;

    TaskList taskList = TaskList();
    MainTask *task1 = new MainTask();
    MainTask *task2 = new MainTask();
    MainTask *task3 = new MainTask();

    task1->editDdl(timep1);

    timep2 = timep1 + 100;
    task2->editDdl(timep2);

    timep3 = timep1 + 200;
    task3->editDdl(timep3);

    std::cout << timep1 << "," << timep2 << "," << timep3 << std::endl;

    taskList.addTask(task3);
    taskList.addTask(task2);
    taskList.addTask(task1);
    taskList.sort(2);

    EXPECT_EQ(taskList.getAllTasks().at(0)->getDdl(), timep1);
    EXPECT_EQ(taskList.getAllTasks().at(1)->getDdl(), timep2);
    EXPECT_EQ(taskList.getAllTasks().at(2)->getDdl(), timep3);
}

TEST(TaskList, TestDeleteTask)
{

    TaskList taskList = TaskList();
    // MainTask* newTask = new MainTask();
    MainTask *task1 = new MainTask();

    taskList.addTask(task1);
    taskList.deleteTask(1);

    EXPECT_EQ(taskList.getAllTasks().size(), 0);
}

TEST(TaskList, TestAddTask_size)
{

    TaskList taskList = TaskList();
    MainTask *newTask = new MainTask();
    MainTask *task1 = new MainTask();
    taskList.addTask(task1);
    taskList.addTask(newTask);

    EXPECT_EQ(taskList.getAllTasks().size(), 2);
}

TEST(TaskList, TestAddTask_content_ddl)
{

    TaskList taskList = TaskList();
    MainTask *newTask = new MainTask();
    time_t timep1;
    time_t timep2;
    time(&timep1);
    timep2 = timep1 + 100;
    newTask->editDdl(timep1);
    ASSERT_EQ(newTask->getDdl(), timep1);

    MainTask *task1 = new MainTask();
    task1->editDdl(timep2);
    ASSERT_EQ(task1->getDdl(), timep2);
    ASSERT_EQ(newTask->getDdl(), timep1);

    taskList.addTask(task1);
    taskList.addTask(newTask);

    EXPECT_EQ(taskList.getAllTasks()[0]->getDdl(), timep2);
    EXPECT_EQ(taskList.getAllTasks()[1]->getDdl(), timep1);
}

TEST(TaskList, TestAddTask_content_priority)
{
    TaskList taskList = TaskList();
    MainTask *task2 = new MainTask();
    task2->editPriority(2);
    ASSERT_EQ(task2->getPriority(), 2);

    MainTask *task1 = new MainTask();
    task1->editPriority(1);
    ASSERT_EQ(task1->getPriority(), 1);

    taskList.addTask(task1);
    taskList.addTask(task2);

    EXPECT_EQ(taskList.getAllTasks()[0]->getPriority(), 1);
    EXPECT_EQ(taskList.getAllTasks()[1]->getPriority(), 2);
}

TEST(TaskList, TestUpdateDdl)
{

    time_t timep1;
    time_t timep2;
    time_t timep3, timep4;

    time(&timep1);
    timep1 -= 20;

    TaskList taskList = TaskList();

    MainTask *task1 = new MainTask(); // passes
    task1->editDdlPassed(true);
    task1->editRecurringEventTime(1);
    task1->editDdl(timep1);

    MainTask *task2 = new MainTask(); // not passed, don't change
    task2->editDdlPassed(false);
    task2->editRecurringEventTime(3);
    timep2 = timep1 + 1000;
    task2->editDdl(timep2);

    MainTask *task3 = new MainTask(); // false but already passed, needs to be changed
    task3->editDdlPassed(false);
    task3->editRecurringEventTime(2);
    timep3 = timep1 - 1000;
    task3->editDdl(timep3);

    MainTask *task4 = new MainTask(); // no recurring
    task4->editDdlPassed(false);
    task4->editRecurringEventTime(0);
    timep4 = timep1 - 1500;
    task4->editDdl(timep4);

    taskList.addTask(task1);
    taskList.addTask(task2);
    taskList.addTask(task3);
    taskList.addTask(task4);
    sleep(1);
    uint pid = taskList.updateDdl();
    sleep(2);

    EXPECT_TRUE(pid > 0);
    std::cout << timep1 << "," << timep2 << "," << timep3 << "," << timep4 << std::endl;
    EXPECT_EQ(taskList.getAllTasks().at(0)->getDdl(), timep1 + ONE_DAY);
    EXPECT_EQ(taskList.getAllTasks().at(1)->getDdl(), timep2);
    EXPECT_EQ(taskList.getAllTasks().at(2)->getDdl(), timep3 + ONE_DAY * 2);
    EXPECT_EQ(taskList.getAllTasks().at(3)->getDdl(), timep4);
}
