#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* countAndSay(int n) {
  char *result = malloc(sizeof(*result) * 2);
  result[0] = '1';
  result[1] = '\0';

  //3 3 2 2 2 5 1
  //0 1 3 4 5 6 7
  for (int i = 0; i < n - 1; i++)
  {
    int idx = 0, result_len = 0;
    char *tmp = malloc(sizeof(*tmp) * (strlen(result) + 1));
    strcpy(tmp, result);
    while (tmp[idx] != '\0')
    {
      char c = tmp[idx];
      int count = 0;
      while (tmp[idx] == c)
      {
	idx++;
	count++;
      }

      result_len += 2;
      result = (char *)realloc(result, sizeof(*result) * (result_len + 1));
      result[result_len - 2] = '0' + count;
      result[result_len - 1] = c;
      result[result_len] = '\0';
    }

    free(tmp);
  }

  return result;
}

int main()
{
  char *s = countAndSay(4);
  printf("%s\n", s);
}
