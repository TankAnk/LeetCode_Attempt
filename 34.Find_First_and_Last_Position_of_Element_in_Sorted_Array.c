#include <stdio.h>
#include <stdlib.h>

int binary_search(int* nums, int left, int right, int target)
{
  while (left <= right)
  {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target)
      return mid;
    else if (nums[mid] < target)
      left = mid + 1;
    else
      right = mid - 1;
  }
  
  return -1;
}

int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
  *returnSize = 2;
  int *result = malloc(*returnSize * sizeof(*result));
  result[0] = result[1] = -1;
  if (numsSize == 0)
    return result;

  int idx = binary_search(nums, 0, numsSize - 1, target);
  result[0] = result[1] = idx;
  if (idx != -1)
  {
    int left_bound = idx - 1, right_bound = idx + 1;
    while (left_bound >= 0)
    {
      left_bound = binary_search(nums, 0, left_bound, target);
      if (left_bound != -1 && left_bound < result[0])
	result[0] = left_bound--;
    }

    while (right_bound < numsSize && right_bound != -1)
    {
      right_bound = binary_search(nums, right_bound, numsSize - 1, target);
      if (right_bound != -1 && right_bound > result[1])
	result[1] = right_bound++;
    }
  }  

  return result;
}

int main()
{
  int nums[] = {5,7,7,8,8,10};
  int numsSize = sizeof(nums) / sizeof(*nums);  
  int target = 8, returnSize;
  printf("%d\n", binary_search(nums, 0, numsSize - 1, target));
  int *result = searchRange(nums, numsSize, target, &returnSize);
  for (int i = 0; i < returnSize; i++)
    printf("%d ", result[i]);
  free(result);
  return 0;
}
