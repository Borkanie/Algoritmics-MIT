#include <iostream>
#include <vector>
#include ".././Task/Task.hpp"
#include "../daily.cpp"

// This is a algoritm aimed to maximy the daily outpouf of a random person.
using namespace std;

void testDaily(){
    for(int i=1;i<100;i=i+3){
        cout<<"iteration: "+to_string(i)<<endl;
        auto tasks = daily::GetRandomTasks(i);
        for(int j=1;j<tasks.size();j++){
            if(tasks[j-1].startingTime>tasks[j].startingTime){
                throw invalid_argument("Order is faulty");
            }
        }
    }
}

