void quick_sort(int *nums, int left, int right)
{
  if (left == right)
    return;

  int i = left, j = right;
  int pivot = nums[(right - left) / 2 + left];

  while (i <= j)
  {
    while (nums[i] < pivot)
      i++;

    while (nums[j] > pivot)
      j--;

    if (i <= j)
    {
      int tmp = nums[i];
      nums[i] = nums[j];
      nums[j] = tmp;

      i++;
      j--;
    }
  }

  if (left < j)
    quick_sort(nums, left, j);

  if (i < right)
    quick_sort(nums, i, right);
}

int *majorityElement(int *nums, int numsSize, int *returnSize)
{
  if (numsSize == 1)
  {
    *returnSize = numsSize;
    return nums;
  }

  *returnSize = 0;
  int capacity = 128;
  int *result = malloc(capacity * sizeof(*result));

  quick_sort(nums, 0, numsSize - 1);

  int cnt = 0, curr = nums[0];
  int i = 0;

  while (i < numsSize)
  {
    if (nums[i] == curr)
    {

      // Increase count for this current number.
      cnt++;

      // If this number apprear more than n/3 times, add to result
      // and skip to next number.
      if (cnt > numsSize / 3)
      {
        if (*returnSize == capacity)
        {
          capacity *= 2;
          result = realloc(result, capacity * sizeof(*result));
        }

        result[(*returnSize)++] = curr;

        // Skips to the next number.
        while (i + 1 < numsSize && nums[i + 1] == curr)
          i++;
      }

      i++;
    }

    // Reset cnt and curr.
    else
    {
      curr = nums[i];
      cnt = 0;
    }
  }

  return result;
}
