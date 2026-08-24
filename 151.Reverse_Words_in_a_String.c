/*1st attempt
char *reverseWords(char *s)
{
  char stack[10000];
  int len = strlen(s);
  int s_idx = len - 1, stk_idx = -1, res_size = 0;
  char *result = malloc((len + 1) * sizeof(*result));
  memset(result, '\0', (len + 1) * sizeof(*result));

  while (s_idx >= 0)
  {
    if (s[s_idx] == ' ')
    {
      s_idx--;
      continue;
    }

    while (s_idx >= 0 && s[s_idx] != ' ')
      stack[++stk_idx] = s[s_idx--];

    //If there is a word needed to insert and this result is not empty, add a space
    if (stk_idx >= 0 && res_size > 0)
      result[res_size++] = ' ';

    while (stk_idx > -1)
      result[res_size++] = stack[stk_idx--];
  }

  return result;
}
*/

/*O(1) solution
Ex: the sky is blue
1. Remove extra whitespace
2. Reverse each word:
eht yks si eulb
3. Reverse the entire string:
blue is sky the
*/

char *reverseWords(char *s)
{
  //1. Remove extra whitespace
  int read = 0, write = 0;
  while (s[read] != '\0')
  {
    while (s[read] != '\0' && s[read] == ' ')
      read++;

    if (write > 0 && s[read] != '\0')
      s[write++] = ' ';

    while (s[read] != '\0' && s[read] != ' ')
      s[write++] = s[read++];
  }
  s[write] = '\0';

  //2. Reverse each word in string
  int left = 0, right = 0, len = strlen(s);
  while (right < len)
  {
    //left == right at the beginning
    //skip whitespace
    while (s[left] != '\0' && s[left] == ' ')
    {
      left++;
      right++;
    }

    //Find the word range
    while (s[right] != '\0' && s[right] != ' ')
      right++;

    //Reverse word
    int l_ptr = left, r_ptr = right - 1;
    while (l_ptr < r_ptr)
    {
      char tmp = s[l_ptr];
      s[l_ptr] = s[r_ptr];
      s[r_ptr] = tmp;
      l_ptr++;
      r_ptr--;
    }

    left = right;
  }

  //3. Reverse entire string
  for (int i = 0; i < len / 2; i++)
  {
    char tmp = s[i];
    s[i] = s[len - 1 - i];
    s[len - 1 - i] = tmp;
  }

  return s;
}
