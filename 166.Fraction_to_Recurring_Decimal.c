#define HASH_SIZE 100003

char *fractionToDecimal(int numerator, int denominator)
{
  if (numerator == 0)
  {
    char *result = malloc(2 * sizeof(*result));
    strcpy(result, "0");
    return result;
  }

  int capacity = 1024;
  char *result = malloc(capacity * sizeof(*result));

  long long nume = numerator;
  long long deno = denominator;
  int res_idx = 0;

  //Pre process input for signs
  if ((nume < 0) ^ (deno < 0))
    result[res_idx++] = '-';

  if (nume < 0)
    nume = -nume;

  if (deno < 0)
    deno = -deno;

  //1. Handle integer part
  long long int_part = nume / deno;
  long long remain = nume % deno;

  //Convert integer to char
  int start_int = res_idx;

  do
  {
    if (res_idx == capacity)
    {
      capacity *= 2;
      result = realloc(result, capacity * sizeof(*result));
    }

    result[res_idx++] = int_part % 10 + '0';
    int_part /= 10;
  } while (int_part > 0);

  //Reverse
  for (int left = start_int, right = res_idx - 1;
       left < right;
       left++, right--)
  {
    char tmp = result[left];
    result[left] = result[right];
    result[right] = tmp;
  }

  //2. Handle fractional part
  if (remain == 0)
  {
    result[res_idx] = '\0';
    return result;
  }

  //Add decimal point
  result[res_idx++] = '.';

  //Have we seen this remainder before?
  long long *seen = malloc(HASH_SIZE * sizeof(*seen));
  //Where in the result did this remainer first appear?
  int *pos = malloc(HASH_SIZE * sizeof(*pos));

  for (int i = 0; i < HASH_SIZE; i++)
    seen[i] = -1;

  while (remain != 0)
  {
    int idx = remain % HASH_SIZE;
    bool found = false;
    int prev_idx = -1;

    while (seen[idx] != -1)
    {
      if (seen[idx] == remain)
      {
        found = true;
        prev_idx = pos[idx];
        break;
      }
      idx = (idx + 1) % HASH_SIZE;
    }

    //Recurring decimal detected
    if (found)
    {
      if (res_idx == capacity)
      {
        capacity += 3;
        result = realloc(result, capacity * sizeof(*result));
      }

      for (int i = res_idx - 1; i >= prev_idx; i--)
        result[i + 1] = result[i];

      result[prev_idx] = '(';
      result[res_idx + 1] = ')';
      result[res_idx + 2] = '\0';

      free(seen);
      free(pos);
      return result;
    }

    else
    {
      seen[idx] = remain;
      pos[idx] = res_idx;

      remain *= 10;
      if (res_idx == capacity)
      {
        capacity *= 2;
        result = realloc(result, capacity * sizeof(*result));
      }

      result[res_idx++] = remain / deno + '0';
      remain = remain % deno;
    }
  }

  //3. Final result
  result[res_idx] = '\0';
  free(seen);
  free(pos);

  return result;
}
