/*
void solve(char *s, int start, int end, int len, int cnt, int *result)
{
  if (end >= len || start >= len || cnt > len)
    return;

  if (is_palindrome(s, start, end))
  {
    if (end == len - 1)
    {
      *result = (*result < cnt ? *result : cnt);
      return;
    }

    else
      solve(s, end + 1, end + 1, len, cnt + 1, result);
  }

  solve(s, start, end + 1, len, cnt, result);
}

int minCut(char *s)
{
  int len = strlen(s);
  if (len == 1)
    return 0;

  int result = len + 1;
  solve(s, 0, 0, len, 0, &result);
  return result;
}
*/

bool is_palindrome(char *s, int start, int end)
{
  while (start < end)
    if (s[start++] != s[end--])
      return false;

  return true;
}

int solve(char *s, int start, int end, int len, int memo[][len])
{
  if (end >= len || start >= len)
    return len + 1;

  if (memo[start][end] != -1)
    return memo[start][end];

  if (is_palindrome(s, start, end))
  {
    if (end == len - 1)
      return (memo[start][end] = 0); //0 cut needed if reach the end

    else
    {
      int cut = 1 + solve(s, end + 1, end + 1, len, memo);
      memo[start][end] = (memo[start][end] != -1 && memo[start][end] < cut ? memo[start][end] : cut);
    }
  }

  int keep = solve(s, start, end + 1, len, memo);
  memo[start][end] = (memo[start][end] != -1 && memo[start][end] < keep ? memo[start][end] : keep);

  return memo[start][end];
}

int minCut(char *s)
{
  int len = strlen(s);
  if (len == 1)
    return 0;

  int memo[len][len];
  for (int i = 0; i < len; i++)
    memset(memo[i], 0xFF, len * sizeof(**memo));

  return solve(s, 0, 0, len, memo);
}
