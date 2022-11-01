#include <iostream>
#include <vector>
#include <Task/Task.hpp>
#include <cstdlib>
// This is a algoritm aimed to maximy the daily outpouf of a random person.

using namespace std;

vector<Task::Task> GetRandomTasks(int numberOfTasks)
{
    int max;
    max = 100; // set the upper bound to generate the random number
    srand(time(0));
    vector<Task::Task> tasks;
    for (int i = 0; i < numberOfTasks; i++)
    {
        Task::Task task;
        task.TaskType = 
    }
    return tasks;
}

int main(int arg, char **args)
{

    return 0;
}