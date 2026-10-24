int calculate(char *s)
{
  int *numbers = malloc(150001 * sizeof(*numbers));
  int num_size = 0;
  char *operators = malloc(149999 * sizeof(*operators));
  int op_size = 0;

  for (int i = 0, len = strlen(s); i < len; i++)
  {
    if (s[i] == ' ')
      continue;

    if ('0' <= s[i] && s[i] <= '9')
    {
      long curr = s[i] - '0';
      while (i + 1 < len && '0' <= s[i + 1] && s[i + 1] <= '9')
      {
        curr *= 10;
        curr += (s[i + 1] - '0');
        i++;
      }

      numbers[num_size++] = (int)curr;
    }

    else
      operators[op_size++] = s[i];
  }

  int result = numbers[0];

  if (op_size == 0)
  {
    free(numbers);
    free(operators);
    return result;
  }

  // i to traverse numbers[] and j to traverse operators.
  int i = 1, j = 0;

  while (i < num_size && j < op_size)
  {
    // If the current number is 0, skip all the next * and / operations and numbers.
    if (numbers[i] == 0)
    {
      // Set result to 0 if the current operator is *.
      if (operators[j] == '*')
        result = 0;

      i++;
      j++;
      while (i < num_size && j < op_size && (operators[j] == '*' || operators[j] == '/'))
      {
        i++;
        j++;
      }
    }

    // If it's either * or /, simply operate on the current number.
    else if (operators[j] == '*' || operators[j] == '/')
    {
      result = (operators[j] == '*') ? result * numbers[i] : result / numbers[i];
      i++;
      j++;
    }

    // If it's either + or -.
    else if (operators[j] == '+' || operators[j] == '-')
    {
      // If this is the last number OR the next operator is either + or -
      // simply operates on the current number.
      if (i == num_size - 1
          || (j + 1 < op_size && (operators[j + 1] == '-' || operators[j + 1] == '+'))
          )
      {
        result = (operators[j] == '+') ? result + numbers[i] : result - numbers[i];
        i++;
        j++;
      }

      // If the next operator is either * or /, finish the higher priority expression first.
      else
      {
        int sign = (operators[j] == '+') ? 1 : -1;
        int curr = numbers[i];
        i++;
        j++;

        while (i < num_size && j < op_size && (operators[j] == '*' || operators[j] == '/'))
        {
          curr = (operators[j] == '*') ? curr * numbers[i] : curr / numbers[i];
          i++;
          j++;
        }

        result += (sign * curr);
      }
    }
  }

  free(numbers);
  free(operators);

  return result;
}

/*
5/2-1-2+25/3+6*42/2*3-0/2*1/23
num = [5,2,1,2,25,3,6,42,2,3,0,2,1,23]
ope = [/,-,-,+,/,+,*,/,*,-,/,*,/]
*/
