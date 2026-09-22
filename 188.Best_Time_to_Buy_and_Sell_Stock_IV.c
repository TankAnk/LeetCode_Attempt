/*
  3 2 6 5 0 3
  Buy 2, sell 6 -> 4
  Buy 0, sell 3 -> 3

  In a day:
  - Keep current state and move on
  - If holding, sell
  - If not holding, buy
*/

int solve(int curr_day, int ***memo, int *prices, int pricesSize, bool holding, int trans_cnt, int k)
{
  if (trans_cnt == k || curr_day == pricesSize)
    return 0;

  if (memo[curr_day][holding][trans_cnt] != INT_MIN)
    return memo[curr_day][holding][trans_cnt];

  int keep, transaction;
  // Keep
  keep = solve(curr_day + 1, memo, prices, pricesSize, holding, trans_cnt, k);

  // Sell
  if (holding)
    transaction = +prices[curr_day] + solve(curr_day + 1, memo, prices, pricesSize, !holding, trans_cnt + 1, k);

  // Buy
  if (!holding)
    transaction = -prices[curr_day] + solve(curr_day + 1, memo, prices, pricesSize, !holding, trans_cnt, k);

  memo[curr_day][holding][trans_cnt] = keep > transaction ? keep : transaction;
  return memo[curr_day][holding][trans_cnt];
}

int maxProfit(int k, int *prices, int pricesSize)
{
  // State memo[day][holding][transaction count]
  int ***memo = malloc(pricesSize * sizeof(*memo));
  for (int i = 0; i < pricesSize; i++)
  {
    memo[i] = malloc(2 * sizeof(**memo));
    for (int j = 0; j < 2; j++)
      memo[i][j] = malloc((k + 1) * sizeof(***memo));
  }

  for (int i = 0; i < pricesSize; i++)
    for (int j = 0; j < 2; j++)
      for (int m = 0; m <= k; m++)
        memo[i][j][m] = INT_MIN;

  int result = solve(0, memo, prices, pricesSize, 0, 0, k);

  for (int i = 0; i < pricesSize; i++)
  {
    for (int j = 0; j < 2; j++)
      free(memo[i][j]);

    free (memo[i]);
  }
  free(memo);

  return result;
}
