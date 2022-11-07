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
    // C++98 guarantees that '0', '1', ... '9' are consecutive.
    // It only guarantees that 'a' ... 'f' and 'A' ... 'F' are
    // in increasing order, but the only two alternative encodings
    // of the basic source character set that are still used by
    // anyone today (ASCII and EBCDIC) make them consecutive.
    unsigned char randomSign(unsigned char c)
    {
        switch(c & 0b00001111){
            case 0b00000000:
                return '0';
            case 0b00000001:
                return '1';
            case 0b00000010:
                return '2';
            case 0b00000011:
                return '3';
            case 0b00000100:
                return '4';
            case 0b00000101:
                return '5';
            case 0b00000110:
                return '6';
            case 0b00000111:
                return '7';
            case 0b00001000:
                return '8';
            case 0b00001001:
                return '9';
            case 0b00001010:
                return 'A';
            case 0b00001011:
                return 'B';
            case 0b00001100:
                return 'C';
            case 0b00001101:
                return 'D';
            case 0b00001110:
                return 'E';
            case 0b00001111:
                return 'F';
            default:
                return '+';
        }
    }

    long CTimeSpan(int days, int hours,int minutes,int seconds){
        return (long)seconds*1000+(long)minutes*1000*60+(long)hours*1000*60*60+(long)days*1000*60*60*24;
    }

    Task::TaskType GetEnumerationById(int id)
    {
        return static_cast<Task::TaskType>(id);
    }

    vector<Task::Task> GetRandomTasks(int numberOfTasks, bool print = true)
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
            task.startingTime = time(0) + CTimeSpan(0, rand() %23, rand() %59, 0);
            task.duration = CTimeSpan(0, 0, rand() %59, 0);
            task.value = rand();
            int isChild = rand() % 3;
            if (isChild >= 1 && tasks.size() > 2)
            {
                int parentIndex=rand() % (tasks.size() - 1);
                tasks[parentIndex].Children.push_back(task);
                task.Sign=tasks[parentIndex].Sign;
                
            }else{
                uint8_t colorInt=0;
                while(colorInt==0){
                    colorInt = ((uint8_t)rand()%16);
                }
                task.Sign=std::to_string(i).c_str()[0];
            }
            tasks.push_back(task); 
        }

        if (print)
        {
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
    vector<Task::Task> tasks = daily::GetRandomTasks(20, false);
    // daily::testDaily();
    //  we sort them by starting date
    Task::QuickSortByStartingTime(tasks, 0, tasks.size() - 1);
    Task::DisplayTaskArray(tasks, 10);
    Person::RecursiveOptimalTaskByPoints(tasks,0);
    Task::DisplayTaskArray(Person::bestRow, 10);
    return 0;
}