#include "Task.hpp"
#include "vector"

namespace Task
{
    double Task::Density() const
    {
        return ((double)this->value) / ((double)this->duration);
    }

    int Task::TotalTime() const
    {
        int value = 0;
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
        int duration = this->duration / 1000;
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