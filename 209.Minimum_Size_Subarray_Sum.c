/*
- Traverse the array with left and right pointer
- At the start of every loop, check if we already added the current right to the sum:
  + If not, add
  + If already, do not add
- If the current sum is smaller than target, keep expanding to the right
- If the current sum is larger than or equal to target, we found the subarray:
  + Update the result if this subarray has smaller length than the minimim
  + If the current sum is strictly larger than the target, try to minimize the window by shrinking from the left
  + If the current sum strictly equals the target, keep expanding to the right
*/

int minSubArrayLen(int target, int *nums, int numsSize)
{
  int result = numsSize + 1;

  int left = 0, right = 0, prev_right = -1, curr_sum = 0;
  while (right < numsSize && left < numsSize)
  {
    if (prev_right < right)
      curr_sum += nums[right];

    if (curr_sum < target)
      prev_right = right++;

    else if (curr_sum >= target)
    {
      int len = right - left + 1;

      if (len == 1)
        return len;

      result = (len < result) ? len : result;

      if (curr_sum > target)
      {
        curr_sum -= nums[left++];
        prev_right++;
      }

      else
        prev_right = right++;
    }
  }

  return (result == numsSize + 1 ? 0 : result);
}
