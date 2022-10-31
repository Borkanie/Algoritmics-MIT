#include <iostream>
#define number_of_elements_in_sub_array 5
using namespace std;

// Standard partition process of QuickSort().
// It considers the last element as pivot
// and moves all smaller element to left of
// it and greater elements to right
int partition(int arr[], int l, int r)
{
    int x = arr[r], i = l;
    for (int j = l; j <= r - 1; j++)
    {
        if (arr[j] <= x)
        {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[r]);
    return i;
}

// This function returns k'th smallest
// element in arr[l..r] using QuickSort
// based method.  ASSUMPTION: ALL ELEMENTS
// IN ARR[] ARE DISTINCT
int kthSmallest(int arr[], int l, int r, int k)
{
    // If k is smaller than number of
    // elements in array
    if (k > 0 && k <= r - l + 1)
    {

        // Partition the array around last
        // element and get position of pivot
        // element in sorted array
        int index = partition(arr, l, r);

        // If position is same as k
        if (index - l == k - 1)
            return arr[index];

        // If position is more, recur
        // for left subarray
        if (index - l > k - 1)
            return kthSmallest(arr, l, index - 1, k);

        // Else recur for right subarray
        return kthSmallest(arr, index + 1, r,
                           k - index + l - 1);
    }

    // If k is more than number of
    // elements in array
    return INT_MAX;
}

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
int medianOfMedians(int* array,int number_of_elements_in_array)
{
    // split in subarrays of n is done by simply using the idnexes
    // Initialize an empty array to store medians
    int *M = (int *)malloc(sizeof(array) / number_of_elements_in_sub_array);
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
    return kthSmallest(M, 0, index - 1, index / 2);
}

int main(int arg, char **args)
{
    int list[] = {1, 2, 3, 4, 5, 6,7,8,9,10,11,12,13,14,15,16,17,17};
    cout << "Median of medians: " << medianOfMedians(list,sizeof(list)/sizeof(int)) << endl;
    char a;
    cin >> a;
    return 0;
}