bool wordBreak(char *s, char **wordDict, int wordDictSize)
{
  int s_len = strlen(s);
  //State memo[i] means if we can reach position i
  bool memo[s_len + 1];
  memset(memo, false, (s_len + 1) * sizeof(*memo));
  memo[0] = true;

  for (int pos = 0; pos <= s_len; pos++)
  {
    if (!memo[pos])
      continue;

    for (int i = 0; i < wordDictSize; i++)
    {
      int wrd_len = strlen(wordDict[i]);
      int remain = s_len - pos;
      //If curr word fits AND matches substring
      if (wrd_len <= remain && memcmp(s + pos, wordDict[i], wrd_len) == 0)
        memo[pos + wrd_len] = true;
    }
  }

  return memo[s_len];
}
