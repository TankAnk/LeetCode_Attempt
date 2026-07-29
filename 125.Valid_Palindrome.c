bool isPalindrome(char *s)
{
  int len = strlen(s);
  char clean[len + 1];
  int clean_len = 0;

  for (int i = 0; i < len; i++)
  {
    //Uppercase alphabet
    if (65 <= s[i] && s[i] <= 90)
      clean[clean_len++] = s[i] + 32;

    //Lowercase alphabet OR number
    else if ((97 <= s[i] && s[i] <= 122) || (48 <= s[i] && s[i] <= 57))
      clean[clean_len++] = s[i];
  }
  clean[clean_len] = '\0';

  for (int left = 0, right = clean_len - 1; left < right; left++, right--)
    if (clean[left] != clean[right])
      return false;

  return true;
}
