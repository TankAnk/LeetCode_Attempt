int solve(int *nums, int numsSize, int house, bool robbed_prev_house, int **memo)
{
  if (house >= numsSize)
    return 0;

  if (memo[house][robbed_prev_house] != -1)
    return memo[house][robbed_prev_house];

  // Keep this state.
  int keep = solve(nums, numsSize, house + 1, false, memo);

  int act = 0;
  // If the previous house is not robbed, we might rob this house.
  if (!robbed_prev_house)
    act = nums[house] + solve(nums, numsSize, house + 1, true, memo);

  memo[house][robbed_prev_house] = keep > act ? keep : act;

  return memo[house][robbed_prev_house];
}

/*
Explore from house 0 to n - 2 AND house 1 to n - 1 to avoid complexity.
*/
int rob(int *nums, int numsSize)
{
  if (numsSize == 0)
    return 0;

  if (numsSize == 1)
    return nums[0];

  int **memo = malloc(numsSize * sizeof(*memo));
  for (int i = 0; i < numsSize; i++)
  {
    memo[i] = malloc(2 * sizeof(**memo));
    memo[i][0] = -1;
    memo[i][1] = -1;
  }

  int c1 = solve(nums, numsSize - 1, 0, 0, memo);
  for (int i = 0; i < numsSize; i++)
  {
    memo[i][0] = -1;
    memo[i][1] = -1;
  }
  int c2 = solve(nums + 1, numsSize - 1, 0, 0, memo);

  for (int i = 0; i < numsSize; i++)
    free(memo[i]);
  free(memo);

  return (c1 > c2 ? c1 : c2);
}
