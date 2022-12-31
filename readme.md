# Simple Terminal To-Do App

## How it Works
The to-do program prints/updates the todo list everytime a command is used.

### Task Features
\
![Empty To-Do App](readme_pics/Screenshot%202022-12-30%20at%2023.41.51.png)
\
\
Each task has 4 components that can be manipulated according to the commands listed below:
- __Name__
- __Associated Date__ (can represent a due date or some other kind of date)
  - Date does not come with reminders. That may come in a future update, but I'm not promising anything.
- __Status__
  - Can be one of the following:
    - Not started
    - In Progress
    - Done
- __Done/Checked__
  - If changed, status is changed automatically

\
![To-Do App With Tasks](readme_pics/Screenshot%202022-12-30%20at%2023.48.13.png)

### Commands
Interacting with the to-do program is done with a set of commands, listed as follows:

- __help/commands__ - Lists the commands supported by the to-do program
- __add__ - Adds a task to the list
  - asks for the name, associated date, and status of said task
- __delete__ - deletes a task
  - asks for the name of the task to be deleted
- __check__ - marks a task as done
  - asks for the name of the task
- __change status__ - changes the status of a task (ex: from "not started" to "in progress")
  - asks for the name of task and the new status to change to
- __clear__ - clears the entire to-do list
- __save__ - saves the to-do list to a JSON file titled "todo.json"
  - if said JSON file does not exist, the program will create it for you
- __load__ - loads a to-do list from said JSON file stored on disk
- __exit__ - exits the program

__Command Examples__:
![Add Command](readme_pics/Screenshot%202022-12-30%20at%2023.49.40.png)
\
\
![Change Status Command](readme_pics/Screenshot%202022-12-30%20at%2023.49.59.png)

NOTE: commands are case-sensitive, so make sure to type them in all lowercase.

## Installation Instructions
Should work for Mac & Windows
1. go to the git branch labeled for your operating system
   - MacOS branch for mac
   - Windows branch for windows
2. download the code as a zip file
3. unzip file
4. click on executable file to open the program
