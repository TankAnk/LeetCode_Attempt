char **summaryRanges(int *nums, int numsSize, int *returnSize)
{
  *returnSize = 0;
  if (numsSize == 0)
    return NULL;

  // At most numsSize ranges can exist:
  char **result = malloc(numsSize * sizeof(*result));

  // start: index of the first element in the current range.
  // end:   index immediately AFTER the current range (exclusive).
  int start = 0, end = 0;

  while (end < numsSize)
  {
    /*
    - Extend the range while the next element is 1 larger the the previous element.
    - start == end means the range is initially empty, so the first element must be included unconditionally.
    - Check INT_MAX before adding 1 to avoid signed overflow.
    */
    while (end < numsSize
          && (start == end || (nums[end - 1] != INT_MAX && nums[end - 1] + 1 == nums[end]))
          )
      end++;

    /*
    - A range containing one element is formatted as "a".
    - A range containing multiple elements is formatted as "a->b".
    - snprintf(NULL, 0, ...) calculates the required character count without writing to a destination buffer. The returned length excludes the terminating '\0'.
    */
    int len;
    if (end - 1 == start)
      len = snprintf(NULL, 0, "%d", nums[start]);
    else
      len = snprintf(NULL, 0, "%d->%d", nums[start], nums[end - 1]);

    result[*returnSize] = malloc((len + 1) * sizeof(**result));

    // snprintf() automatically appends the terminating '\0'.
    if (end - 1 == start)
      snprintf(result[*returnSize], len + 1, "%d", nums[start]);
    else
      snprintf(result[*returnSize], len + 1, "%d->%d", nums[start], nums[end - 1]);

    (*returnSize)++;

    // Start the next range at the first element not included in the current range.
    start = end;
  }

  return result;
}
