char** fullJustify(char** words, int wordsSize, int maxWidth, int* returnSize)
{
  *returnSize = 0;
  char **result = malloc(wordsSize * sizeof(*result));
  char *empty = malloc(maxWidth * sizeof(*empty));
  for (int i = 0; i < maxWidth; i++)
    empty[i] = ' ';

  int start = 0, end = 0, letter_len = 0, curr_len, gap, offset, total_space, base, extra;
  while (start < wordsSize)
  {
    while (end < wordsSize && letter_len + strlen(words[end]) + (end - start) <= maxWidth)
    {
      letter_len += strlen(words[end]);
      end++;
    }

    offset = 0;
    gap = end - start - 1;
    total_space = maxWidth - letter_len;
    result[*returnSize] = malloc((maxWidth + 1) * sizeof(**result));
    result[*returnSize][maxWidth] = '\0';

    //Handle single word line
    if (gap == 0)
    {
      curr_len = strlen(words[start]);
      memcpy(result[*returnSize], words[start], curr_len * sizeof(**result));
      memcpy(result[*returnSize] + curr_len, empty, total_space * sizeof(**result));
    }

    //Handle last line
    else if (end == wordsSize)
    {
      for (int i = 0; i <= gap; i++)
      {
        curr_len = strlen(words[start + i]);
        memcpy(result[*returnSize] + offset, words[start + i], curr_len * sizeof(**result));
        offset += curr_len;

        //Adding space after each word except for the last one
        if (i != gap)
        {
          result[*returnSize][offset] = ' ';
          offset++;
        }
      }

      memcpy(result[*returnSize] + offset, empty, (maxWidth - letter_len - gap) * sizeof(**result));
    }

    //Handle normal case
    else
    {
      //Every gap gets at least base spaces
      base = total_space / gap;
      //The first extra gaps get one additional space.
      extra = total_space % gap;

      for (int i = 0; i <= gap; i++)
      {
        curr_len = strlen(words[start + i]);
        memcpy(result[*returnSize] + offset, words[start + i], curr_len * sizeof(**result));
        offset += curr_len;

        //No space after last word
        if (i == gap)
          continue;

        if (i < extra)
        {
          memcpy(result[*returnSize] + offset, empty, (base + 1) * sizeof(**result));
          offset += (base + 1);
        }

        else
        {
          memcpy(result[*returnSize] + offset, empty, base * sizeof(**result));
          offset += base;
        }
      }
    }

    (*returnSize)++;
    start = end;
    letter_len = 0;
  }

  free(empty);
  return result;
}
