int** merge(int** intervals, int intervalsSize, int intervalsColSize, int* returnSize) {
  *returnSize = 0;
  int *remove = calloc(intervalsSize, sizeof(*remove));
  int remove_count = 0;
  for (int i = 0; i < intervalsSize - 1; i++)
  {
    for (int j = i + 1; j < intervalsSize; j++)
    {
      if (!remove[i] && !remove[j])
      {
	int l1 = intervals[i][0], r1 = intervals[i][1];
	int l2 = intervals[j][0], r2 = intervals[j][1];

	if (r1 < l2 || r2 < l1)
	  continue;

	else
	{
	  intervals[i][0] = (l1 < l2) ? l1 : l2;
	  intervals[i][1] = (r1 > r2) ? r1 : r2;
	  remove_count++;
	  remove[j] = 1;
	}
      }
    }
  }

  *returnSize = intervalsSize - remove_count;

  int **result = malloc(*returnSize * sizeof(*result));
  for (int i = 0; i < *returnSize; i++)
    result[i] = malloc(intervalsColSize * sizeof(**result));

  int idx = 0;
  for (int i = 0; i < intervalsSize; i++)
    if (!remove[i])
      memcpy(result[idx++], intervals[i], intervalsColSize * sizeof(**result));

  free(remove);

  return result;
}

int** insert(int** intervals, int intervalsSize, int* intervalsColSize, int* newInterval, int newIntervalSize, int* returnSize, int** returnColumnSizes) {
  if (intervalsSize == 0)
  {
    *returnSize = 1;
    *returnColumnSizes = malloc(*returnSize * sizeof(**returnColumnSizes));
    (*returnColumnSizes)[0] = 2;
    int **result = malloc(sizeof(*result));
    result[0] = malloc(2 * sizeof(**result));
    result[0][0] = newInterval[0];
    result[0][1] = newInterval[1];
    return result;
  }

  int insert = intervalsSize;
  for (int i = 0; i < intervalsSize && insert == intervalsSize; i++)
    if (intervals[i][0] >= newInterval[0])
      insert = i;

  int **tmp = malloc((intervalsSize + 1) * sizeof(*tmp));
  for (int i = 0; i < intervalsSize + 1; i++)
    tmp[i] = malloc(intervalsColSize[0] * sizeof(**tmp));
  for (int i = 0, j = 0; i < intervalsSize + 1; i++)
  {
    if (i == insert)
    {
      tmp[i][0] = newInterval[0];
      tmp[i][1] = newInterval[1];
    }

    else
    {
      tmp[i][0] = intervals[j][0];
      tmp[i][1] = intervals[j][1];
      j++;
    }
  }

  int **result = merge(tmp, intervalsSize + 1, intervalsColSize[0], returnSize);

  *returnColumnSizes = malloc(*returnSize * sizeof(**returnColumnSizes));
  for (int i = 0; i < *returnSize; i++)
    (*returnColumnSizes)[i] = intervalsColSize[0];

  for (int i = 0; i < intervalsSize + 1; i++)
    free(tmp[i]);
  free(tmp);

  return result;
}
