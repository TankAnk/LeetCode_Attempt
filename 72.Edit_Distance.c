/*
0 1 2 3 4 5 6 7
a b c d e f g
a b I c d e f g
*/
void insert_str(char **str, int pos, int *len, char c)
{
  if (pos > *len)
    pos = *len;
  else if (pos < 0)
    pos = 0;
  *str = realloc(*str, (*len + 2) * sizeof(**str));
  (*str)[*len + 1] = '\0';
  for (int i = *len; i > pos; i++)
    (*str)[i] = (*str)[i - 1];
  (*str)[pos] = c;
  (*len)++;
}

/*
0 1 2 3 4 5 6
a b c d e f g
    x
*/
void del_str(char **str, int pos, int *len)
{
  if (pos >= *len)
    pos = *len - 1;
  else if (pos < 0)
    pos = 0;
  for (int i = pos; i < *len; i++)
    (*str)[i] = (*str)[i + 1];
  *str = realloc(*str, (*len) * sizeof(**str));
  (*len)--;
}

/*
h o r s e
r o s
h o r s e
horse --> rorse --> rose --> ros
*/
int solve(char* word1, char* word2, int len1, int len2, int w1_idx, int w2_idx, int **memo)
{
  if (w1_idx >= len1)
    return len2 - w2_idx;
  if (w2_idx >= len2)
    return len1 - w1_idx;
  if (memo[w1_idx][w2_idx] != -1)
    return memo[w1_idx][w2_idx];

  if (word1[w1_idx] == word2[w2_idx])
    return memo[w1_idx][w2_idx] = solve(word1, word2, len1, len2, w1_idx + 1, w2_idx + 1, memo);

  int a1, a2, a3;
  //Approach 1: Replace
  a1 = 1 + solve(word1, word2, len1, len2, w1_idx + 1, w2_idx + 1, memo);

  //Approach 2: Delete
  a2 = 1 + solve(word1, word2, len1, len2, w1_idx + 1, w2_idx, memo);

  //Approach 3: Insert
  a3 = 1 + solve(word1, word2, len1, len2, w1_idx, w2_idx + 1, memo);

  memo[w1_idx][w2_idx] = a1;
  if (memo[w1_idx][w2_idx] > a2)
    memo[w1_idx][w2_idx] = a2;
  if (memo[w1_idx][w2_idx] > a3)
    memo[w1_idx][w2_idx] = a3;
  return memo[w1_idx][w2_idx];
}

int minDistance(char* word1, char* word2)
{
  int len1 = strlen(word1), len2 = strlen(word2);
  if (len1 == 0)
    return len2;
  if (len2 == 0)
    return len1;

  int **memo = malloc(len1 * sizeof(*memo));
  for (int i = 0; i < len1; i++)
  {
    memo[i] = malloc(len2 * sizeof(**memo));
    memset(memo[i], -1, len2 * sizeof(**memo));
  }

  int result = solve(word1, word2, len1, len2, 0, 0, memo);
  for (int i = 0; i < len1; i++)
    free(memo[i]);
  free(memo);
  return result;
}
