#include <stdio.h>
#include <stdlib.h>

int firstMissingPositive(int* nums, int numsSize) {
  for (int i = 0; i < numsSize; i++)
    if (nums[i] <= 0 || nums[i] > numsSize)
      nums[i] = numsSize + 1;

  for (int i = 0; i < numsSize; i++)
  {
    int x = abs(nums[i]);
    if (x > 0 && x <= numsSize)
      nums[x - 1] = -abs(nums[x - 1]);
  }

  for (int i = 0; i < numsSize; i++)
    if (nums[i] > 0)
      return i + 1;  

  return numsSize + 1;
}

int main()
{
  int nums[] = {1, 2, 2};
  int numsSize = sizeof(nums) / sizeof(*nums);
  printf("%d\n", firstMissingPositive(nums, numsSize));
  return 0;
}
