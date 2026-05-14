#include <stdio.h>
#include <stdlib.h>

int jump(int* nums, int numsSize) {
  if (numsSize <= 1) return 0;
  if (nums[0] >= numsSize - 1) return 1;

  int count = 0, max_jmp = 0, bound = 0;
  for (int i = 0; i < numsSize - 1; i++)
  {
    if (max_jmp < i + nums[i])
      max_jmp = i + nums[i];

    if (i == bound)
    {
      count++;
      bound = max_jmp;
    }
  }

  return count;
}

int main()
{
  int nums[] = {1,1,2,1,1};
  int numsSize = sizeof(nums) / sizeof(*nums);
  printf("%d\n", jump(nums, numsSize));
  
  return 0;
}
