#include "Task.hpp"
#include "vector"
#include <ctime>
#include <stdlib.h>

namespace Task
{
    
    int DisplayDayAsFlatLine(int minutePerBar)
    {
        std::cout << "[";
        for (int i = 0; i < 24 * 60 / minutePerBar; i++)
        {
            if (i * minutePerBar % 60 == 0)
            {
                std::cout << "|";
            }
            else
            {
                std::cout << "-";
            }
        }
        std::cout << "]";
        return 24 * 60 / minutePerBar;
    }
    long Task::EndTime() const
    {
        return this->startingTime + this->duration;
    }

    bool Task::OverLap(const Task task) const
    {
        if(this->startingTime == 0){
            return false;
        }
        bool taskStartsBeforeThisEnds=task.startingTime <= this->EndTime() ;
        bool taskStartAfterThisStarts=task.startingTime >= this->startingTime;
        bool thisStartsBeforeTaskEnds = this->startingTime <= task.EndTime();
        bool thisStartsAfterTAskStarts = this->startingTime >= task.startingTime;
        bool taskStartWhileThisIsRunning =( taskStartsBeforeThisEnds && taskStartAfterThisStarts);
        bool thisStartsWhileTaskIsRunning = (thisStartsBeforeTaskEnds && thisStartsAfterTAskStarts);
        return taskStartWhileThisIsRunning || thisStartsWhileTaskIsRunning;
    }

    bool Task::DoesNotOverLapWithArray(const std::vector<Task> tasks) const
    {
        for (int i = 0; i < tasks.size(); i++)
        {
            if (this->OverLap(tasks[i]))
            {
                return false;
            }
        }
        return true;
    }

    std::vector<std::vector<Task>> GetNonOverlappingArraysFromArray(std::vector<Task> tasks)
    {
        using namespace std;
        vector<vector<Task>> nonOverlappingTasks;
        nonOverlappingTasks.push_back(vector<Task>());
        nonOverlappingTasks[0].push_back(tasks[0]);
        tasks.erase(tasks.begin() + 0);
        while (tasks.size() > 0)
        {
            int suitableIndex = -1;
            // we search for the first array that can hold this task
            for (int i = 0; i < nonOverlappingTasks.size(); i++)
            {
                if (tasks[0].DoesNotOverLapWithArray(nonOverlappingTasks[i]))
                {
                    suitableIndex = i;
                    break;
                }
            }
            // if we found an array we add it there
            if (suitableIndex >= 0)
            {
                nonOverlappingTasks[suitableIndex].push_back(tasks[0]);
            }
            else
            {
                nonOverlappingTasks.push_back(vector<Task>());
                nonOverlappingTasks[nonOverlappingTasks.size() - 1].push_back(tasks[0]);
            }
            // we remove the task from the array
            tasks.erase(tasks.begin() + 0);
        }
        return nonOverlappingTasks;
    }

    void DisplayTaskNonOverlappingArray(const std::vector<Task> tasks, int minutePerBar)
    {
        long startingTime = std::time(0);
        int currenttask = 0;
        for (int i = 0; i < 24 * 60 / minutePerBar; i++)
        {
            if ((startingTime + (i - 1) * minutePerBar * 60 * 1000 <= tasks[currenttask].startingTime))
                if ((tasks[currenttask].startingTime <= startingTime + (i + 1) * minutePerBar * 60 * 1000))
                {
                    // std::cout<<std::ctime(&tasks[currenttask].startingTime);
                    DisplayTaskAsFlatLine(tasks[currenttask], minutePerBar);
                    i += tasks[currenttask].duration / (60 * 1000 * minutePerBar);
                    currenttask++;
                    continue;
                }
            std::cout << " ";
        }
        std::cout << std::endl;
    }

    void DisplayTaskArray(std::vector<Task> tasks, int minutePerBar)
    {

        // Length of the day
        int numberOfDotsOnLine = DisplayDayAsFlatLine(minutePerBar);
        std::cout << std::endl;
        // We always have to start from '1' becaus of '['

        // we split them into lsits of non ovelapping arrays
        std::vector<std::vector<Task>> nonOverlappingArrays = GetNonOverlappingArraysFromArray(tasks);

        for (int i = 0; i < nonOverlappingArrays.size(); i++)
        {
            DisplayTaskNonOverlappingArray(nonOverlappingArrays[i], minutePerBar);
        }
    }

    void DisplayTaskAsFlatLine(Task task, int minutePerBar)
    {
        for (int i = 0; i <= task.duration / (1000 * 60); i += minutePerBar)
        {
            std::cout << task.Sign;
        }

    }

    int partition(std::vector<Task> &arr, int low, int high, long pivot)
    {
        int i = low;
        int j = low;
        while (i <= high)
        {
            if (arr[i].startingTime > pivot)
            {
                i++;
            }
            else
            {
                std::swap(arr[i], arr[j]);
                i++;
                j++;
            }
        }
        return j - 1;
    }

    void QuickSortByStartingTime(std::vector<Task> &arr, int low, int high)
    {
        if (low < high)
        {
            long pivot = arr[high].startingTime;
            int pos = partition(arr, low, high, pivot);

            QuickSortByStartingTime(arr, low, pos - 1);
            QuickSortByStartingTime(arr, pos + 1, high);
        }
    }

    double Task::Density() const
    {
        return ((double)this->value) / ((double)this->duration);
    }

    long Task::TotalTime() const
    {
        long value = 0;
        for (int i = 0; i < this->prerequisites.size(); i++)
        {
            value += this->prerequisites[i].TotalTime();
        }
        return this->duration + value;
    };

    int Task::TotalValue() const
    {
        int value = 0;
        for (int i = 0; i < this->prerequisites.size(); i++)
        {
            value += this->prerequisites[i].TotalValue();
        }
        return this->value + value;
    };

    std::string Task::Duration() const
    {
        std::string result = "";
        // from ms to s
        long duration = this->duration / 1000;
        int months = duration / (60 * 60 * 24 * 30);
        int days = (duration - (60 * 60 * 24 * 30) * months) / (60 * 60 * 24);
        int hours = (duration - (60 * 60 * 24 * 30) * months - (60 * 60 * 24) * days) / (60 * 60);
        int minutes = (duration - (60 * 60 * 24 * 30) * months - (60 * 60 * 24) * days - hours * 60 * 60) / 60;
        int seconds = (duration - (60 * 60 * 24 * 30) * months - (60 * 60 * 24) * days - hours * 60 * 60 - minutes * 60);
        if (months > 0)
        {
            result += " Months: ";
            result += std::to_string(months);
        }

        if (days > 0)
        {
            result += " Days: ";
            result += std::to_string(days);
        }

        if (hours > 0)
        {
            result += " hours: ";
            result += std::to_string(hours);
        }

        if (minutes > 0)
        {
            result += " Minutes: ";
            result += std::to_string(minutes);
        }

        if (seconds > 0)
        {
            result += " Seconds: ";
            result += std::to_string(seconds);
        }
        return result;
    };
}