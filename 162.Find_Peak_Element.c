int findPeakElement(int *nums, int numsSize)
{
  if (numsSize == 1 || nums[0] > nums[1])
    return 0;

  if (nums[numsSize - 1] > nums[numsSize -2])
    return numsSize - 1;

  int left = 1, right = numsSize - 2, result = -1;
  while (left <= right && result == -1)
  {
    int mid = (right - left) / 2 + left;

    //Peak
    if (nums[mid - 1] < nums[mid] && nums[mid] > nums[mid + 1])
      result = mid;

    //Valley -> go to the side with the larger number
    else if (nums[mid - 1] > nums[mid] && nums[mid] < nums[mid + 1])
    {
      if (nums[mid - 1] > nums[mid + 1])
        right = mid - 1;

      else
        left = mid + 1;
    }

    //Uphill -> keep going up to find peak
    else if (nums[mid - 1] < nums[mid] && nums[mid] < nums[mid + 1])
      left = mid + 1;

    //Downhill -> go back to find peak
    else if (nums[mid - 1] > nums[mid] && nums[mid] > nums[mid + 1])
      right = mid - 1;
  }

  return result;
}
