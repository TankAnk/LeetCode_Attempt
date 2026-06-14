int removeDuplicates(int* nums, int numsSize)
{
  if (numsSize <= 2)
    return numsSize;

  int left = 0, right = 1, insert_idx = 0;
  while (left < numsSize && right < numsSize && insert_idx < numsSize)
  {
    while (right < numsSize && nums[left] == nums[right])
      right++;

    if (right - left >= 3)
    {
      int tmp = nums[left], i;
      for (i = 0; i < 2 && insert_idx < numsSize && left < numsSize && tmp == nums[left]; i++)
        nums[insert_idx++] = nums[left++];
    }

    else
    {
      for (int i = 0; insert_idx < numsSize && i < right - left; i++)
        nums[insert_idx++] = nums[left];
    }

    left = right;
  }

  return insert_idx;
}
