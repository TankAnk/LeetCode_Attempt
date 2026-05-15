#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool canJump(int* nums, int numsSize) {
  if (numsSize == 1)
    return true;
  if (numsSize == 2)
    return (nums[0] > 0);
  
  int max_end = 0, bound = 0;
  for (int i = 0; i < numsSize - 1; i++)
  {
    if (max_end < i + nums[i])
      max_end = i + nums[i];

    if (max_end >= numsSize - 1)
      return true;

    if (i == bound)
    {
      if (max_end <= bound)
        return 0;

      bound = max_end;
    }
  }
  
  return true;
}

int main()
{
  int nums[] = {2, 3, 1, 1, 4};
  int numsSize = sizeof(nums) / sizeof(*nums);
  printf("%d\n", canJump(nums, numsSize));
  return 0;
}
