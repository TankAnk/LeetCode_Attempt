int find_max(int n1, int n2, int n3)
{
  if (n1 < n2)
    n1 = n2;

  if (n1 < n3)
    n1 = n3;

  return n1;
}

int find_min(int n1, int n2, int n3)
{
  if (n1 > n2)
    n1 = n2;

  if (n1 > n3)
    n1 = n3;

  return n1;
}

int maxProduct(int *nums, int numsSize)
{
  int result = nums[0];
  int local_max = nums[0], local_min = nums[0];
  for (int i = 1; i < numsSize; i++)
  {
    int prod1 = nums[i] * local_max;
    int prod2 = nums[i] * local_min;
    local_max = find_max(nums[i], prod1, prod2);
    local_min = find_min(nums[i], prod1, prod2);

    if (result < local_max)
      result = local_max;

    if (nums[i] == 0)
    {
      local_max = 0;
      local_min = 0;
    }
  }

  return result;
}
