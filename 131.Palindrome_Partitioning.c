#define MAX_LEN 16

bool is_palindrome(char *s, int start, int end)
{
  while (start < end)
    if (s[start++] != s[end--])
      return false;

  return true;
}

void solve(char *s, int start, int end, int len, char curr[][MAX_LEN + 1], int curr_idx, char ****result, int *returnSize, int **returnColumnSizes, int *capacity)
{
  if (end >= len || start >= len || curr_idx >= MAX_LEN)
    return;

  if (is_palindrome(s, start, end))
  {
    memcpy(curr[curr_idx], s + start, (end - start + 1) * sizeof(**curr));
    curr[curr_idx][end - start + 1] = '\0';

    if (end == len - 1)
    {
      if (*returnSize == *capacity)
      {
        *capacity *= 2;
        *result = realloc(*result, *capacity * sizeof(**result));
        *returnColumnSizes = realloc(*returnColumnSizes, *capacity * sizeof(**returnColumnSizes));
      }

      (*returnColumnSizes)[*returnSize] = curr_idx + 1;
      (*result)[*returnSize] = malloc((curr_idx + 1) * sizeof(***result));
      for (int i = 0; i <= curr_idx; i++)
      {
        (*result)[*returnSize][i] = malloc((strlen(curr[i]) + 1) * sizeof(****result));
        strcpy((*result)[*returnSize][i], curr[i]);
      }

      (*returnSize)++;

      return;
    }

    else
      solve(s, end + 1, end + 1, len, curr, curr_idx + 1, result, returnSize, returnColumnSizes, capacity);
  }

  solve(s, start, end + 1, len, curr, curr_idx, result, returnSize, returnColumnSizes, capacity);
}

char ***partition(char *s, int *returnSize, int **returnColumnSizes)
{
  *returnSize = 0;
  int capacity = 128, len = strlen(s);
  char ***result = malloc(capacity * sizeof(*result));
  *returnColumnSizes = malloc(capacity * sizeof(**returnColumnSizes));

  char curr[MAX_LEN][MAX_LEN + 1];
  for (int i = 0; i < MAX_LEN; i++)
    memset(curr[i], '\0', (MAX_LEN + 1) * sizeof(**curr));

  solve(s, 0, 0, len, curr, 0, &result, returnSize, returnColumnSizes, &capacity);

  return result;
}
