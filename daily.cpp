#include <iostream>
#include <vector>
#include "./Task/Task.hpp"
#include "./Person/Person.hpp"
#include <cstdlib>
#include <ctime>

// This is a algoritm aimed to maximy the daily outpouf of a random person.

using namespace std;
namespace daily
{

    Task::TaskType GetEnumerationById(int id)
    {
        return static_cast<Task::TaskType>(id);
    }

    vector<Task::Task> GetRandomTasks(int numberOfTasks,bool print=true)
    {
        int max;
        max = 100; // set the upper bound to generate the random number
        srand(time(0));
        vector<Task::Task> tasks;
        for (int i = 0; i < numberOfTasks; i++)
        {
            Task::Task task;
            task.name = "#" + std::to_string(i);
            task.TaskType = GetEnumerationById(rand() % 10);
            task.startingTime = time(0) + rand() % (23 * 3600*1000);
            task.duration = rand() * 1000 % (3600*1000);
            task.value = rand();
            tasks.push_back(task);
            int isChild = rand() % 3;
            if (isChild >= 1 && tasks.size() > 2)
            {
                tasks[rand() % (tasks.size() - 1)].Children.push_back(task);
            }
        }
        
        
        if(print){
        for (int i = 0; i < numberOfTasks; i++)
        {
            cout << tasks[i].startingTime << endl;
        }
        }

        return tasks;
    }
    void testDaily()
    {
        for (int i = 1; i < 100; i = i + 3)
        {
            cout << "iteration: " + to_string(i) << endl;
            auto tasks = daily::GetRandomTasks(i);
            for (int j = 1; j < tasks.size(); j++)
            {
                if (tasks[j - 1].startingTime > tasks[j].startingTime)
                {
                    throw invalid_argument("Order is faulty");
                }
            }
        }
    }
}

/* 
    Stating the problem:
    There are a subtotal on n tasks to be done in a single day.
    Some tasks have other tasks as prerequiosites.
    We have a limited time each day.
    We need to create an algorithm that will make us accomplish the optimal numbar of tasks each day.
    Multiple algorithms would be better.
*/
int main(int arg, char **args)
{
    // we generate random tasks
    vector<Task::Task> tasks = daily::GetRandomTasks(20,false);
    //daily::testDaily();
    // we sort them by starting date
    Task::QuickSortByStartingTime(tasks, 0, tasks.size() - 1);
    Task::DisplayTaskArray(tasks,10);

    return 0;
}