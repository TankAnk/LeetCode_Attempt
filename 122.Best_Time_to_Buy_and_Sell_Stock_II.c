int solve(int *prices, int size, int day, int is_holding, int **memo)
{
  if (day == size)
    return 0;

  if (memo[day][is_holding] != -1)
    return memo[day][is_holding];

  /*
  In a day, either:
    - Move on, dgaf
    - If not empty-handed, sell and move on
    - If empty-handed, hold today and move on
  */
  int keep = 0, transaction = 0;
  keep = solve(prices, size, day + 1, is_holding, memo);

  if (is_holding)
    transaction = prices[day] + solve(prices, size, day + 1, 0, memo);

  else
    transaction = -prices[day] + solve(prices, size, day + 1, 1, memo);

  return (memo[day][is_holding] = (keep > transaction ? keep : transaction));
}

int maxProfit(int *prices, int pricesSize)
{
  int **memo = malloc(pricesSize * sizeof(*memo));
  for (int i = 0; i < pricesSize; i++)
  {
    memo[i] = malloc(2 * sizeof(**memo));
    memo[i][0] = -1;
    memo[i][1] = -1;
  }

  int result = solve(prices, pricesSize, 0, 0, memo);
  for (int i = 0; i < pricesSize; i++)
    free(memo[i]);
  free(memo);
  return result;
}
