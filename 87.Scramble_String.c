/*
char *swap_substring(char *s, int len, int pos)
{
  if (len < 2 || pos >= len || pos <= 0)
    return s;

  int left_len = pos, right_len = len - pos;
  char left[left_len], right[right_len];
  for (int i = 0; i < left_len; i++)
    left[i] = s[i];
  for (int j = 0; j < right_len; j++)
    right[j] = s[j + pos];

  char *result = malloc((len + 1) * sizeof(*s));
  int idx = 0;
  for (int j = 0; j < right_len; j++)
    result[idx++] = right[j];
  for (int i = 0; i < left_len; i++)
    result[idx++] = left[i];
  result[len] = '\0';

  return result;
}
*/

bool solve(char* s1, char* s2, int s1_idx, int s2_idx, int len, int ***memo)
{
  if (len == 1)
    return (memo[s1_idx][s2_idx][len] = (s1[s1_idx] == s2[s2_idx]));

  if (memo[s1_idx][s2_idx][len] != -1)
    return memo[s1_idx][s2_idx][len];

  for (int i = 1; i < len; i++)
  {
    //No swap
    bool nw1 = solve(s1, s2, s1_idx, s2_idx, i, memo);
    bool nw2 = solve(s1, s2, s1_idx + i, s2_idx + i, len - i, memo);
    if (nw1 && nw2)
      return (memo[s1_idx][s2_idx][len] = 1);

    //Swap
    bool sw_left = solve(s1, s2, s1_idx, s2_idx + len - i, i, memo);
    bool sw_right = solve(s1, s2, s1_idx + i, s2_idx, len - i, memo);
    if (sw_left && sw_right)
      return (memo[s1_idx][s2_idx][len] = 1);
  }

  return (memo[s1_idx][s2_idx][len] = 0);
}

bool isScramble(char* s1, char* s2)
{
  int len = strlen(s1);
  int ***memo = malloc(len * sizeof(*memo));
  for (int i = 0; i < len; i++)
  {
    memo[i] = malloc(len * sizeof(**memo));
    for (int j = 0; j < len; j++)
      memo[i][j] = malloc((len + 1) * sizeof(***memo));
  }

  for (int i = 0; i < len; i++)
    for (int j = 0; j < len; j++)
      for (int k = 0; k <= len; k++)
        memo[i][j][k] = -1;

  bool result = solve(s1, s2, 0, 0, len, memo);
  for (int i = 0; i < len; i++)
  {
    for (int j = 0; j < len; j++)
      free(memo[i][j]);

    free(memo[i]);
  }

  free(memo);
  return result;
}
