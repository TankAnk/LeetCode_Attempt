#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool check(int **memo, char *s, char *p, int s_len, int p_len, int s_idx, int p_idx)
{
  if (memo[s_idx][p_idx] != -1)
    return memo[s_idx][p_idx];

  if (p_idx >= p_len)
    memo[s_idx][p_idx] = s_idx >= s_len;

  else if (s_idx >= s_len)
    memo[s_idx][p_idx] = (p[p_idx] == '*' && check(memo, s, p, s_len, p_len, s_idx, p_idx + 1));

  else if (p[p_idx] == '*')
    memo[s_idx][p_idx] = (check(memo, s, p, s_len, p_len, s_idx + 1, p_idx) || check(memo, s, p, s_len, p_len, s_idx, p_idx + 1));

  else if (p[p_idx] == '?')
    memo[s_idx][p_idx] = check(memo, s, p, s_len, p_len, s_idx + 1, p_idx + 1);

  else
    memo[s_idx][p_idx] = (s[s_idx] == p[p_idx]) && check(memo, s, p, s_len, p_len, s_idx + 1, p_idx + 1);

  return memo[s_idx][p_idx];    
}

bool isMatch(char* s, char* p) {
  int s_len = strlen(s), p_len = strlen(p);

  if (p_len == 0)
    return (s_len == 0);

  if (s_len == 0)
  {
    for (int i = 0; p[i] != '\0'; i++)
      if (p[i] != '*')
	return false;

    return true;
  }
  
  int **memo = malloc(sizeof(*memo) * (s_len + 1));
  for (int i = 0; i < s_len + 1; i++)
    memo[i] = malloc(sizeof(**memo) * (p_len + 1));
  for (int i = 0; i < s_len + 1; i++)
    memset(memo[i], -1, sizeof(int) * (p_len + 1));
  bool result = check(memo, s, p, s_len, p_len, 0, 0);
  for (int i = 0; i < s_len + 1; i++)
    free(memo[i]);
  free(memo);
  return result;
}  

int main()
{
  char s[] = "adceb";
  char p[] = "*a*b";
  printf("%d\n", isMatch(s, p));

  return 0;
}
