#include <vector>

namespace Task
{
    enum TaskType
    {
        Relaxation=1,
        Work=2,
        Enjoyment=3,
        Sleep=4,
        Eating=5,
        Learning=6,
        Research=7,
        Side_Projects=8,
        Side_Hustle=9,
    };
    class Task
    {
    private: 
        std::vector<Task> prerequisites;
    public:
        Task();
        Task(std::vector<Task> prerequisites){
            this->prerequisites = prerequisites;
        };
        int StartingTime;
        int EndingTime;
        int Duration();
        int Cost();
        TaskType TaskType;
        Task* Children;
    };
}