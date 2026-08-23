/*
- Scan from left to right, push operand on stack
- Encounter operator, do the caculation
Ex: [a, b, c, d, /] --> [a, b, c / d]
- Maximum stack size:
+ Valid expression requires odd number of total tokens -> Maximum 10^4 - 1 = 9999 tokens
+ Valid expression requires total operands = total operators + 1 -> Maximum operand = 5000 and Maximum operator = 4999
-> Maximum stack size = 5000
*/

/*
00 01 02 03 04 05 06 07 08 09 10
-6 17
*/
#define MAX_SIZE 5000

int evalRPN(char **tokens, int tokensSize)
{
  int stack[MAX_SIZE];
  int idx = -1;

  for (int i = 0; i < tokensSize; i++)
  {
    char *curr = tokens[i];
    int num;

    if ((curr[0] == '-' && curr[1] != '\0') || ('0' <= curr[0] && curr[0] <= '9'))
    {
      num = 0;
      int j = (curr[0] == '-') ? 1 : 0;
      while (curr[j] != '\0')
      {
        num *= 10;
        num += curr[j++] - '0';
      }

      stack[++idx] = (curr[0] == '-') ? -num : num;
    }

    else
    {
      if (curr[0] == '+')
        num = stack[idx - 1] + stack[idx];
      else if (curr[0] == '*')
        num = stack[idx - 1] * stack[idx];
      else if (curr[0] == '-')
        num = stack[idx - 1] - stack[idx];
      else if (curr[0] == '/')
        num = stack[idx - 1] / stack[idx];

      stack[--idx] = num;
    }
  }

  return stack[idx];
}
