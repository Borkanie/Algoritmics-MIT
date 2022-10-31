# MIT algortimics

## Median of medians algoritm

### Scope

It's scope is to find the smallest elemnt in a given array of elements.

Given an array A = [1,...,n] of n numbers and an index i, where 1 ≤ i ≤ n, find the $i^{th}$ the smallest element of A. It can find the smallest element in O(n) time.

> This algoritm assumes all elements are unique but it can be generalized for duplicated elements.

Steps:

```
1.  Divide the list into sublist of five elements( it's fine if fewer remain in a list).
2.  Sort each sublist and determine the median. Sorting small lists takes linear time(We need to see where this assumption fails). 
3.  Split the list in half and put all elements smaller than the median element on the left and all elements bigger on the right. we do not need to order them.
4.  Use the median-of-median algorithm to recursively determine the median of the set of all the medians.
5.  Use this median as the pivot element, x. The pivot is an approximate median of the whole list and then each recursive step hones in on the true median.
6. Reorder A such that all elements lass than x are to the left of x and all elements greater than x are to the right of x. This is called PARTITIONING. The elements are in no particular order.
```


