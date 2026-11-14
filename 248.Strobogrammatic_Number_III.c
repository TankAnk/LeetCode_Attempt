/*
- Return the number of strobogrammatic numbers within [low, high].
- Constraints:
+ 1 <= low.length, high.length <= 15.
+ low and high consist of digits only.
+ low <= high.
+ Neither string contains leading zeros, except for the number "0" itself.
*/

/*
- Return all possible strobogrammatic numbers with exactly n digits.

- If n == 1: 0, 1, 8

- All possible strobogrammatic numbers length 5: abcde
+ a&e (most outer pair): 1, 6, 8, 9 -> 4 possible values.
+ b&d (inner pair): 0, 1, 6, 8, 9 -> 5 possible values.
+ c (middle element when length is odd): 0, 1, 8 -> 3 possible values.
-> 4 * 5 * 3 = 60.

- All possible strobogrammatic numbers length 6: abcdef
+ a&f (most outer pair): 1, 6, 8, 9 -> 4 possible values.
+ b&e (inner pair): 0, 1, 6, 8, 9 -> 5 possible values.
+ c&d (inner pair): 0, 1, 8, 8, 9 -> 5 possible values.
-> 4 * 5 * 5 = 100.
*/
int strobogrammatic_count(int n)
{
  if (n <= 0)
    return 0;

  int result = 1;
  for (int left = 0, right = n - 1; left <= right; left++, right--)
  {
    if (left == 0 && n > 1)
      result *= 4;

    else if (left == right)
      result *= 3;

    else
      result *= 5;
  }

  return result;
}

/*
  Calculate the total number of strobogrammatic numbers that:
  - Has exactly len digits AND
  - Less than or equal to num.

  Constraint: len == strlen(num)

  619|097
  abcdef
  a&f: min = 1, max = 6 -> 1, 6
*/
int strobogrammatic_count_same_length(char *num, int len)
{
  int outer[] = {1, 6, 8, 9};
  int inner[] = {0, 1, 6, 8, 9};
  int middle[] = {0, 1, 8};
  int rotate[] = {'0', '1', -1, -1, -1, -1, '9', -1, '8', '6'};

  int result = 0;
  int bound = (len + 1) / 2;
  bool prefix_valid = true;

  for (int left = 0; left < bound; left++)
  {
    int *map;
    int size;

    if (left == 0 && len > 1)
    {
      map = outer;
      size = sizeof(outer) / sizeof(*outer);
    }
    else if (len % 2 == 1 && left == bound - 1)
    {
      map = middle;
      size = sizeof(middle) / sizeof(*middle);
    }
    else
    {
      map = inner;
      size = sizeof(inner) / sizeof(*inner);
    }

    int curr_digit = num[left] - '0';

    // Count valid digits smaller than the current digit.
    bool valid_digit = false;
    int smaller = 0;

    for (int i = 0; i < size; i++)
    {
      if (map[i] < curr_digit)
        smaller++;

      if (map[i] == curr_digit)
        valid_digit = true;
    }

    // Count the possible completions for each smaller digit.
    int total = 1;

    for (int i = left + 1; i < bound; i++)
    {
      if (len % 2 == 1 && i == bound - 1)
        total *= 3;

      else
        total *= 5;
    }
    result += smaller * total;

    // Cannot continue matching num's prefix.
    if (!valid_digit)
    {
      prefix_valid = false;
      break;
    }
  }

  // Handle the candidate whose entire left half matches num.
  if (prefix_valid)
  {
    char candidate[16];

    // Copy num.
    for (int i = 0; i < len; i++)
      candidate[i] = num[i];

    candidate[len] = '\0';

    for (int i = 0; i < len / 2; i++)
      candidate[len - 1 - i] = rotate[num[i] - '0'];

    // Include the candidate if it is <= num.
    if (strcmp(candidate, num) <= 0)
      result++;
  }

  return result;
}

/*
Return the total number of strobogrammatic numbers in [0, num] assume that num >= 0.
*/
int strobogrammatic_cumulative(char *num)
{
  int len = strlen(num);

  // Calculate total possible strobogrammtic numbers from 1 to n - 1 digits.
  int result = 0;
  for (int i = 1; i < len; i++)
    result += strobogrammatic_count(i);

  /*
    Calculate the total number of strobogrammatic numbers that:
    - Has exactly len digits AND
    - Less than or equal to num.
  */
  result += strobogrammatic_count_same_length(num, len);

  return result;
}

int is_strobogrammatic(char *num)
{
  int map[] = {'0', '1', -1, -1, -1, -1, '9', -1, '8', '6'};
  int len = strlen(num);

  for (int i = 0; i < len; i++)
  {
    int digit = num[i] - '0';
    if (map[digit] == -1 || num[len - 1 - i] != map[digit])
      return 0;
  }

  return 1;
}

int strobogrammaticInRange(char *low, char *high)
{
  /*
    - If low itself is strobogrammatic, plus 1.
    Ex: low = 69, hight = 96 -> 69, 88, 96
    f(69) = 0, 1, 8, 11, 88, 69
    f(96) = 0, 1, 8, 11, 88, 69, 88, 96
    -> f(96) - f(69) = 2 as we exclude 69.
  */
  return strobogrammatic_cumulative(high) - strobogrammatic_cumulative(low) + is_strobogrammatic(low);
}
