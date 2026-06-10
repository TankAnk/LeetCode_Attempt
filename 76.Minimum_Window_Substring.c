#define SIZE 53 //Total 52 char --> next prime is 53
unsigned int hash_char(char c)
{
  if (c <= 'Z')
    return ((unsigned char)c - 'A') % SIZE;
  return ((unsigned char)c - 71) % SIZE;
}

char* minWindow(char* s, char* t)
{
  int s_len = strlen(s), t_len = strlen(t);
  char *result = malloc((s_len + 1) * sizeof(*result));
  result[0] = '\0';
  if (s_len < t_len)
    return result;

  int *occur = calloc(SIZE, sizeof(*occur));
  for (int i = 0; i < t_len; i++)
    occur[hash_char(t[i])]++;
  int *window = calloc(SIZE, sizeof(*window));
  int occur_count = 0, min = s_len + 1, min_start = 0, window_start = 0, window_end = 0;
  unsigned int key;

  while (window_end < s_len)
  {
    key = hash_char(s[window_end]);
    window[key]++;

    if (window[key] <= occur[key])
      occur_count++;

    while (occur_count == t_len)
    {
      if (window_end - window_start + 1 < min)
      {
        min = window_end - window_start + 1;
        min_start = window_start;
      }

      key = hash_char(s[window_start]);

      window[key]--;
      if (window[key] < occur[key])
        occur_count--;

      window_start++;
    }

    window_end++;
  }

  if (min <= s_len)
  {
      memcpy(result, s + min_start, min * sizeof(*result));
      result[min] = '\0';
  }

  free(occur);
  free(window);

  return result;
}
