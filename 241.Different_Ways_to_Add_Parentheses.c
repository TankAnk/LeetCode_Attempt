/*
1*2-3*4+5
val = 1 2 3 4 5
ope =  * - * +
No of Operands m = 5
No of Operator n = 4

- Choose any operator to be the last to be considered -> left expression and right expression.
- Recursively evaluate left and right expression.
1. + at last: (1*2-3*4)+(5)
2. * at last: (1*2-3)*(4+5)
3. - at last: (1*2)-(3*4+5)
4. * at last: (1)*(2-3*4+5)
*/

int *solve(char *expression, int ex_start, int ex_end, int *operators, int op_start, int op_end, int *returnSize)
{
  // If this expression has no operator.
  if (op_start > op_end)
  {
    int *result = malloc(sizeof(*result));

    // Convert substring into an integer.
    int num = 0;
    for (int i = ex_start; i <= ex_end; i++)
      num = num * 10 + (expression[i] - '0');

    *returnSize = 1;
    result[0] = num;
    return result;
  }

  int capacity = 32;
  int *result = malloc(capacity * sizeof(*result));
  *returnSize = 0;

  for (int i = op_start; i <= op_end; i++)
  {
    int op_idx = operators[i];
    int left_size, right_size;
    int *left = solve(expression, ex_start, op_idx - 1, operators, op_start, i - 1, &left_size);
    int *right = solve(expression, op_idx + 1, ex_end, operators, i + 1, op_end, &right_size);

    // Combine every possible pair of results.
    for (int l = 0; l < left_size; l++)
    {
      for (int r = 0; r < right_size; r++)
      {
        int val;
        if (expression[op_idx] == '+')
          val = left[l] + right[r];
        else if (expression[op_idx] == '-')
          val = left[l] - right[r];
        else
          val = left[l] * right[r];

        if (*returnSize == capacity)
        {
          capacity *= 2;
          result = realloc(result, capacity * sizeof(*result));
        }

        result[(*returnSize)++] = val;
      }
    }

    free(left);
    free(right);
  }

  return result;
}

int *diffWaysToCompute(char *expression, int *returnSize)
{
  int capacity = 64;
  int return_size = 0;

  // Array to store the indices of operators in the string.
  int operators[10];
  int operators_size = 0;
  for (int i = 0; expression[i] != '\0'; i++)
  {
    if ('0' <= expression[i] && expression[i] <= '9')
      continue;

    operators[operators_size++] = i;
  }

  return solve(expression, 0, strlen(expression) - 1, operators, 0, operators_size - 1, returnSize);
}
