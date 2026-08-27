int findMin(int *nums, int numsSize)
{
  int left = 0, right = numsSize - 1;

  while (left < right)
  {
    int mid = (right - left) / 2 + left;

    //[mid, right] ascending -> Min is in [left, right]
    if (nums[mid] < nums[right])
      right = mid;

    //Cross the roation point, mid cannot be min -> Min is in (mid, right]
    else if (nums[mid] > nums[right])
      left = mid + 1;

    else
    {
      /*
      //Reasonable, but unnecessary
      if (nums[left] < nums[right])
        right = mid;

      //Not enough information. Counter examples:
        4, 1, 3, 3, 3 -> Min on left
        8, 9, 6, 6, 6 -> Min on right
      else if (nums[left] > nums[right])
        left = mid;
      */

      //nums[right] is not unique -> do not loose any value when discard
        right--;
    }
  }

  return nums[right];
}
