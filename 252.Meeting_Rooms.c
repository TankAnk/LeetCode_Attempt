#include <stdio.h>
#include <stdbool.h>

/*
- You are given an array of meeting time intervals where each interval consists of a start time and an end time, represented as intervals[i] = [starti, endi].
- Determine if a person could attend all meetings. Return true if a person can attend all meetings. Otherwise, return false.

Example 1:
Input: intervals = [[0,30],[5,10],[15,20]]
Output: false

Example 2:
Input: intervals = [[7,10],[2,4]]
Output: true

Example 3:
Input: intervals = [[1,1000000],[1,2],[1,3],[1,999999]]
Output: false

Example 4:
Input: intervals = [[0,100],[1,100],[2,100],[99,100]]
Output: false

Example 5:
Input: intervals = [[50,60],[1,5],[20,30],[4,10],[70,80],[10,20]]
Output: false

Constraints:
- 0 <= intervals.length <= 10^4
- intervals[i].length == 2;
- 0 <= start i < end i <= 10^6
*/

// Sort intervals by start time.
void quick_sort2D(int **arr, int left, int right)
{
  if (left >= right)
    return;

  int i = left;
  int j = right;
  int pivot = arr[left + (right - left) / 2][0];

  while (i <= j)
  {
    while (arr[i][0] < pivot)
      i++;

    while (arr[j][0] > pivot)
      j--;

    if (i <= j)
    {
      int tmp[] = {arr[i][0], arr[i][1]};
      arr[i][0] = arr[j][0];
      arr[i][1] = arr[j][1];
      arr[j][0] = tmp[0];
      arr[j][1] = tmp[1];

      i++;
      j--;
    }
  }

  if (left < j)
    quick_sort2D(arr, left, j);

  if (i < right)
    quick_sort2D(arr, i, right);
}

bool canAttendMeetings(int **intervals, int intervalsSize, int *intervalsColSize)
{
  if (intervalsSize <= 1)
    return true;

  quick_sort2D(intervals, 0, intervalsSize - 1);

  // If the next meeting starts before the previous meeting ends,
  // return false.
  for (int i = 0; i < intervalsSize - 1; i++)
    if (intervals[i + 1][0] < intervals[i][1])
      return false;

  return true;
}

int main(void) {
  int intervalsSize = 6;

  int data[6][2] = {
    {50, 60},
    {1, 5},
    {20, 30},
    {4, 10},
    {70, 80},
    {10, 20}
  };

  int* intervals[6];
  int intervalsColSize[6];

  for (int i = 0; i < intervalsSize; i++) {
    intervals[i] = data[i];
    intervalsColSize[i] = 2;
  }

  bool result = canAttendMeetings(
    intervals,
    intervalsSize,
    intervalsColSize
    );

  for (int i = 0; i < intervalsSize; i++)
  {
    for (int j = 0; j < intervalsColSize[i]; j++)
      printf("%d ", intervals[i][j]);

    printf("\n");
  }

  printf("Result: %s\n", result ? "true" : "false");

  return 0;
}
