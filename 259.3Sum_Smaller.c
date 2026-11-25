/*
Given an array of n integers nums and an integer target, find the number of index triplets i, j, k such that:
- 0 <= i < j < k < n AND
- nums[i] + nums[j] + nums[k] < target
Return the number of triplets that satisfy the above conditions.

Example 1:
Input: nums = [-2, 0, 1, 3], target = 2
Output: 2
Explanation:
There are two triplets whose sum is less than 2:
[-2, 0, 1]
[-2, 0, 3]

Example 2:
Input: nums = [], target = 0
Output: 0

Example 3:
Input: nums = [0], target = 0
Output: 0

Constraints:
- n == nums.length
- 0 <= n <= 350
- -100 <= nums[i] <= 100
- -100 <= target <= 100
*/
#include <stdio.h>
#include <stdlib.h>

#define MIN_VAL -100
#define MAX_VAL 100
#define MAX_VAL_SIZE 201

int threeSumSmaller(int *nums, int numsSize, int target)
{
  if (numsSize < 3)
    return 0;

  // smaller[i] = Total count of numbers that are strictly smaller than (i - 100).
  // Normalize a number for X to the index by X + 100.
  int smaller[MAX_VAL_SIZE] = {0};

  // When encounter X, the total numbers smaller than X+1, X+2,.. increase by 1.
  // [0,5]. Encounter 3 -> The total numbers smaller than 4 and smaller than 5 increase by 1.
  for (int i = 0; i < numsSize; i++)
    for (int idx = nums[i] + MAX_VAL + 1; idx < MAX_VAL_SIZE; idx++)
      smaller[idx]++;

  int result = 0;
  for (int i = 0; i < numsSize - 1; i++)
  {
    for (int j = i + 1; j < numsSize; j++)
    {
      // Finds the total numbers of values that strictly smaller than complement.
      int complement = target - nums[i] - nums[j];

      // If the complement < the smallest value, no number in the array satisfy.
      if (complement < MIN_VAL)
        continue;

      // If the complement > the largest value, all numbers in the array satisfy.
      // Exclude nums[i] and nums[j].
      if (complement > MAX_VAL)
      {
        result += (numsSize - 2);
        continue;
      }

      int com_idx = complement + MAX_VAL;

      // How many numbers smaller than complement.
      result += smaller[com_idx];

      // If nums[i] is smaller than complement, it was counted into result.
      // Remove it.
      if (nums[i] < complement)
        result--;

      // If nums[j] is smaller than complement, it was counted into result.
      // Remove it.
      if (nums[j] < complement)
        result--;
    }
  }

  /*
    - A valid set of 3 indices will be counted 3 times.
    Ex: (0, 1, 2)
    At i = 0, j = 1 -> k = 2
    At i = 0, j = 2 -> k = 1
    At i = 1, j = 2 -> k = 0
  */
  return result / 3;
}
