#include "ToDoMain.h"
#include<iostream>
#include<fstream>
// #include<cstdio>
#include<string>

todo::todo():mainId(0)
{

}
int todo::getUserOption()
{
  int userOption = 0;
  string option;
  getline(cin,option);
  try
  {
    userOption = stoi(option);
    if(userOption > 5 || userOption <= 0)
      throw exception();
  }
  catch(const exception& e)
  {
    cout<<"\nWrong option - Choose again!\n"<<endl;
  }
  return userOption;
}
void todo::init()
{
  string id;
  string task;
  ofstream outfile("taskFile.txt",ios::out);
  while(true)
  {
    for(int i=0;i<50;i++)
      cout<<"*";
    cout<<"\nWelcome to To-Do List"<<endl;
    for(int i=0;i<50;i++)
      cout<<"*";
    cout<<endl;
    do
    {
      cout<<"1. Insert task"<<endl;
      cout<<"2. View all tasks"<<endl;
      cout<<"3. Search for a task"<<endl;
      cout<<"4. Delete a task"<<endl;
      cout<<"5. Update a task"<<endl;
      cout<<"Enter your option: "<<endl;
      int option = getUserOption();
      // deleteAlgorithm d;

      switch(option)
      {
        case 1: cout<<"\nEnter task: "<<endl;
                getline(cin,task);
                insertTask(task);
                break;
        case 2: viewTasks();
                break;
        case 3: searchTask();
                break;
        case 4: deleteTask();
                break;
        case 5: updateTask();
                break;
        default:cout<<"";
                break;
      }
    }while(true);
    outfile.seekp(0,ios::beg);
    outfile<<"";
  }
}
int todo::intToString()
{
  string id;
  cout<<"Enter task line number: ";
  getline(cin,id);
  int intId = stoi(id);
  return intId;
}

void todo::insertTask(string task)
{
  ofstream outFile("taskFile.txt",ios::app);
  mainId++;
  outFile<<task<<"\n";
  cout<<"\nTask inserted\n"<<endl;
  outFile.close();
}
void todo::deleteTask()
{
  ifstream inFile("taskFile.txt");
  ofstream ofile("taskFile2.txt",ios::out);
  inFile.seekg(0,ios::end);
  if(inFile.tellg() == 0)
    cout<<"\nNo tasks recorded yet to delete.\n"<<endl;
  else
  {
    inFile.seekg(0,ios::beg);
    string line;
    int intId = intToString();
    int current_id = 0;
    while(getline(inFile,line))
    {
      current_id++;
      if(current_id != intId)
      {
        ofile<<line<<endl;
      }
    }
    ofile.close();
    inFile.close();
    int status = remove("taskFile.txt");
    if(status == 0)
    {
      int renameStatus = rename("taskFile2.txt","taskFile.txt");
      if(renameStatus == 0)
        cout<<"Task Deleted\n"<<endl;
    }
    else
      cout<<"Task could not delete\n"<<endl;
  }
}
void todo::viewTasks()
{
  string line;
  ifstream inFile("taskFile.txt",ios::in);
  //checking if the file has records in it by placing the pointer to the end of file
  inFile.seekg(0,ios::end);
  if(inFile.tellg() == 0)
    cout<<"\nNo tasks recorded yet\n"<<endl;
  else
  {
    cout<<"Your tasks: \n"<<endl;
    // if not, replace the pointer to the first position
    inFile.seekg(0,ios::beg);
    for(int i=0;i<50;i++)
      cout<<"*";
    cout<<endl;
    while(getline(inFile,line))
      cout<<line<<"\n";
    for(int i=0;i<50;i++)
      cout<<"*";
    cout<<"\n\n";
  }
  inFile.close();
}
void todo::updateTask()
{
  ifstream inFile("taskFile.txt",ios::in);
  ofstream outFile("temp.txt",ios::out);
  inFile.seekg(0,ios::end);
  if(inFile.tellg() == 0)
    cout<<"\nNo tasks found for updation.\n"<<endl;
  else
  {
    try
    {
      inFile.seekg(0,ios::beg);
      string line;
      viewTasks();
      int intId = intToString();
      int current_id = 0;
      while(getline(inFile,line))
      {
        current_id++;
        if(current_id == intId)
        {
          string newLine;
          cout<<"Enter new task: "<<endl;
          getline(cin,newLine);
          line.replace(line.begin(),line.end(),newLine);
          outFile<<line<<endl;
        }
        else
          outFile<<line<<endl;
      }
    }
    catch(const exception& e)
    {
      cout<<"Bad input\n"<<endl;
    }
    outFile.close();
    inFile.close();
    int status = remove("taskFile.txt");
    if(status == 0)
    {
      int renameStatus = rename("temp.txt","taskFile.txt");
      if(renameStatus == 0)
        cout<<"\nTask updated\n"<<endl;
    }
    else
      cout<<"\nTask could not update\n"<<endl;
  }

}

void todo::searchTask()
{
  string line;
  string flagLine;
  ifstream inFile("taskFile.txt",ios::in);
  inFile.seekg(0,ios::end);
  if(inFile.tellg() == 0)
    cout<<"\nNo tasks to be searched for!\n"<<endl;
  else
  {
    viewTasks();
    inFile.seekg(0,ios::beg);
    try{
      int intId = intToString();
      int current_id = 0;
      int flag = 0;
      while(getline(inFile,line))
      {
        current_id++;
        if(current_id != intId)
        {
          continue;
        }
        else
        {
          flag = 1;
          flagLine = line;
        }
      }
      if(flag == 1)
        cout<<"\nSearch results\n"<<flagLine<<"\n"<<endl;
      else
        cout<<"\nNo such tasks found\n"<<endl;
    }
    catch(const exception& e)
    {
      cout<<"Bad input\n"<<endl;
    }
    inFile.close();
  }
}
