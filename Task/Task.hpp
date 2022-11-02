#include <vector>
// overload_date.cpp
// compile with: /EHsc
#include <iostream>
#include <string>
#include <ctime>
#pragma once
namespace Task
{
    enum TaskType
    {
        Relaxation = 1,
        Work = 2,
        Enjoyment = 3,
        Sleep = 4,
        Eating = 5,
        Learning = 6,
        Research = 7,
        Side_Projects = 8,
        Side_Hustle = 9,
    };
    /* An abstraction of a class. Multiple tasks can be related or not.
    Each group fo ralated tasks can be seen as a tree with a variable number of leafes.
    The cost of the task will only be represinted by the time spent on the task.
    The value of the task will be a fixed number.
    */
    class Task
    {
    private:
        std::vector<Task> prerequisites;

    public:
        Task(){};
        Task(std::vector<Task> prerequisites)
        {
            this->prerequisites = prerequisites;
        };
        // The name of the task
        std::string name;
        // The time when the task should start
        time_t startingTime;
        // The percieved value of the task
        int value;
        // The density of the task, which is defined as the value of the task divided by the amount of effort in the form of time consumed by the task
        double Density() const;
        // The total duration on the task in ms
        int duration;
        // The total duration of the task displayed in a stirng format
        std::string Duration() const ;
        // The total value of the task togheter with all it's children
        int TotalValue() const ;
        // The total time consumed by the task and all it's children
        int TotalTime() const ;
        // The type of the task
        TaskType TaskType;
        // The list of children
        std::vector<Task> Children;
        friend std::ostream& operator<<(std::ostream& os,const Task& task){
            os << "Task: " << task.name << " with the duration of: " << task.Duration() << " and the value of: " << task.value << " and the Children:";
            for(int i=0;i<task.Children.size();i++){
                os << task.Children[i];
            }
            os << std::endl;
            return os;
        }
    };
}