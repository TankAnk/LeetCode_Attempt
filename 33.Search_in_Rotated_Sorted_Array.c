#include <stdio.h>

int search(int* nums, int numsSize, int target) {
  if (numsSize == 1)
    return (nums[0] == target) ? 0 : -1;

  int left = 0, right = numsSize - 1, mid;
  while (left <= right)
  {
    mid = left + (right - left) / 2;
    if (nums[mid] == target)
      return mid;

    if (nums[left] <= nums[mid])
    {
      if (nums[left] <= target && target < nums[mid])
	right = mid - 1;
      else
	left = mid + 1;
    }

    else
    {
      if (nums[mid] < target && target <= nums[right])
	left = mid + 1;
      else
	right = mid - 1;
    }
  }

  return -1;
}

int main()
{
  //int nums[] = {3};
  int nums[] = {3,4,5,6,1,2};
  int target = 2, size = sizeof(nums)/sizeof(*nums);
  printf("%d\n", search(nums, size, target));
  
  return 0;
}
