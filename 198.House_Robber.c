/*
On a house:
- Just move on, dgaf
- If the house before was robbed, skip
- If the house before was not robbed, rob this shit
*/

int solve(int **memo, int house, bool robbed_before, int *nums, int numsSize)
{
  if (house == numsSize)
    return 0;

  if (memo[house][robbed_before] != -1)
    return memo[house][robbed_before];

  int skip = solve(memo, house + 1, robbed_before, nums, numsSize);

  int move;
  if (robbed_before)
    move = solve(memo, house + 1, false, nums, numsSize);
  else
    move = +nums[house] + solve(memo, house + 1, true, nums, numsSize);

  memo[house][robbed_before] = skip > move ? skip : move;

  return memo[house][robbed_before];
}

int rob(int *nums, int numsSize)
{
  int **memo = malloc(numsSize * sizeof(*memo));
  for (int i = 0; i < numsSize; i++)
  {
    memo[i] = malloc(2 * sizeof(**memo));
    memo[i][0] = -1;
    memo[i][1] = -1;
  }

  int result = solve(memo, 0, false, nums, numsSize);

  for (int i = 0; i < numsSize; i++)
    free(memo[i]);
  free(memo);

  return result;
}
