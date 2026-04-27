#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void nextPermutation(int* nums, int numsSize) {
  if (numsSize == 1)
    return;

  int k = -1, l = -1;
  //Find the largest index k such that a[k] < a[k + 1]
  for (int i = numsSize - 1; (i >= 1) && (k == -1); i--)    
    if (nums[i] > nums[i - 1])
      k = i - 1;
  
  //If no k exists, the permutation is the last --> reverse
  if (k == -1)
  {
    for (int i = 0; i < numsSize / 2; i++)
      swap(&nums[i], &nums[numsSize - i - 1]);
    
    return;
  }

  //Find the largest index l greater than k such that a[k] < a[l]
  else
  {
    for (int j = numsSize - 1; (j > k) && (l == -1); j--)
      if (nums[j] > nums[k])
	l = j;
    
    //Swap a[k] with a[l]
    swap(&nums[k], &nums[l]);

    //Reverse the sequence from a[k + 1] to the end
    for (int offset = k + 1, i = 0, len = numsSize - k - 1; i < len / 2; i++)
      swap(&nums[i + offset], &nums[len - i - 1 + offset]);  
  }
}

int main()
{
  int nums[] = {1, 3, 5, 4, 2};
  int size = sizeof(nums)/sizeof(*nums);
  nextPermutation(nums, size);
  for (int i = 0; i < size; i++)
    printf("%d ", nums[i]);
  printf("\n");
  return 0;
}
