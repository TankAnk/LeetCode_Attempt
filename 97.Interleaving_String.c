bool solve(char *s1, int len1, int s1_idx, char *s2, int len2, int s2_idx, char *s3, int len3, int **memo)
{
  if (memo[s1_idx][s2_idx] != -1)
    return memo[s1_idx][s2_idx];

  if (s1_idx + s2_idx == len3)
    return memo[s1_idx][s2_idx] = true;

  bool c1 = false, c2 = false;
  if (s1_idx < len1 && s1[s1_idx] == s3[s1_idx + s2_idx])
    c1 = solve(s1, len1, s1_idx + 1, s2, len2, s2_idx, s3, len3, memo);

  if (s2_idx < len2 && s2[s2_idx] == s3[s1_idx + s2_idx])
    c2 = solve(s1, len1, s1_idx, s2, len2, s2_idx + 1, s3, len3, memo);

  return (memo[s1_idx][s2_idx] = c1 || c2);
}

bool isInterleave(char* s1, char* s2, char* s3)
{
  int len1 = strlen(s1), len2 = strlen(s2), len3 = strlen(s3);
  if (len3 == 0)
    return (len1 == 0 && len2 == 0);

  if (len1 == 0)
    return (strcmp(s2, s3) == 0);

  if (len2 == 0)
    return (strcmp(s1, s3) == 0);

  if (len1 + len2 != len3)
    return false;

  int **memo = malloc((len1 + 1)* sizeof(*memo));
  for (int i = 0; i <= len1; i++)
  {
    memo[i] = malloc((len2 + 1)* sizeof(**memo));
    for (int j = 0; j <= len2; j++)
      memo[i][j] = -1;
  }

  bool result = solve(s1, len1, 0, s2, len2, 0, s3, len3, memo);
  for (int i = 0; i <= len1; i++)
    free(memo[i]);
  free(memo);
  return result;
}
