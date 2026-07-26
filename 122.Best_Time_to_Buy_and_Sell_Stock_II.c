/*2D Top-down
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
*/

//2D Bottom-up
int maxProfit(int *prices, int pricesSize)
{
  int memo[pricesSize][2];
  memo[0][0] = 0;
  memo[0][1] = -prices[0];

  for (int day = 1; day < pricesSize; day++)
  {
    //Empty-handed today = max(empty-handed yesterday VS sell today, hold yesterday)
    memo[day][0] = (memo[day - 1][0] > prices[day] + memo[day - 1][1]) ? memo[day - 1][0] : prices[day] + memo[day - 1][1];

    //Hold today = max(hold yesterday VS buy today, empty-handed yesterday)
    memo[day][1] = (memo[day - 1][1] > -prices[day] + memo[day - 1][0]) ? memo[day - 1][1] : -prices[day] + memo[day - 1][0];
  }

  return memo[pricesSize - 1][0];
}
