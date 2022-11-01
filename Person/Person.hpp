#pragma once
#include <vector>
#include "../Task/Task.hpp"

namespace Person
{
    class Person
    {
    public:
        Person();
        std::vector<Task::Task> GetOptimalTask(std::vector<Task::Task> PossibleTasks);
        int Points;
        double TiredFactor;
    };
}