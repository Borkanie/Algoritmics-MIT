#include <vector>
#include "../Task/Task.hpp"
#include "Person.hpp"
namespace Person
{
    int totalPointsInRow(std::vector<Task::Task> row){
        int result=0;
        for(int i=0;i<row.size();i++){
            result+=row[i].value;
        }
        return result;
    }

    void RecursiveOptimalTaskByPoints(std::vector<Task::Task> tasks,int currentPoints){
        
        for(int i=0;i<tasks.size();i++){
            if(currentRoad.size()==0){
                currentRoad.push_back(tasks[0]);
                tasks.erase(tasks.begin()+0);
                continue;
            }
            Task::Task currentTask=tasks[i];
            tasks.erase(tasks.begin()+i);
            if(currentTask.DoesNotOverLapWithArray(currentRoad)){
                currentRoad.push_back(currentTask);
                RecursiveOptimalTaskByPoints(tasks,currentPoints);
                //tasks.insert(tasks.begin()+i,currentTask);
                currentRoad.pop_back();
            }
        }
        if(totalPointsInRow(currentRoad)>=totalPointsInRow(bestRow)){
            bestRow = currentRoad;
        }
    }

    std::vector<Task::Task> Person::GetOptimalTask(std::vector<Task::Task> possibleTasks)
    {
        std::vector<Task::Task> tasks;
        
        return tasks;
    };
    
    void Person::DisplayTasks(std::vector<Task::Task> tasks){

    }

}