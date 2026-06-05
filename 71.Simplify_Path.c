char* simplifyPath(char* path)
{
  int len = strlen(path);
  char *result = malloc((len + 1) * sizeof(*result));

  for (int i = 0; i < len + 1; i++)
    result[i] = '\0';

  int pth_idx = 1, res_idx = 0, letter_count, dot_count, start;
  while (pth_idx < len)
  {
    letter_count = 0;
    dot_count = 0;

    while (pth_idx < len && path[pth_idx] == '/')
      pth_idx++;

    if (pth_idx >= len)
      break;

    start = pth_idx;
    while (pth_idx < len && path[pth_idx] != '/')
    {
      if (path[pth_idx] == '.')
        dot_count++;
      else
        letter_count++;

      pth_idx++;
    }

    // Valid path name
    if (letter_count > 0 || dot_count >= 3)
    {
      result[res_idx++] = '/';

      for (int i = start; i < pth_idx; i++)
        result[res_idx++] = path[i];
    }

    // Go back to parent directory
    else if (letter_count == 0 && dot_count == 2)
    {
      if (res_idx > 0)
      {
        res_idx--;

        while (res_idx > 0 && result[res_idx] != '/')
          res_idx--;
      }
    }

    // Single dot --> do nothing
  }

  char *final;
  if (res_idx == 0)
  {
    final = malloc(2 * sizeof(*final));
    final[0] = '/';
    final[1] = '\0';
    return final;
  }

  final = malloc((res_idx + 1) * sizeof(*final));
  result[res_idx] = '\0';
  memcpy(final, result, (res_idx + 1) * sizeof(*final));
  free(result);
  return final;
}
