/*
  - A str always contains 10 char + There are only 4 possible char -> Maximum 4^10 str
  - Encode a str into an int -> Each int is unique -> essentially a hash map
  - Count the no of each unique int apprears, add to result when count is exactly 2 to avoid duplication
*/

#define MAX_SIZE 1048576

// Convert char to int
int val(char c)
{
  if (c == 'A')
    return 0;
  if (c == 'C')
    return 1;
  if (c == 'G')
    return 2;

  return 3;
}

/* For each char
   - Shift left code by 2 bits to make room for the current char
   - Add the 2-bit value of decoded current char into the 2 LSB of code
*/
int encode(const char *s, int start, int end)
{
  int code = 0;
  for (int i = start; i <= end; i++)
    code = (code << 2) | val(s[i]);

  return code;
}

char **findRepeatedDnaSequences(char *s, int *returnSize)
{
  *returnSize = 0;
  int len = strlen(s);
  if (len < 10)
    return NULL;

  unsigned char *count = calloc(MAX_SIZE, sizeof(*count));

  int capacity = 128;
  char **result = malloc(capacity * sizeof(*result));

  int start = 0, end = 9, code = 0;
  while (end < len)
  {
    // Encode first 10 char at the beginning
    if (start == 0)
      code = encode(s, start, end);

    // From the 2nd time, shift left, preserve 20 LSB and add 2 new bits
    else
      code = ((code << 2) & 0xFFFFF)| val(s[end]);

    if (count[code] < 2)
    {
      count[code]++;

      if (count[code] == 2)
      {
        if (*returnSize == capacity)
        {
          capacity *= 2;
          result = realloc(result, capacity * sizeof(*result));
        }

        result[*returnSize] = malloc(11 * sizeof(**result));
        memcpy(result[*returnSize], s + start, 10 * sizeof(**result));
        result[(*returnSize)++][10] = '\0';
      }
    }

    start++;
    end++;
  }

  free(count);

  return result;
}
