/*
- Given an integer n, return all the strobogrammatic numbers that are of length n.
- A strobogrammatic number is a number that looks the same when rotated 180 degrees (upside down).
- The digits that remain valid after a 180-degree rotation are: 0 - 0, 1 - 1, 6 - 9, 8 - 8, 9 - 6.
- With a number with n digits, digit at index i after the roration land in index n - 1 - i.
- A number cannot end w/ 0 as leading 0 is not allowed.
- 1 <= n <= 14.

n = 1: 0, 1, 8
n = 2: 11, 69, 88, 96
n = 3:
-> 101, 111, 181
-> 609, 619, 689
-> 808, 818, 888
-> 906, 916, 986

- Inserting strobogrammatic digit and its counterpart from 2 ends.
- Handle the middle slot if n is odd.
- Handle leading and trailing 0 when n > 1.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE 10

void solve(int n, int *returnSize, char ***result, int **returnColumnSizes, int *capacity, int *map, char *tmp_buf, int left, int right)
{
  // If we finish building current number.
  if (left > right)
  {
    if (*returnSize == *capacity)
    {
      *capacity *= 2;
      *result = realloc(*result, *capacity * sizeof(**result));
      *returnColumnSizes = realloc(*returnColumnSizes, *capacity * sizeof(**returnColumnSizes));
    }

    (*returnColumnSizes)[*returnSize] = n;
    (*result)[*returnSize] = malloc((n + 1) * sizeof(***result));
    memcpy((*result)[*returnSize], tmp_buf, (n + 1) * sizeof(***result));
    (*returnSize)++;

    return;
  }

  // Insert the strobogrammtic digit and its counterpart into 2 ends.
  for (int i = 0; i < MAP_SIZE; i++)
  {
    /*
      Skip inserting the current number if either:
      - It's not a strobogrammatic digit.
      - It's the middle slot and it's either 6 or 9.
      - Insert 0 at the very first (and last) while n > 1.
    */
    if (map[i] == -1 ||
        (left == right && (i == 6 || i == 9)) ||
        (left == 0 && i == 0 && n > 1)
      )
      continue;

    tmp_buf[left] = i + '0';
    tmp_buf[right] = map[i];
    solve(n, returnSize, result, returnColumnSizes, capacity, map, tmp_buf, left + 1, right - 1);
  }
}

char **findStrobogrammatic(int n, int *returnSize, int **returnColumnSizes)
{
  *returnSize = 0;
  int capacity = 64;
  char **result = malloc(capacity * sizeof(*result));
  *returnColumnSizes = malloc(capacity * sizeof(**returnColumnSizes));

  int map[MAP_SIZE] = {'0', '1', -1, -1, -1, -1, '9', -1, '8', '6'};
  char tmp_buf[n + 1];
  tmp_buf[n] = '\0';

  solve(n, returnSize, &result, returnColumnSizes, &capacity, map, tmp_buf, 0, n - 1);
  return result;
}

int main(void)
{
  int x;
  printf("Enter x: ");
  scanf("%d", &x);

  for (int n = 1; n <= x; n++)
  {
    int returnSize = 0;
    int *returnColumnSizes = NULL;
    char **result = findStrobogrammatic(n, &returnSize, &returnColumnSizes);
    printf("\nn = %d (%d results):\n", n, returnSize);

    for (int i = 0; i < returnSize; i++)
      printf("%s\n", result[i]);

    for (int i = 0; i < returnSize; i++)
      free(result[i]);

    free(result);
    free(returnColumnSizes);
  }

  return 0;
}
