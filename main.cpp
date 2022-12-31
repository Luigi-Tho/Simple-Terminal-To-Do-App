#include <fstream>
#include <iostream>
#include <string>

#include "todo.h"

using namespace std;

int main()
{
    ToDoList t_list;
    std::string command;
    bool exit = false;

    while (!exit)
    {
        std::cout << t_list;
        getline(cin, command);
        if (command.find("add") != string::npos)
        {
            Task task;
            cout << "name: ";
            getline(cin, command);
            task.SetName(command);
            cout << "due date (YYYY-MM-DD): ";
            getline(cin, command);
            task.SetDate(command);
            task.SetStatus(0);
            t_list += task;
        }

        else if (command.find("delete") != string::npos)
        {
            cout << "name: ";
            getline(cin, command);
            t_list.DeleteTasks(command);
        }

        else if (command.find("check") != string::npos)
        {
            cout << "name: ";
            getline(cin, command);
            t_list.GetTask(command).SetDone(true);
        }

        else if (command.find("change status") != string::npos)
        {
            cout << "name: ";
            getline(cin, command);
            Task temp(command);
            cout << "new status: ";
            getline(cin, command);
            t_list.GetTask(temp.GetName()).SetStatus(command);
        }

        else if (command.find("rename") != string::npos)
        {
            cout << "name of task to change: ";
            getline(cin, command);
            Task temp = t_list.GetTask(command);
            t_list.DeleteTasks(command);
            cout << "new name for task: ";
            getline(cin, command);
            temp.SetName(command);
            t_list.AddTasks(temp);
        }

        else if (command.find("clear") != string::npos)
        {
            t_list.DeleteTasks();
        }

        else if (
            (command.find("help") != string::npos) || (command.find("commands") != string::npos))
        {
            cout << "Commands:" << std::endl;
            cout << "help/commands\tLists valid commands" << std::endl;
            cout << "add\tAdd a task to list" << std::endl;
            cout << "delete\tDelete a task from list" << std::endl;
            cout << "check\tMarks a task in a list as done" << std::endl;
            cout << "change status\tChanges the status of a task in a list" << std::endl;
            cout << "clear\tClear all tasks in a list" << std::endl;
            cout << "save\tSaves all tasks in a list to disk" << std::endl;
            cout << "load\tLoads a list from disk" << std::endl;
            cout << "exit\tCloses the to-do program" << std::endl;
            cout << endl;
        }

        else if (command.find("load") != string::npos)
        {
            Load(t_list);
        }

        else if (command.find("save") != string::npos)
        {
            t_list.Save();
        }

        else if (command.find("exit") != string::npos)
        {
            exit = true;
        }
    }
}