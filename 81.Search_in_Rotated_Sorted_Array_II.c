bool search(int* nums, int numsSize, int target)
{
  if (numsSize == 1)
    return nums[0] == target;

  int left = 0, right = numsSize - 1, mid;
  while (left <= right)
  {
    mid = left + (right - left) / 2;
    if (nums[left] == target || nums[mid] == target || nums[right] == target)
      return true;

    if (nums[left] == nums[mid])
      left++;

    else if (nums[right] == nums[mid])
      right--;

    else if (nums[left] < nums[mid])
    {
      if (nums[left] < target && target < nums[mid])
        right = mid - 1;
      else
        left = mid + 1;
    }

    else
    {
      if (nums[mid] < target && target < nums[right])
        left = mid + 1;
      else
        right = mid - 1;
    }
  }

  return false;
}
/*
Target = 1
2 5 6 0 0 1 2
Target = 3
2 5 6 7 7 1 2
Target = 0
1 0 1 1 1
Target = 2
1 1 1 1 1 2 1
*/
