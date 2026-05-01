#include <stdio.h>

int searchInsert(int* nums, int numsSize, int target) {
  int left = 0, right =  numsSize - 1, mid;
  while (left <= right)
  {
    mid = left + (right - left) / 2;
    if (nums[mid] == target)
      return mid;
    else if (nums[mid] < target)
      left = mid + 1;
    else
      right = mid - 1;
  }
  
  printf("left: %d, right: %d, mid: %d\n", left, right, mid);

  //return (nums[mid] > target) ? mid : (mid + 1);
  return left;
}

int main()
{
  int nums[] = {-10, -3, 0, 4, 8, 12};
  int numsSize = sizeof(nums) / sizeof(*nums);
  int target = 5;
  printf("%d\n", searchInsert(nums, numsSize, target));

  return 0;
}
