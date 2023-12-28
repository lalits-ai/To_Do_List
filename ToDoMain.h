#pragma once
#include<string>
using namespace std;

class todo
{
  private:
    int mainId;
    string task;
    int getUserOption();
  public:
    todo();
    void init();
    int intToString();
    void insertTask(string task);
    void deleteTask();
    void viewTasks();
    void updateTask();
    void searchTask();

};