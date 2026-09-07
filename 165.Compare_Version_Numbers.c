int compareVersion(char *version1, char *version2)
{
  int len1 = strlen(version1), len2 = strlen(version2);
  int i1 = 0, i2 = 0;
  while (i1 < len1 && i2 < len2)
  {
    //Calculate the revision
    int rev1 = 0;
    while (i1 < len1 && version1[i1] != '.')
    {
      rev1 = rev1 * 10 + (version1[i1] - '0'); //This already handles leading 0s
      i1++;
    }

    //Same for version2
    int rev2 = 0;
    while (i2 < len2 && version2[i2] != '.')
    {
      rev2 = rev2 * 10 + (version2[i2] - '0');
      i2++;
    }

    if (rev1 < rev2)
      return -1;

    else if (rev1 > rev2)
      return 1;

    //Skip '.'
    i1++;
    i2++;
  }

  /*At this point:
    - version1 is equal to version2
    - Either version1 or version2 is exhausted
  */
  while (i1 < len1)
  {
    //As long as a digit is > 0, we can decide
    while (i1 < len1 && version1[i1] != '.')
    {
      if (version1[i1] > '0')
        return 1;

      i1++;
    }

    //Skip '.'
    i1++;
  }

  while (i2 < len2)
  {
    //As long as a digit is > 0, we can decide
    while (i2 < len2 && version2[i2] != '.')
    {
      if (version2[i2] > '0')
        return -1;

      i2++;
    }

    //Skip '.'
    i2++;
  }

  return 0;
}
