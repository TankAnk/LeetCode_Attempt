#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void custom_merge(int **intervals, int left, int mid, int right)
{
  int s1 = mid - left + 1, s2 = right - mid;
  int L[s1][2], R[s2][2];
  for (int i = 0; i < s1; i++)
  {
    L[i][0] = intervals[left + i][0];
    L[i][1] = intervals[left + i][1];
  }

  for (int j = 0; j < s2; j++)
  {
    R[j][0] = intervals[mid + 1 + j][0];
    R[j][1] = intervals[mid + 1 + j][1];
  }

  int i = 0, j = 0, k = left;
  while (i < s1 && j < s2)
  {
    if (L[i][0] <= R[j][0])
    {
      intervals[k][0] = L[i][0];
      intervals[k][1] = L[i][1];
      i++;
    }

    else
    {
      intervals[k][0] = R[j][0];
      intervals[k][1] = R[j][1];
      j++;
    }

    k++;
  }

  while (i < s1)
  {
    intervals[k][0] = L[i][0];
    intervals[k][1] = L[i][1];
    i++;
    k++;
  }

  while (j < s2)
  {
    intervals[k][0] = R[j][0];
    intervals[k][1] = R[j][1];
    j++;
    k++;
  }
}

void custom_merge_sort(int **intervals, int left, int right)
{
  if (left < right)
  {
    int mid = left + (right - left) / 2;
    custom_merge_sort(intervals, left, mid);
    custom_merge_sort(intervals, mid + 1, right);
    custom_merge(intervals, left, mid, right);
  }
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes) {
  *returnSize = 0;
  int *remove = calloc(intervalsSize, sizeof(*remove));
  custom_merge_sort(intervals, 0, intervalsSize - 1);
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
  *returnColumnSizes = malloc(*returnSize * sizeof(**returnColumnSizes));
  for (int i = 0; i < *returnSize; i++)
    (*returnColumnSizes)[i] = intervalsColSize[0];

  int **result = malloc(*returnSize * sizeof(*result));
  for (int i = 0; i < *returnSize; i++)
    result[i] = malloc(intervalsColSize[0] * sizeof(**result));

  int idx = 0;
  for (int i = 0; i < intervalsSize; i++)
    if (!remove[i])
      memcpy(result[idx++], intervals[i], intervalsColSize[0] * sizeof(**result));

  free(remove);

  return result;
}

int main() {

    int arr[][2] = {
        {1, 3},
        {2, 6},
        {8, 10},
        {8, 9},
        {9, 11},
        {15, 18},
        {2, 4},
        {16, 17}
    };

    int intervalsSize = sizeof(arr) / sizeof(arr[0]);

    int* intervals[intervalsSize];

    for (int i = 0; i < intervalsSize; i++) {
        intervals[i] = arr[i];
    }

    int intervalsColSize[intervalsSize];

    for (int i = 0; i < intervalsSize; i++) {
        intervalsColSize[i] = 2;
    }

    int returnSize;
    int* returnColumnSizes;

    int** result = merge(
        intervals,
        intervalsSize,
        intervalsColSize,
        &returnSize,
        &returnColumnSizes
    );

    printf("Merged intervals:\n");

    for (int i = 0; i < returnSize; i++) {
        printf("[%d, %d]\n", result[i][0], result[i][1]);
    }

    return 0;
}
