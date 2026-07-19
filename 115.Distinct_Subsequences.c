int numDistinct(char *s, char *t)
{
  int s_len = strlen(s), t_len = strlen(t);
  int diff = s_len - t_len;
  if (diff < 0)
    return 0;

  if (diff == 0)
    return (strcmp(s, t) == 0 ? 1 : 0);

  //memo[i][j] = how many way to form first j char from t with first i char from s
  //i for s, j for t
  unsigned int **memo = malloc((s_len + 1) * sizeof(*memo));
  for (int i = 0; i <= s_len; i++)
    memo[i] = calloc(t_len + 1, sizeof(**memo));

  //If t empty -> 1 way to form (delete all char)
  for (int i = 0; i <= s_len; i++)
    memo[i][0] = 1;

  //If s empty but t is not -> 0 way
  for (int j = 1; j <= t_len; j++)
    memo[0][j] = 0;

  for (int i = 1; i <= s_len; i++)
  {
    for (int j = 1; j <= t_len; j++)
    {
      //Can use matching char OR skip it
      if (s[i - 1] == t[j - 1])
        memo[i][j] = memo[i - 1][j - 1] + memo[i - 1][j];

      //Must skip if does not match
      else
        memo[i][j] = memo[i - 1][j];
    }
  }

  int result = (int)memo[s_len][t_len];
  for (int i = 0; i <= s_len; i++)
    free(memo[i]);
  free(memo);
  return result;
}

/*
s = babgbag
t = bag
ba|b|g|bag|     --> Remove idx 2,4,5,6
ba|bgba|g       --> Remove idx 2,3,4,5
b|abgb|ag       --> Remove idx 1,2,3,4
|ba|b|gb|ag     --> Remove idx 0,1,3,4
|babg|bag       --> Remove idx 0,1,2,3
*/
