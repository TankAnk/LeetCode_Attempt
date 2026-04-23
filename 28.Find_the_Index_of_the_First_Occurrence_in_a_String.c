/*Easiest:
int strStr(char* haystack, char* needle) {
  char *result = strstr(haystack, needle);
  if (!result)
    return -1;

  return result - haystack;
}
*/
int strStr(char* haystack, char* needle) {
  if (strlen(needle) > strlen(haystack))
    return -1;

  int len = strlen(needle);
  for (int i = 0; haystack[i] != '\0'; i++)
  {
    if (haystack[i] == needle[0])
    {
      int count = 1, j = i + 1, k = 1;
      for (j, k; haystack[j] != '\0' && k < len; k++, j++)
	if (haystack[j] == needle[k])
	  count++;

      if (count == len)
	return i;

      i = j - 1;
    }
  }

  return -1;
}
