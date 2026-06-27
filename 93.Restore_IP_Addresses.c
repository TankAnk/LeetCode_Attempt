void solve(char *s, int s_idx, int s_len, char ***result, int *returnSize, char *curr, int curr_idx, int curr_len, int dot_count, int *capacity)
{
  if (curr_idx == curr_len && s_idx == s_len && dot_count == 3)
  {
    if (*returnSize == *capacity)
    {
      *capacity *= 2;
      *result = realloc(*result, *capacity * sizeof(**result));
    }
    (*result)[*returnSize] = malloc((curr_len + 1) * sizeof(***result));
    memcpy((*result)[(*returnSize)++], curr, (curr_len + 1) * sizeof(***result));

    return;
  }

  if (dot_count > 3 || curr_idx >= curr_len  || s_idx >= s_len)
    return;

  //Cannot have leading 0
  curr[curr_idx] = s[s_idx];
  int start = curr_idx;
  while (start > 0 && curr[start - 1] != '.')
    start--;
  if (start != curr_idx && curr[start] == '0')
    return;

  //Octet cannot exceed 255
  int num = 0, pow = 1, i = curr_idx;
  while (i >= 0 && curr[i] != '.')
  {
    num += ((curr[i] - '0') * pow);
    pow *= 10;
    i--;
  }
  if (num > 255)
    return;

  //Add next number to the octet
  solve(s, s_idx + 1, s_len, result, returnSize, curr, curr_idx + 1, curr_len, dot_count, capacity);

  //Place a dot right after
  if (s_idx + 1 < s_len)
  {
    curr[curr_idx + 1] = '.';
    solve(s, s_idx + 1, s_len, result, returnSize, curr, curr_idx + 2, curr_len, dot_count + 1, capacity);
  }
}

char **restoreIpAddresses(char *s, int *returnSize)
{
  *returnSize = 0;
  int len = strlen(s), capacity = 128;
  char **result;
  if (len < 4 || len > 12)
    return result;

  result = malloc(capacity * sizeof(*result));

  char *curr = malloc((len + 4) * sizeof(*curr));
  curr[len + 3] = '\0';

  solve(s, 0, len, &result, returnSize, curr, 0, len + 3, 0, &capacity);

  free(curr);
  return result;
}
