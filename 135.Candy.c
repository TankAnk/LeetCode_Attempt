int candy(int* ratings, int ratingsSize)
{
  if (ratingsSize == 0)
    return 0;

  int result = 1;
  int up = 0, down = 0, peak = 0;

  for (int i = 1; i < ratingsSize; i++)
  {
    if (ratings[i] > ratings[i - 1])
    {
      up++;
      down = 0;
      peak = up;
      result += 1 + up;
    }

    else if (ratings[i] == ratings[i - 1])
    {
      up = 0;
      down = 0;
      peak = 0;
      result += 1;
    }

    else
    {
      down++;
      up = 0;
      result += down;

      // If downhill deeper than uphill peak, the peak child needs 1 more candy to stay taller than the downhill child.
      if (down > peak)
        result += 1;
    }
  }

  return result;
}
