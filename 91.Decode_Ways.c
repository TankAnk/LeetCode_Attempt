int str_to_int(char *s, int l_idx, int r_idx)
{
  int result = 0;
  for (int i = r_idx, pow = 1; i >= l_idx; i--)
  {
    result += ((s[i] - '0') * pow);
    pow *= 10;
  }

  return result;
}

int solve(char *s, int len, int idx, int *memo)
{
  if (idx >= len)
    return 1;

  if (s[idx] == '0')
    return (memo[idx] = 0);

  if (memo[idx] != -1)
    return memo[idx];

  memo[idx] = solve(s, len, idx + 1, memo);

  if (idx + 1 < len)
  {
    int num = ((s[idx] - '0') * 10) + (s[idx + 1] - '0');
    if (10 <= num && num <= 26)
    memo[idx] += solve(s, len, idx + 2, memo);
  }

  return memo[idx];
}

int numDecodings(char* s)
{
  int len = strlen(s);
  int *memo = malloc(len * sizeof(*memo));
  for (int i = 0; i < len; i++)
    memo[i] = -1;

  int result = solve(s, len, 0, memo);
  free(memo);
  return result;
}
