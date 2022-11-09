#include <vector>
#include <ctime>
#include <iostream>
#include "Task.hpp"
#ifndef TaskBuffer
#define TaskBuffer
namespace TaskStreamBuffer
{
    /**
     * This class will bge used as a buffer for displaying a task array.
     * It will be fed the array and will in the background create a character array equal to the entire picture.
     * It will take into account the 2 spaces lost by the '[' ']' characters of the day line.
    */
    class TasksStreamBuffer
    {
    private:
        int minutesPerBar = 10;
        int numberOfDisplayedHours = 24;
        void AddTask(Task::Task tasks,int lineIndex);
        int width =0;
        long startingTime; 

    public:
        // Creates an instance of a buffer with a fixed temporal size on each bar and a total spantime covered
        TasksStreamBuffer(int minutesPerBar = 10, int numberOfHours = 24);
        // This is where the output will be stored.
        std::vector<std::vector<char>> Buffer;
        // We ovverride the operator to dump the buffer on the std::cout
        friend std::ostream &operator<<(std::ostream &os, const TasksStreamBuffer &buffer);
        /* Adds a task array to the buffer.
        * It does not check for overlaping tasks so we need to maake sure they do not overlap.
        * @param tasks : The vector of tasks we want to add to the buffer
        * @param lastIndex : The index where we will write the given task vector. 
        * If the value is smaller or equal to 0 or if it will be greater than the size of the buffer we will set the tasks in the last line of the buffer.
        */
        void AddTasksArray(std::vector<Task::Task> tasks,int lineIndex = 0);
        // Displays this buffers time interval as a loing line.
        void DisplayDayAsFlatLine();
    };
}

#endif