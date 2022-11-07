#pragma once
#include <vector>
#include "../Task/Task.hpp"

namespace Person
{
#ifndef PersonConstants
#define PersonConstants
    inline int maxPoints=0;
    inline std::vector<Task::Task> bestRow;
    inline std::vector<Task::Task> currentRoad;
#endif

    class Person
    {
    public:
        Person();
        std::vector<Task::Task> GetOptimalTask(std::vector<Task::Task> possibleTasks);
        int Points;
        double TiredFactor;
        std::vector<Task::Task> tasks;
        friend std::ostream &operator<<(std::ostream &os, const Person &person)
        {
            os << "Person with the tasks: ";
            for (int i = 0; i < person.tasks.size(); i++)
            {
                os << person.tasks[i];
            }
            os << std::endl;
            return os;
        }
        void DisplayTasks(std::vector<Task::Task> tasks);
    };
    void RecursiveOptimalTaskByPoints(std::vector<Task::Task> tasks, int currentPoints = 0);
}