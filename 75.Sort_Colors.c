#include <stdio.h>
#include <stdlib.h>

void heapify(int *arr, int size, int idx)
{
  int max = idx, left = 2 * idx + 1, right = 2 * idx + 2;
  if (left < size && arr[left] > arr[max])
    max = left;
  if (right < size && arr[right] > arr[max])
    max = right;
  if (max != idx)
  {
    int tmp = arr[idx];
    arr[idx] = arr[max];
    arr[max] = tmp;

    heapify(arr, size, max);
  }
}


void heap_sort(int *arr, int size)
{
  for (int i = size / 2 - 1; i >= 0; i--)
    heapify(arr, size, i);
  for (int i = size - 1; i > 0; i--)
  {
    int tmp = arr[0];
    arr[0] = arr[i];
    arr[i] = tmp;

    heapify(arr, i, 0);
  }
}

void sortColors(int* nums, int numsSize)
{
  heap_sort(nums, numsSize);
}

int main()
{
  int nums[] = {2,0,2,1,1,0};
  int numsSize = sizeof(nums) / sizeof(*nums);
  sortColors(nums, numsSize);
  printf("[ ");
  for (int i = 0; i < numsSize; i++)
    printf("%d ", nums[i]);
  printf("]\n");
  return 0;
}
