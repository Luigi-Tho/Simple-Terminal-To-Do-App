#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "include/single_include/nlohmann/json.hpp"
using json = nlohmann::json;

class Task
{
private:
    std::string t_name;
    // stores the date as a string for easy access; uses YYYY-MM-DD HH:MM:SS.S format.
    std::string t_date;
    int t_status; // 0 = not started, 1 = in progress, 2 = done
    bool is_done; // is checked off if status is set to done

public:
    Task();
    Task(std::string);
    // Date uses YYYY-MM-DD HH:MM:SS.S format.
    Task(std::string, std::string);
    // Status: 0 = not started, 1 = in progress, 2 = done
    Task(std::string, std::string, int);
    std::string GetName();
    std::string GetDate();
    std::string GetStatus();
    bool isDone();
    // sets status to correct integer representation
    void SetStatus(std::string);
    // Direct integer assignment. 0 = not started, 1 = in progress, 2 = done.
    void SetStatus(int);
    void SetName(std::string);
    void SetDone(bool);
    void SetDate(std::string);
};

class ToDoList
{
private:
    std::vector<Task> todo;

public:
    ToDoList();
    ToDoList(std::vector<Task>);
    // void operator =(/*JSON object*/);
    void operator=(std::vector<Task>);
    void operator+=(Task);
    void operator+=(std::vector<Task>);
    friend std::ostream &operator<<(std::ostream &out, ToDoList list)
    {
        std::string header = "\tName    |     Due Date    |    Status";
        out << header << std::endl;
        out << "\t";
        for (int i = 0; i < header.size(); i++)
        {
            out << "-";
        }
        out << std::endl;

        for (int i = 0; i < list.size(); i++)
        {
            out << "\t" << list.at(i).GetName() << "    |    " << list.at(i).GetDate() << "    |    " << list.at(i).GetStatus() << std::endl;
        }
        return out;
    }
    void AddTasks(Task);
    void AddTasks(std::vector<Task>);
    void DeleteTasks();
    void DeleteTasks(std::string);
    Task &GetTask(std::string);
    Task at(int);
    size_t size();
    void Print();
    void Save();
    void Load();
};

// Task member functions
// Task constructors
Task::Task() {}
Task::Task(std::string name)
{
    t_name = name;
    t_status = 0;
    is_done = (t_status == 2);
}
Task::Task(std::string name, std::string date)
{
    t_name = name;
    t_date = date;
    t_status = 0;
    is_done = (t_status == 2);
}
Task::Task(std::string name, std::string date, int status)
{
    t_name = name;
    t_date = date;
    t_status = status;
    is_done = (t_status == 2);
}

std::string Task::GetName() { return t_name; }
std::string Task::GetDate() { return t_date; }
bool Task::isDone() { return is_done; }
std::string Task::GetStatus()
{
    switch (t_status)
    {
    case 1:
        return "in progress";
    case 2:
        return "done";
    default:
        return "not started";
    }
}

void Task::SetStatus(std::string status)
{
    if (status == "in progress")
    {
        t_status = 1;
    }
    else if (status == "done")
    {
        t_status = 2;
    }
    else
    {
        t_status = 0;
    }
}
void Task::SetStatus(int status) { t_status = status; }
void Task::SetName(std::string name) { t_name = name; }
void Task::SetDone(bool done)
{
    is_done = done;
    t_status = done ? 2 : 1;
}
void Task::SetDate(std::string date) { t_date = date; }

// To Do List Member Functions
ToDoList::ToDoList() {}

ToDoList::ToDoList(std::vector<Task> tasks)
{
    todo = tasks;
}

Task ToDoList::at(int index)
{
    return todo.at(index);
}

size_t ToDoList::size()
{
    return todo.size();
}

void ToDoList::operator=(std::vector<Task> tasks)
{
    todo = tasks;
}

void ToDoList::AddTasks(Task task)
{
    todo.push_back(task);
}

void ToDoList::AddTasks(std::vector<Task> tasks)
{
    for (int i = 0; i < tasks.size(); i++)
    {
        todo.push_back(tasks.at(i));
    }
}

void ToDoList::DeleteTasks()
{
    todo.clear();
}

void ToDoList::DeleteTasks(std::string name)
{
    for (int i = 0; i < todo.size(); i++)
    {
        if (name == todo.at(i).GetName())
        {
            todo.erase(todo.begin() + i);
            return;
        }
    }
}

Task &ToDoList::GetTask(std::string name)
{
    for (int i = 0; i < todo.size(); i++)
    {
        if (name == todo.at(i).GetName())
        {
            return todo.at(i);
        }
    }
    std::cout << "task not found" << std::endl;
    Task Temp("error");
    return Temp;
}

void ToDoList::Print()
{
    std::string header = "\tName    |     Due Date    |    Status";
    std::cout << header << std::endl;
    std::cout << "\t";
    for (int i = 0; i < header.size(); i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;

    for (int i = 0; i < todo.size(); i++)
    {
        std::cout << "\t" << todo.at(i).GetName() << "    |    " << todo.at(i).GetDate() << "    |    " << todo.at(i).GetStatus() << std::endl;
    }
}

void ToDoList::Save()
{
    std::ofstream out("todo.json");
    json j_todo;
    for (int i = 0; i < todo.size(); i++)
    {
        j_todo["Tasks"][i]["Name"] = todo.at(i).GetName();
        j_todo["Tasks"][i]["Date"] = todo.at(i).GetDate();
        j_todo["Tasks"][i]["Status"] = todo.at(i).GetStatus();
    }
    out << j_todo;
}

void Load(ToDoList &list)
{
    std::ifstream in("todo.json");
    json j = json::parse(in);
    Task temp;
    for (auto task : j)
    {
        for (int i = 0; i < task.size(); i++)
        {
            temp.SetName(task[i]["Name"].get<std::string>());
            temp.SetDate(task[i]["Date"].get<std::string>());
            temp.SetStatus(task[i]["Status"].get<std::string>());
            list += temp;
        }
    }
}

void ToDoList::operator+=(Task task)
{
    todo.push_back(task);
}

void ToDoList::operator+=(std::vector<Task> tasks)
{
    AddTasks(tasks);
}
