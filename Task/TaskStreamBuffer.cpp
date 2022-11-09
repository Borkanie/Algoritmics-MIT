#include <vector>
#include <iostream>
#include "TaskStreamBuffer.hpp"
#include "Task.hpp"
#include <ctime>

#ifdef TaskBuffer
#ifndef TaskBufferImplementation
#define TaskBufferImplementation
namespace TaskStreamBuffer
{

    TasksStreamBuffer::TasksStreamBuffer(int minutesPerBar, int numberOfHours)
    {
        this->startingTime = time(0);
        this->minutesPerBar = minutesPerBar;
        this->numberOfDisplayedHours = numberOfHours;
        this->width = this->numberOfDisplayedHours * 60 / this->minutesPerBar + 2;
        this->DisplayDayAsFlatLine();
    }

    void TasksStreamBuffer::DisplayDayAsFlatLine()
    {
        std::vector<char> line;
        char c = '[';
        line.push_back('[');
        for (int i = 1; i < this->width - 1; i++)
        {
            if (i * this->minutesPerBar % 60 == 0)
            {
                line.push_back('|');
            }
            else
            {
                line.push_back('-');
            }
        }
        line.push_back((']'));
        this->Buffer.push_back(line);
    }

    void TasksStreamBuffer::AddTask(Task::Task task, int lineIndex)
    {
        int startingIndex = (task.startingTime - this->startingTime) / (60000 * minutesPerBar) + 1;
        int lastIndex = (task.EndTime() - this->startingTime) / (60000 * minutesPerBar) + 1;
        // If lineIndex is specified we will use that if not we will use the last line available.
        if (lineIndex > this->Buffer.size() || lineIndex <= 0)
        {
            lineIndex = this->Buffer.size() - 1;
        }
        // In case the task is longer than 3 intervals we can sorround it by  '[' and ']'
        if (lastIndex - startingIndex >= 3)
        {
            this->Buffer[lineIndex][lastIndex--] = ']';
            this->Buffer[lineIndex][startingIndex++] = '[';
        }
        // Here we jsut replace all the signs in the size with the tasks sign.
        for (int i = startingIndex; i <= lastIndex; i++)
        {
            this->Buffer[lineIndex][i] = task.Sign;
        }
    }

    void TasksStreamBuffer::AddTasksArray(std::vector<Task::Task> tasks, int lineIndex)
    {
        std::vector<char> charArray(this->width, ' ');
        if (lineIndex < 1 && lineIndex < this->Buffer.size())
        {
            this->Buffer.push_back(charArray);
        }
        else
        {
            this->Buffer.at(lineIndex) = charArray;
        }
        for (int i = 1; i < tasks.size(); i++)
        {
            this->AddTask(tasks[i], this->Buffer.size() - 1);
        }
    }

    std::ostream &operator<<(std::ostream &os, const TasksStreamBuffer &buffer)
    {
        for (int i = 0; i < buffer.Buffer.size(); i++)
        {
            for (int j = 0; j < buffer.Buffer[i].size(); j++)
            {
                os << buffer.Buffer[i][j];
            }
            os << std::endl;
        }
        return os;
    }

}
#endif
#endif