typedef struct Bucket
{
  int max;
  int min;
  bool is_empty;
} Bucket;


int maximumGap(int *nums, int numsSize)
{
  if (numsSize < 2)
    return 0;

  //1. Find low and high
  int low = nums[0], high = nums[0];
  for (int i = 1; i < numsSize; i++)
  {
    if (low > nums[i])
      low = nums[i];
    if (high < nums[i])
      high = nums[i];
  }

  //Duplicated array -> gap = 0
  if (low == high)
    return 0;

  //2. Create empty buckets
  Bucket buckets[numsSize];
  for (int i = 0; i < numsSize; i++)
    buckets[i].is_empty = true;

  //3. Calculate bucket size = ceil(high - low / number of buckets)
  int bucket_size = (high - low + numsSize - 2) / (numsSize - 1);

  //4. Put numbers into buckets
  for (int i = 0; i < numsSize; i++)
  {
    int bucket_idx = (nums[i] - low) / bucket_size;
    if (buckets[bucket_idx].is_empty)
    {
      buckets[bucket_idx].is_empty = false;
      buckets[bucket_idx].max = nums[i];
      buckets[bucket_idx].min = nums[i];
    }

    else
    {
      if (nums[i] < buckets[bucket_idx].min)
        buckets[bucket_idx].min = nums[i];

      if (nums[i] > buckets[bucket_idx].max)
        buckets[bucket_idx].max = nums[i];
    }
  }

  //5. Find maximum gap
  int result = 0, prev_max = low;
  for (int i = 0; i < numsSize; i++)
  {
    if (buckets[i].is_empty)
      continue;

    int gap = buckets[i].min - prev_max;
    if (result < gap)
      result = gap;

    prev_max = buckets[i].max;
  }

  return result;
}
