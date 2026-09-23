/*1 2 3 4 5 6 7 8 9
k = 3 --> 1 2 3 4 5 6 | 7 8 9
Reverse both partitions: 6 5 4 3 2 1 | 9 8 7
Reverse the whole array: 7 8 9 1 2 3 4 5 6
*/

void rotate(int *nums, int numsSize, int k)
{
  k %= numsSize;

  if (k == 0)
    return;

  // Reverse left parition
  for (int i = 0, left_size = numsSize - k; i < left_size / 2; i++)
  {
    int tmp = nums[i];
    nums[i] = nums[left_size - 1 - i];
    nums[left_size - 1 - i] = tmp;
  }

  // Reverse right partition
  for (int i = 0, right_size = k; i < k / 2; i++)
  {
    int tmp = nums[numsSize - k + i];
    nums[numsSize - k + i] = nums[numsSize - 1 - i];
    nums[numsSize - 1 - i] = tmp;
  }

  // Reverse the whole array
  for (int i = 0; i < numsSize / 2; i++)
  {
    int tmp = nums[i];
    nums[i] = nums[numsSize - 1 - i];
    nums[numsSize - 1 - i] = tmp;
  }
}
