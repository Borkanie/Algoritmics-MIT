#include <iostream>
#include <vector>
#include "./Task/Task.hpp"
#include <cstdlib>
#include <ctime>

// This is a algoritm aimed to maximy the daily outpouf of a random person.

using namespace std;

Task::TaskType GetEnumerationById(int id)
{
    return static_cast<Task::TaskType>(id);
}

vector<Task::Task> GetRandomTasks(int numberOfTasks)
{
    int max;
    max = 100; // set the upper bound to generate the random number
    srand(time(0));
    vector<Task::Task> tasks;
    for (int i = 0; i < numberOfTasks; i++)
    {
        Task::Task task;
        task.TaskType = GetEnumerationById(rand() % 10);
        task.startingTime = time(0)+rand()%24*60000;
        task.duration = rand() % 60000;
        int numberOfChildren = rand() % 3;
        if (tasks.size() > numberOfChildren)
        {
            for (int j = 0; j < numberOfChildren; j++)
            {
                task.Children.push_back(tasks[rand() % tasks.size()]);
            }
        }
        cout << task;
    }
    return tasks;
}

/* Stating the problem:
 There are a subtotal on n tasks to be done in a single day.
 Some tasks have other tasks as prerequiosites.
 We have a limited time each day.
 We need to create an algorithm that will make us accomplish the optimal numbar of tasks each day.
 Multiple algorithms would be better.
*/
int main(int arg, char **args)
{
    GetRandomTasks(20);
    return 0;
}