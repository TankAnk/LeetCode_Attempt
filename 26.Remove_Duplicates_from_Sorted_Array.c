#include <stdio.h>
#include <stdlib.h>

int removeDuplicates(int* nums, int numsSize) {
  if (numsSize <= 1)
    return numsSize;

  int i = 0;
  for (int j = 1; j < numsSize; j++)
    if (nums[i] != nums[j])
      nums[++i] = nums[j];

  return i + 1;
}

int main()
{
  //int nums[] = {1, 1, 2, 3};
  int nums[] = {1, 1};
  int size = sizeof(nums)/sizeof(*nums);
  int k = removeDuplicates(nums, size);
  printf("%d\n", k);
  printf("[");
  for (int i = 0; i < size; i++)
  {
    printf("%d ", nums[i]);
  }
  printf("]\n");
  return 0;
}
