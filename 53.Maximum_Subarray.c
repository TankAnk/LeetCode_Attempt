#include <stdio.h>
#include <stdlib.h>

int maxSubArray(int* nums, int numsSize) {
  if (numsSize == 1)
    return nums[0];
  
  int result = nums[0], max_end = nums[0];

  for (int i = 1; i < numsSize; i++)
  {
    if (max_end > 0)
      max_end += nums[i];
    else
      max_end = nums[i];

    if (result < max_end)
      result = max_end;
  }
  
  return result;
}

int main()
{
  int nums[] = {-2,1,-3,4,-1,2,1,-5,4};
  //int nums[] = {5,4,-1,7,8};
  //int nums[] = {-8, -3, -6, -2, -5, -4};
  //int nums[] = {7};
  //int nums[] = {5, 4, -100, 6, -2, 7};
  //int nums[] = {0,0,0,0};
  int numsSize = sizeof(nums) / sizeof(*nums);
  printf("%d\n", maxSubArray(nums, numsSize));
  return 0;
}
