int shortest_dist_identical(char **wordsDict, int wordsDictSize, char *word)
{
  int prev = -1;
  int result = wordsDictSize;
  for (int i = 0; i < wordsDictSize; i++)
  {
    if (strcmp(wordsDict[i], word) == 0)
    {
      if (prev != -1 && result > i - prev)
      {
        result = i - prev;

        if (result == 1)
          return result;
      }

      prev = i;
    }
  }

  return result;
}

int shortest_dist(char **wordsDict, int wordsDictSize, char *word1, char *word2)
{
  int idx1 = -1;
  int idx2 = -1;
  int result = wordsDictSize;
  for (int i = 0; i < wordsDictSize; i++)
  {
    if (strcmp(wordsDict[i], word1) == 0)
      idx1 = i;

    if (strcmp(wordsDict[i], word2) == 0)
      idx2 = i;

    if (idx1 != -1 && idx2 != -1)
    {
      int dist = abs(idx1 - idx2);

      if (result > dist)
      {
        result = dist;
        if (result == 1)
          return result;
      }
    }
  }

  return result;
}

int shortestWordDistance(char **wordsDict, int wordsDictSize, char *word1, char *word2)
{
  if (strcmp(word1, word2) == 0)
    return shortest_dist_identical(wordsDict, wordsDictSize, word1);

  return shortest_dist(wordsDict, wordsDictSize, word1, word2);
}
