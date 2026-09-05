#include <stdio.h>
#include <stdlib.h>

int **findMissingRanges(int *nums, int numsSize, int lower, int upper, int *returnSize)
{
  *returnSize = 0;
  int capacity = 64;
  int **result = malloc(capacity * sizeof(*result));
  int curr = lower, idx = 0;

  while (idx < numsSize && curr <= upper)
  {
    if (nums[idx] == curr)
    {
      idx++;
      curr++;
    }

    else if (nums[idx] > curr)
    {
      if (*returnSize == capacity)
      {
        capacity *= 2;
        result = realloc(result, capacity * sizeof(*result));
      }

      result[*returnSize] = malloc(2 * sizeof(**result));
      result[*returnSize][0] = curr;
      result[*returnSize][1] = nums[idx] - 1;

      (*returnSize)++;
      curr = nums[idx];
    }
  }

  if (curr <= upper)
  {
    if (*returnSize == capacity)
    {
      capacity *= 2;
      result = realloc(result, capacity * sizeof(*result));
    }

    result[*returnSize] = malloc(2 * sizeof(**result));
    result[*returnSize][0] = curr;
    result[*returnSize][1] = upper;

    (*returnSize)++;
  }

  return result;
}

int main()
{
  int returnSize;
  /*int lower = 0, upper = 99;
    int nums[] = {0,1,3,50,75};*/

  /*int lower = 1, upper = 5;
    int nums[] = {1,2,3,4,5};*/

  /*int lower = 1, upper = 5;
    int nums[] = {3,4,5};*/

  /*int lower = 1, upper = 5;
    int nums[] = {1,2,3};*/

  /*int lower = 1, upper = 6;
    int nums[] = {1,2,5,6};*/

  /*int lower = -7, upper = 6;
    int nums[] = {-5,-2,0,4};*/

  /*int lower = -1, upper = -1;
    int nums[] = {-1};*/

  /*int lower = 1, upper = 10;
    int *nums = NULL;
    Use numsSize = 0
  */

  int **result = findMissingRanges(nums, sizeof(nums) / sizeof(*nums), lower, upper, &returnSize);
  for (int i = 0; i < returnSize; i++)
    printf("[%d,%d]\n", result[i][0], result[i][1]);
}
