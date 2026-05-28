#include <stdio.h>
#include <stdlib.h>

int factorial(int n)
{
  int result = 1;
  for (int i = 2; i <= n; i++)
    result *= i;
  return result;
}

void del_arr(int **arr, int *size, int pos)
{
  for (int i = pos; i < *size - 1; i++)
    (*arr)[i] = (*arr)[i + 1];
  (*size)--;
}

char* getPermutation(int n, int k) {
  char *result = malloc((n + 1) * sizeof(*result));
  result[n] = '\0';
  int *nums = malloc(n * sizeof(*nums));
  for (int i = 0; i < n; i++)
    nums[i] = i + 1;
  k--;
  int nums_size = n, res_idx = 0, block_size, nums_idx;
  while (res_idx < n && size > 0)
  {
    block_size = factorial(nums_size - 1);
    nums_idx = k / block_size;
    result[res_idx++] = nums[nums_idx] + '0';

    k %= block_size;
    del_arr(&nums, &nums_size, nums_idx);
  }

  free(nums);
  return result;
}

/*
[1, 2, 3, 4]
1234 1243 1324 1342 1423 1432
2134 2143 2314 2341 2413 2431
3124 3142 3214 3241 3412 3421
4123 4132 4213 4231 4312 4321
*/

int main()
{
  int n = 4, k = 9;
  char *s = getPermutation(n, k);
  printf("%s\n", s);
  free(s);

  return 0;
}
