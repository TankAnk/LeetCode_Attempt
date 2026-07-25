//7 1 5 3 6 4
int maxProfit(int *prices, int pricesSize)
{
  int result = 0, min = prices[0];
  for (int i = 0; i < pricesSize; i++)
  {
    if (prices[i] < min)
      min = prices[i];

    else if (prices[i] - min > result)
      result = prices[i] - min;
  }

  return result;
}
