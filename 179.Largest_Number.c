#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int no_of_digits(int n)
{
  int cnt = 0;

  do
  {
    cnt++;
    n /= 10;

  } while (n > 0);

  return cnt;
}

int compare(int n1, int n2)
{
  char s1[12];
  char s2[12];

  sprintf(s1, "%d", n1);
  sprintf(s2, "%d", n2);

  int len1 = strlen(s1);
  int len2 = strlen(s2);

  for (int i = 0; i < len1 + len2; i++)
  {
    char c1;
    char c2;

    if (i < len1)
      c1 = s1[i];
    else
      c1 = s2[i - len1];

    if (i < len2)
      c2 = s2[i];
    else
      c2 = s1[i - len2];

    if (c1 > c2)
      return 1;

    if (c1 < c2)
      return -1;
  }

  return 0;
}

void custom_merge(int *arr, int left, int mid, int right)
{
  int left_size = mid - left + 1;
  int right_size = right - mid;

  int left_sub[left_size];
  int right_sub[right_size];

  for (int i = 0; i < left_size; i++)
    left_sub[i] = arr[left + i];

  for (int i = 0; i < right_size; i++)
    right_sub[i] = arr[mid + 1 + i];

  int i = 0;
  int j = 0;
  int k = left;

  while (i < left_size && j < right_size)
  {
    /*
     * Put the number with the larger concatenation first.
     */
    if (compare(left_sub[i], right_sub[j]) >= 0)
      arr[k++] = left_sub[i++];

    else
      arr[k++] = right_sub[j++];
  }

  while (i < left_size)
    arr[k++] = left_sub[i++];

  while (j < right_size)
    arr[k++] = right_sub[j++];
}

void custom_merge_sort(int *arr, int left, int right)
{
  if (left < right)
  {
    int mid = left + (right - left) / 2;

    custom_merge_sort(arr, left, mid);
    custom_merge_sort(arr, mid + 1, right);

    custom_merge(arr, left, mid, right);
  }
}

char *largestNumber(int *nums, int numsSize)
{
  custom_merge_sort(nums, 0, numsSize - 1);

  /*
   * If the largest number is 0, every number must be 0.
   */
  if (nums[0] == 0)
  {
    char *result = malloc(2 * sizeof(char));

    if (result == NULL)
      return NULL;

    result[0] = '0';
    result[1] = '\0';

    return result;
  }

  int total_digits = 0;

  for (int i = 0; i < numsSize; i++)
    total_digits += no_of_digits(nums[i]);

  char *result = malloc((total_digits + 1) * sizeof(char));

  if (result == NULL)
    return NULL;

  result[total_digits] = '\0';

  int res_idx = 0;

  for (int i = 0; i < numsSize; i++)
  {
    int tmp = nums[i];

    int digits = no_of_digits(tmp);
    int divisor = 1;

    for (int j = 1; j < digits; j++)
      divisor *= 10;

    while (divisor > 0)
    {
      result[res_idx++] = (tmp / divisor) % 10 + '0';
      divisor /= 10;
    }
  }

  return result;
}

int main()
{
  int nums[] = {3, 30, 34, 5, 9};
  int numsSize = sizeof(nums) / sizeof(*nums);

  char *result = largestNumber(nums, numsSize);

  if (result != NULL)
  {
    printf("%s\n", result);
    free(result);
  }

  return 0;
}
