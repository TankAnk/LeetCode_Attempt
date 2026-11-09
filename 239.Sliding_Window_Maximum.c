/*
- Maintain a deque in descending order.
- When insert a new number:
    1. Remove expired elements from the front. Because it's expired duh.
    Ex: 0 1 2 3 4 5 6 7 8 9; k = 3, idx = 5
    Windows of size k that end with idx = 5 is: 3 4 5
    -> Minimum starting index of a window that end with index idx and total window size k is X such that: i - X + 1 = k -> X = i - k + 1.
    -> An index j is outside of current window size k within index i if j <= i - k.

    2. Remove smaller elements from the back. Because smaller and older elements can never become the maximum again while this larger and newer element is in the window.
    0 1 2 3 4 5 6 7
    2 5 3 4 6 1 9 7
    At i = 4 with value 6, it dominate 2, 5, 3, 4 as 6 is larger and 4 is newer.
    When i = 4 expire, i = 0 to 3 will also already expired.
    -> If j < i and nums[j] <= nums[i]:
      + nums[i] is newer so it expires later than nums[j].
      + When both are inside the same window, nums[j] cannot be the maxium.
      + Once nums[i] expires, nums[j] must have already expired.
*/

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize)
{
  *returnSize = numsSize - k + 1;

  int *result = malloc(*returnSize * sizeof(*result));

  // Queue that stores the index of the element from nums.
  int *queue = malloc(numsSize * sizeof(*queue));

  int front = 0;
  int rear = 0;

  for (int i = 0; i < numsSize; i++)
  {
    // Remove indices outside the current window.
    while (front < rear && queue[front] <= i - k)
      front++;

    // Remove smaller or equal elements from the back.
    while (front < rear && nums[queue[rear - 1]] <= nums[i])
      rear--;

    // Insert the current index.
    queue[rear++] = i;

    // Fill the result if there is a completed window.
    if (i >= k - 1)
      result[i - k + 1] = nums[queue[front]];
  }

  free(queue);
  return result;
}
