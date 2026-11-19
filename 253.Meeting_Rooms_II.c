/*
- Given an array of meeting time intervals intervals where intervals[i] = [start_i, end_i], return the minimum number of conference rooms required.

Example 1:
Input: intervals = [[0,30],[5,10],[15,20]]
Output: 2
Explanation: The meeting [0,30] overlaps with both [5,10] and [15,20], so two conference rooms are needed.

Example 2:
Input: intervals = [[7,10],[2,4]]
Output: 1
Explanation: The meetings do not overlap, so only one conference room is needed.

Example 3:
Input: intervals = [[1, 5], [2, 6], [3, 7], [4, 8]];
Output: 4

Constraints:
- 1 <= intervals.length <= 10^4
- 0 <= start_i < end_i <= 10^6
*/
#include <stdio.h>
#include <stdlib.h>

#define COL_SIZE 2

void merge(int *arr, int left, int mid, int right)
{
  int left_size = mid - left + 1;
  int right_size = right - mid;
  int left_arr[left_size];
  int right_arr[right_size];

  for (int i = 0; i < left_size; i++)
    left_arr[i] = arr[left + i];

  for (int i = 0; i < right_size; i++)
    right_arr[i] = arr[mid + 1 + i];

  int i = 0, j = 0, k = left;
  while (i < left_size && j < right_size)
  {
    if (left_arr[i] <= right_arr[j])
      arr[k++] = left_arr[i++];

    else
      arr[k++] = right_arr[j++];
  }

  while (i < left_size)
    arr[k++] = left_arr[i++];
}

void merge_sort(int *arr, int left, int right)
{
  if (left < right)
  {
    int mid = left + (right - left) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}

int minMeetingRooms(int **intervals, int intervalsSize, int *intervalsColSize)
{
  if (intervalsSize <= 1)
    return intervalsSize;

  int start[intervalsSize];
  int end[intervalsSize];
  for (int i = 0; i < intervalsSize; i++)
  {
    start[i] = intervals[i][0];
    end[i] = intervals[i][1];
  }

  merge_sort(start, 0, intervalsSize - 1);
  merge_sort(end, 0, intervalsSize - 1);

  /*
  for (int i = 0; i < intervalsSize; i++)
  {
    for (int j = 0; j < COL_SIZE; j++)
      printf("%d ", intervals[i][j]);

    printf("\n");
  }
  */

  /*
    start: Points to the next meeting that hasn't started yet.
    end: Points to the earliest meeting that hasn't finished yet.
    need: Number of currently occupied rooms.
    result: Maximum number of rooms occupied simultaneously.
  */
  int result = 0;
  int need = 0;
  int start_ptr = 0;
  int end_ptr = 0;

  /*
    start = {0, 5, 15};
    end   = {10, 20, 30};

    If a meeting starts, need 1 extra room.
    If a meeting ends, remove 1 room.
  */
  while (start_ptr < intervalsSize && end_ptr < intervalsSize)
  {
    if (start[start_ptr] < end[end_ptr])
    {
      need++;
      start_ptr++;
    }

    else
    {
      result = (result > need) ? result : need;
      need--;
      end_ptr++;
    }
  }

  result = (result > need) ? result : need;

  return result;
}

int main(void) {
    // Test case 1
    int data1[][2] = {{0, 30}, {5, 10}, {15, 20}};
    int* intervals1[3];
    int cols1[] = {2, 2, 2};

    for (int i = 0; i < 3; i++)
        intervals1[i] = data1[i];

    printf("Test 1: %d\n", minMeetingRooms(intervals1, 3, cols1)); // 2

    // Test case 2
    int data2[][2] = {{7, 10}, {2, 4}};
    int* intervals2[2];
    int cols2[] = {2, 2};

    for (int i = 0; i < 2; i++)
        intervals2[i] = data2[i];

    printf("Test 2: %d\n", minMeetingRooms(intervals2, 2, cols2)); // 1

    // Test case 3
    int data3[][2] = {{1, 5}, {2, 6}, {3, 7}, {4, 8}};
    int* intervals3[4];
    int cols3[] = {2, 2, 2, 2};

    for (int i = 0; i < 4; i++)
        intervals3[i] = data3[i];

    printf("Test 3: %d\n", minMeetingRooms(intervals3, 4, cols3)); // 4

    // Test case 4
    int data4[][2] = {{1, 5}, {5, 10}, {10, 15}};
    int* intervals4[3];
    int cols4[] = {2, 2, 2};

    for (int i = 0; i < 3; i++)
      intervals4[i] = data4[i];

    printf("Test 4: %d\n", minMeetingRooms(intervals4, 3, cols4)); // 1

    // Test case 5
    int data5[][2] = {{1, 100}, {10, 90}, {20, 80}, {30, 70}, {40, 60}, {50, 55}};
    int* intervals5[6];
    int cols5[] = {2, 2, 2, 2, 2, 2};

    for (int i = 0; i < 6; i++)
      intervals5[i] = data5[i];

    printf("Test 5: %d\n", minMeetingRooms(intervals5, 6, cols5)); // 6

    // Test case 6
    int data6[][2] = {{1, 10}, {2, 9}, {10, 20}, {11, 19}, {20, 30}, {21, 29}, {30, 40}, {31, 39}};
    int* intervals6[8];
    int cols6[] = {2, 2, 2, 2, 2, 2, 2, 2};

    for (int i = 0; i < 8; i++)
      intervals6[i] = data6[i];

    printf("Test 6: %d\n", minMeetingRooms(intervals6, 8, cols6)); // 2

    // Test case 7
    int data7[][2] = {{5, 15}, {5, 10}, {5, 20}, {5, 8}, {5, 12}, {5, 25}, {5, 30}};
    int* intervals7[7];
    int cols7[] = {2, 2, 2, 2, 2, 2, 2};

    for (int i = 0; i < 7; i++)
      intervals7[i] = data7[i];

    printf("Test 7: %d\n", minMeetingRooms(intervals7, 7, cols7)); // 7

    // Test case 8
    int data8[][2] = {{1, 4}, {2, 7}, {3, 9}, {4, 10}, {5, 11}, {6, 12}, {7, 13}, {8, 14}, {9, 15}, {10, 16}, {11, 17}, {12, 18}, {13, 19}, {14, 20}, {15, 21}, {16, 22}};
    int* intervals8[16];
    int cols8[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};

    for (int i = 0; i < 16; i++)
      intervals8[i] = data8[i];

    printf("Test 8: %d\n", minMeetingRooms(intervals8, 16, cols8)); // 9

    return 0;
}
