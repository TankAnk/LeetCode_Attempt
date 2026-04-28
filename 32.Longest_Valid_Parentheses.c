#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int longestValidParentheses(char* s) {
  int len = strlen(s);
  if (len <= 1)
    return 0;
  
  int result = 0, top = -1;
  int *stack = malloc(sizeof(*stack) * (len + 1));
  stack[++top] = -1;

  for (int  i = 0; s[i]; i++)
  {
    if (s[i] == '(')
      stack[++top] = i;

    else
    {
      top--;
      if (top < 0)
	stack[++top] = i;

      else
      {
	int tmp = i - stack[top];
	if (result < tmp)
	  result = tmp;
      }
    }
  }

  free(stack);
  return result;
}

int main()
{
  char s[] = "()(()";
  printf("%d\n", longestValidParentheses(s));

  return 0;
}
