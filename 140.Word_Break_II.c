#define MAX_SIZE 41

void solve(char *s, int s_len, int s_pos, char *curr, int curr_size, char **dict, int dict_size, int *dict_len, char ***result, int *returnSize, int *capacity)
{
  if (s_pos > s_len) //Just in case, I'm sorry I'm insecure
    return;

  if (s_pos == s_len)
  {
    if (*returnSize == *capacity)
    {
      *capacity *= 2;
      *result = realloc(*result, *capacity * sizeof(**result));
    }

    (*result)[*returnSize] = malloc(curr_size * sizeof(***result));
    memcpy((*result)[*returnSize], curr, curr_size * sizeof(***result));
    (*result)[*returnSize][curr_size - 1] = '\0';
    (*returnSize)++;

    return;
  }

  for (int i = 0; i < dict_size; i++)
  {
    int wrd_len = dict_len[i];
    if (curr_size + wrd_len + 1 >= MAX_SIZE) //Just in case
      continue;

    int remain = s_len - s_pos;
    if (wrd_len <= remain && memcmp(dict[i], s + s_pos, wrd_len * sizeof(*s)) == 0)
    {
      memcpy(curr + curr_size, dict[i], wrd_len * sizeof(*curr));
      curr[curr_size + wrd_len] = ' ';
      solve(s, s_len, s_pos + wrd_len, curr, curr_size + wrd_len + 1, dict, dict_size, dict_len, result, returnSize, capacity);
    }
  }
}

char **wordBreak(char *s, char **wordDict, int wordDictSize, int *returnSize)
{
  int s_len = strlen(s);
  *returnSize = 0;
  int capacity = 128;
  char **result = malloc(capacity * sizeof(*result));
  char curr[MAX_SIZE];
  memset(curr, '\0', MAX_SIZE * sizeof(*curr));

  int dict_len[wordDictSize];
  for (int i = 0; i < wordDictSize; i++)
    dict_len[i] = strlen(wordDict[i]);

  solve(s, s_len, 0, curr, 0, wordDict, wordDictSize, dict_len, &result, returnSize, &capacity);

  return result;
}
