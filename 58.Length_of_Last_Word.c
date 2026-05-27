#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lengthOfLastWord(char* s) {
  int idx = strlen(s) - 1, count = 0;
  while (idx >= 0 && s[idx] == ' ')
    idx--;

  while (idx >= 0 && s[idx] != ' ')
  {
    count++;
    idx--;
  }

  return count;
}

int main()
{
  char *s = "hello                                                  ";
  printf("%d\n", lengthOfLastWord(s));

  return 0;
}
