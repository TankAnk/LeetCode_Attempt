#include <stdio.h>

int majorityElement(int *nums, int numsSize)
{
  int curr, cnt = 0;
  for (int i = 0; i < numsSize; i++)
  {
    if (cnt == 0)
      curr = nums[i];

    if (curr == nums[i])
      cnt++;

    else
      cnt--;
  }

  return curr;
}

int main()
{
  //int nums[] = {3,2,3};
  //int nums[] = {2,2,1,1,1,2,2};
  int nums[] = {1,3,0,3,3,8,3,7,7,3,3,3};

  printf("%d\n", majorityElement(nums, sizeof(nums) / sizeof(*nums)));

  return 0;
}
