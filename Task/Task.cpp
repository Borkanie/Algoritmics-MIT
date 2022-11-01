#include "Task.hpp"
#include "vector"

namespace Task
{
    int Task::Duration()
    {
        return this->EndingTime - this->StartingTime;
    };

    int Task::Cost()
    {
        int cost = 0;
        for (int i = 0; i < this->prerequisites.size(); i++)
        {
            cost += this->prerequisites[i].Cost();
        }
        return this->TaskType * this->Duration() + cost;
    };
}