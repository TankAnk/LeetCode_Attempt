void quick_sort(int *arr, int left, int right)
{
  int i = left;
  int j = right;
  int pivot = arr[(right - left) / 2 + left];

  while (i <= j)
  {
    while (arr[i] < pivot)
      i++;

    while (arr[j] > pivot)
      j--;

    if (i <= j)
    {
      int tmp = arr[i];
      arr[i] = arr[j];
      arr[j] = tmp;

      i++;
      j--;
    }
  }

  if (left < j)
    quick_sort(arr, left, j);

  if (i < right)
    quick_sort(arr, i, right);
}

bool containsDuplicate(int *nums, int numsSize)
{
  quick_sort(nums, 0, numsSize - 1);

  for (int i = 0; i < numsSize - 1; i++)
    if (nums[i] == nums[i + 1])
      return true;

  return false;
}
