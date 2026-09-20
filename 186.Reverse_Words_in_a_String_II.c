#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Original: the sky is blue
Reverse entire string: eulb si yks eht
Reverse each word: blue is sky the
*/

void reverseWords(char *s)
{
  int size = strlen(s);

  if (size <= 2)
    return;

  // Reverse the entire string
  for (int i = 0; i < size / 2; i++)
  {
    char tmp = s[i];
    s[i] = s[size - 1 - i];
    s[size - 1 - i] = tmp;
  }

  // Reverse each word
  int start = 0, end = 0;
  while (end < size)
  {
    while (end < size && s[end] != ' ')
      end++;

    for (int i = 0, wrd_size = end - start; i < wrd_size / 2; i++)
    {
      char tmp = s[start + i];
      s[start + i] = s[end - 1 - i];
      s[end - 1 - i] = tmp;
    }

    start = ++end;
  }
}

int main()
{
  // char string[] = "The sky is blue";
  // char string[] = "Hello world!";
  // char string[] = "a hello world";
  // char string[] = "a";
  // char string[] = "a b c d";
  int len = strlen(string);
  char *s = malloc((len + 1) * sizeof(*s));
  memcpy(s, string, (len + 1) * sizeof(*s));
  reverseWords(s);

  printf("[");
  printf("%s", s);
  printf("]\n");
}
