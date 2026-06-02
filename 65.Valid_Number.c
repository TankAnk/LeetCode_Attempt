bool isNumber(char* s)
{
  int len = strlen(s);
  if (len == 1)
    return (48 <= s[0] && s[0] <= 57);

  int i = 0;
  //Handle sign at the beginning
  while (s[i] != '\0' && (s[i] == '+' || s[i] == '-'))
    i++;

  //Cannot have more than 1 sign next to each other
  if (i > 1)
    return false;

  //Handle special case for '.': cannot be the last digit or have 'e' followed right after it
  if (s[i] == '.' && (i == len - 1 || s[i + 1] == 'e' || s[i + 1] == 'E'))
    return false;

  int j = i, dot_count = 0, e_count = 0;
  while (s[j] != '\0')
  {
    if (s[j] == '.')
    {
      //Cannot have have more than 1 dot or after 'e'
      if (dot_count > 0 || e_count > 0)
        return false;

      dot_count++;
    }

    else if (s[j] == 'e' || s[j] == 'E')
    {
      //Cannot have more than 1 'e' or at the start or at the end
      if (e_count > 0 || j == i || j == len - 1)
        return false;

      e_count++;

      //Handle possible sign after 'e'
      if (s[j + 1] == '+' || s[j + 1] == '-')
        j++;

      //Cannot have a sign at the end
      if (j == len - 1)
        return false;
    }

    else if (s[j] < 48 || s[j] > 57)
      return false;

    j++;
  }

  return true;
}
