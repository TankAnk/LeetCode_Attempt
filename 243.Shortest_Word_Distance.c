bool str_equal(char *s1, char *s2)
{
  int i = 0;
  while (s1[i] != '\0' && s2[i] != '\0')
  {
    if (s1[i] != s2[i])
      return false;

    i++;
  }

  return (s1[i] == s2[i]);
}

/*
     0 1 2 3 4 5 6 7 8
ws = a c b b e a d a b
w1 = a -> 0 5 7
w2 = b -> 2 3 8
Shortest = |7 - 8| = 1

- Traverse the word dictionary.
- Keep track of the latest index of word 1 and word 2.
- Keep track of the min distance.
*/

int shortestDistance(char **wordsDict, int wordsDictSize, char* word1, char* word2)
{
  int last_w1_idx = -1;
  int last_w2_idx = -1;
  int result = wordsDictSize;

  for (int i = 0; i < wordsDictSize; i++)
  {
    if (str_equal(word1, wordsDict[i]))
      last_w1_idx = i;

    if (str_equal(word2, wordsDict[i]))
      last_w2_idx = i;

    if (last_w1_idx != -1 && last_w2_idx != -1)
    {
      int curr_dist = abs(last_w1_idx - last_w2_idx);
      result = (result > curr_dist) ? curr_dist : result;
    }
  }

  return result;
}
