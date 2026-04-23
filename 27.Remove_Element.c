int removeElement(int* nums, int numsSize, int val) {
  if (numsSize == 0)
    return numsSize;

  int count = numsSize;
  int left = 0, right = numsSize - 1;
  do
  {
    while (left < numsSize && nums[left] != val)
    {
      left++;
    }

    while (right >= 0 && nums[right] == val)
    {
      right--;
      count--;
    }
    
    if (left < right)
    {
      nums[left]+=nums[right];
      nums[right] = nums[left] - nums[right];
      nums[left]-=nums[right];
    }
  } while (left < right);
  return count;
}
