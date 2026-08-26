int findMin(int *nums, int numsSize)
{
  int left = 0, right = numsSize - 1;
  while (left < right)
  {
    int mid = (right - left) / 2 + left;
    //[mid, right] is ascending -> min is either mid of on the left side
    if (nums[mid] < nums[right])
      right = mid;

    //Cross the rotation point & mid cannot be min -> min is in the right side
    else
      left = mid + 1;
  }

  return nums[right];
}
