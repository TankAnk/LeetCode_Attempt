/*3D Top-down
int solve(int *prices, int size, int day, int holding, int count, int ***memo)
{
  if (day >= size || count >= 2)
    return 0;

  if (memo[day][holding][count] != -1)
    return memo[day][holding][count];

  //On a day, either:
  //  - Move on, dgaf
  //  - If empty-handed & count < 2, buy today
  //  - If holding & count < 2, sell

  int move = solve(prices, size, day + 1, holding, count, memo);
  int buy = 0, sell = 0;
  if (!holding)
    buy = -prices[day] + solve(prices, size, day + 1, 1, count, memo);

  if (holding)
    sell = prices[day] + solve(prices, size, day + 1, 0, count + 1, memo);

  if (move > buy)
    buy = move;

  memo[day][holding][count] = (buy > sell) ? buy : sell;
  return memo[day][holding][count];
}

int resultProfit(int *prices, int pricesSize)
{
  //memo[day][holding][count];
  int ***memo = malloc(pricesSize * sizeof(*memo));
  for (int i = 0; i < pricesSize; i++)
  {
    memo[i] = malloc(2 * sizeof(**memo));
    for (int j = 0; j < 2; j++)
    {
      memo[i][j] = malloc(3 * sizeof(***memo));
      for (int k = 0; k < 3; k++)
        memo[i][j][k] = -1;
    }
  }

  int result = solve(prices, pricesSize, 0, 0, 0, memo);
  for (int i = 0; i < pricesSize; i++)
  {
    for (int j = 0; j < 2; j++)
      free (memo[i][j]);

    free(memo[i]);
  }
  free(memo);

  return result;
}
*/

//3D Bottom-up
int maxProfit(int *prices, int pricesSize)
{
  const int INVALID = INT_MIN / 2;
  //memo[day][holding][count];
  int memo[pricesSize][2][3];
  memo[0][0][0] = 0;
  memo[0][1][0] = -prices[0];
  for (int hold = 0; hold < 2; hold++)
  {
    for (int count = 1; count < 3; count++)
      memo[0][hold][count] = INVALID;
  }

  for (int day = 1; day < pricesSize; day++)
  {
    //Today no hold, no trans = only yesterday same state
    memo[day][0][0] = memo[day - 1][0][0];
    //Today no hold, 1 trans = max(yesterday same VS today sell, yesterday buy w/ no trans)
    memo[day][0][1] = (memo[day - 1][0][1] > prices[day] + memo[day - 1][1][0]) ? memo[day - 1][0][1] : prices[day] + memo[day - 1][1][0];
    //Today no hold, 2 trans = max(yesterday same VS today sell, yester day buy w/ 1 trans)
    memo[day][0][2] = (memo[day - 1][0][2] > prices[day] + memo[day - 1][1][1]) ? memo[day - 1][0][2] : prices[day] + memo[day - 1][1][1];

    //Today hold, no trans = max(yesterday same VS today buy, yesterday no hold w/ no trans)
    memo[day][1][0] = (memo[day - 1][1][0] > -prices[day] + memo[day - 1][0][0]) ? memo[day - 1][1][0] : -prices[day] + memo[day - 1][0][0];
    //Today hold, 1 trans = max(yesterday same VS today buy, yesterday no hold w/ 1 trans)
    memo[day][1][1] = (memo[day - 1][1][1] > -prices[day] + memo[day - 1][0][1]) ? memo[day - 1][1][1] : -prices[day] + memo[day - 1][0][1];
    //Today hold, 2 trans = INVALID
    memo[day][1][2] = INVALID;
  }

  int result = memo[pricesSize - 1][0][0];
  if (memo[pricesSize - 1][0][1] > result)
    result = memo[pricesSize - 1][0][1];
  return (result > memo[pricesSize - 1][0][2] ? result : memo[pricesSize - 1][0][2]);
}
