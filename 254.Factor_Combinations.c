/*
- Numbers can be regarded as the product of their factors.
For example, 8 = 2 x 2 x 2 = 2 x 4.
- Given an integer n, return all possible combinations of its factors, excluding 1 and n itself.
- You may return the answer in any order.

Example 1:
Input: n = 12
Output: [[2,6],[3,4],[2,2,3]]
Explanation: 12 = 2 x 6 = 3 x 4 = 2 x 2 x 3.

Example 2:
Input: n = 37
Output: []
Explanation: 37 is a prime number.

Example 3:
Input: n = 24
Output: [
[2,2,2,3],
[4,2,3],[6,2,2],
[4,6],
[8,3],[2,12]
]

Pairs of factors w/ lower bound:
Start w/ >= 2: [2,12]
Start w/ >= 2: [2,2,6],[2,3,4]
[2,2,6]
Constraints: 1 <= n <= 10^9
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRIME_FACTORS 30

void solve(int n, int ***result, int *returnSize, int **returnColumnSizes, int *capacity, int remaining, int start, int *tmp, int tmp_idx)
{
  for (int i = start; i <= remaining / i; i++)
  {
    if (remaining % i == 0)
    {
      tmp[tmp_idx] = i;
      solve(n, result, returnSize, returnColumnSizes, capacity, remaining / i, i, tmp, tmp_idx + 1);
    }
  }

  if (1 < remaining && remaining < n)
  {
    tmp[tmp_idx] = remaining;

    if (*capacity == *returnSize)
    {
      *capacity *= 2;
      *result = realloc(*result, *capacity * sizeof(**result));
      *returnColumnSizes = realloc(*returnColumnSizes, *capacity * sizeof(**returnColumnSizes));
    }

    (*returnColumnSizes)[*returnSize] = tmp_idx + 1;
    (*result)[*returnSize] = malloc((tmp_idx + 1) * sizeof(***result));
    memcpy((*result)[*returnSize], tmp, (tmp_idx + 1) * sizeof(***result));
    (*returnSize)++;
  }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned in *returnColumnSizes.
 * Note: Both returned array and *returnColumnSizes must be malloced,
 * and caller will free them.
 */
int **getFactors(int n, int *returnSize, int **returnColumnSizes)
{
  *returnSize = 0;
  if (n <= 2)
    return NULL;

  int capacity = 32;
  int **result = malloc(capacity * sizeof(*result));
  *returnColumnSizes = malloc(capacity * sizeof(**returnColumnSizes));
  int tmp[MAX_PRIME_FACTORS];
  int tmp_idx = 0;

  solve(n, &result, returnSize, returnColumnSizes, &capacity, n, 2, tmp, tmp_idx);

  return result;
}

int main(void)
{
    int n;

    printf("Enter a positive integer: ");
    fflush(stdout);

    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid input.\n");
        return 1;
    }

    int returnSize = 0;
    int *returnColumnSizes = NULL;

    int **result = getFactors(n, &returnSize, &returnColumnSizes);

    printf("\nFactor combinations of %d:\n", n);
    printf("[\n");

    for (int i = 0; i < returnSize; i++)
    {
        printf("  [");

        for (int j = 0; j < returnColumnSizes[i]; j++)
        {
            printf("%d", result[i][j]);

            if (j < returnColumnSizes[i] - 1)
                printf(", ");
        }

        printf("]");

        if (i < returnSize - 1)
            printf(",");

        printf("\n");
    }

    printf("]\n");

    // Free allocated memory
    for (int i = 0; i < returnSize; i++)
        free(result[i]);

    free(result);
    free(returnColumnSizes);

    return 0;
}
