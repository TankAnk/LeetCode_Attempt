int titleToNumber(char *columnTitle)
{
  int len = strlen(columnTitle);
  int result = 0;
  unsigned int mul = 1;

  for (int i = len - 1; i >= 0; i--)
  {
    int curr = columnTitle[i] - 'A' + 1;
    result += (curr * mul);
    mul *= 26;
  }

  return result;
}

/* Basically like convert base 2, base 16, etc to decimal
- ABC = A * 26^2 + B * 26^1 + C * 26^0
- With every char, convert from 0 - 25 to Excel 1 - 26
*/
