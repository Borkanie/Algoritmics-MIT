#include <iostream>
#define number_of_elements_in_sub_array 5
using namespace std;

// Return the value of the median in a given array by a double iteration.
// Using the first iteration it calculates the absolute median of the array and in the next iteration finds the closest value.
int getMedianOfList(int *list, const int startingIndex, const int finalIndex)
{
    int median = list[startingIndex];
    for (int i = startingIndex + 1; i < finalIndex; i++)
    {
        median += list[i];
    }
    median = median / (finalIndex - startingIndex);
    int medianIndex = 0;
    for (int i = startingIndex + 1; i < finalIndex; i++)
    {
        if (abs(list[i] - median) < abs(list[medianIndex] - median))
        {
            medianIndex = i;
        }
    }
    return list[medianIndex];
}

/* This method will return the median of the medians with a O(2*n) complexity for any number of elements in subarray as defined in the macro in the same file.
It expects the target array as an argument and it will return the value of the median.
@param array represent the array that will be execute on.
*/
int medianOfMedians(int *array, int number_of_elements_in_array)
{
    // Split in subarrays of n is done by simply using the indexes.
    // Initialize an empty array to store medians.
    if (number_of_elements_in_array < number_of_elements_in_sub_array)
    {
        return getMedianOfList(array, 0, number_of_elements_in_array);
    }
    else
    {
        int *M = (int *)malloc(number_of_elements_in_array / number_of_elements_in_sub_array*sizeof(int));
        int index = 0;
        for (int i = 0; i < number_of_elements_in_array; i += number_of_elements_in_sub_array)
        {
            if (i + number_of_elements_in_sub_array <= number_of_elements_in_array)
            {
                *(M + index) = getMedianOfList(array, i, i + number_of_elements_in_sub_array);
            }
            else
            {
                *(M + index) = getMedianOfList(array, i, number_of_elements_in_array);
            }
            index++;
        }
        int result= medianOfMedians(M, index);
        free(M);
        return result;
    }
}

int main(int arg, char **args)
{
    int list[100];
    for(int i=0;i<100;i++){
        list[i]=i;
    }
    cout << "Median of medians: " << medianOfMedians(list, sizeof(list) / sizeof(int)) << endl;
    char a;
    cin >> a;
    return 0;
}