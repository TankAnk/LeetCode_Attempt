int calculate(char *s)
{
  int result = 0;

  // Sign of the CURRENT operator.
  int local_sign = 1;

  // Cumulative sign.
  int context_sign = 1;

  char sign_stack[300000];
  int top = -1;

  for (int i = 0, len = strlen(s); i < len; i++)
  {
    if (s[i] == ' ')
      continue;

    if (s[i] == '+')
      local_sign = 1;

    else if (s[i] == '-')
      local_sign = -1;

    else if (s[i] == '(')
    {
      // Save the existing context.
      sign_stack[++top] = context_sign;

      // Apply local sign and context sign.
      context_sign *= local_sign;

      // Reset local operator sign as local_sign is already consumed.
      local_sign = 1;
    }

    else if (s[i] == ')')
      // Retrieve previous state.
      context_sign = sign_stack[top--];

    else
    {
      long curr_num = s[i] - '0';
      while (i + 1 < len && '0' <= s[i + 1] && s[i + 1] <= '9')
      {
        curr_num *= 10;
        curr_num += (s[i + 1] - '0');
        i++;
      }

      result += curr_num * local_sign * context_sign;
    }
  }

  return result;
}
