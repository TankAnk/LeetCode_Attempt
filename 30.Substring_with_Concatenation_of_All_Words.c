int find_word(char **unique, int unique_count, const char *word)
{
  for (int i = 0; i < unique_count; i++)
    if (strcmp(word, unique[i]) == 0)
      return i;

  return -1;
}

int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
  *returnSize = 0;
  int s_len = strlen(s), w_len = strlen(words[0]), comb_len = wordsSize * w_len;
  if (s_len < comb_len)
    return NULL;
  
  int *result = malloc(sizeof(*result) * (s_len - comb_len + 1));  
  char *unique[5000];
  int target[5000];
  int unique_count = 0;

  for (int i = 0; i < wordsSize; i++)
  {
    int idx = find_word(unique, unique_count, words[i]);
    if (idx == -1)
    {
      unique[unique_count] = words[i];
      target[unique_count] = 1;
      unique_count++;
    }

    else
      target[idx]++;
  }

  int *seen = malloc(sizeof(*seen) * unique_count); 

  for (int i = 0; i <= s_len - comb_len; i++)
  {
    memset(seen, 0, sizeof(int) * unique_count);
    int matched = 0;

    for (int j = 0; j < wordsSize; j++)
    {
      char tmp[w_len + 1];
      strncpy(tmp, s + i + j * w_len, w_len);
      tmp[w_len] = '\0';

      int idx = find_word(unique, unique_count, tmp);
      if (idx == -1)
	break;

      seen[idx]++;

      if (seen[idx] > target[idx])
	break;

      matched++;
    }

    if (matched == wordsSize)
      result[(*returnSize)++] = i;
  }
  free(seen);

  return result;
}
