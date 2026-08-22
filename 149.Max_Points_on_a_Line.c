#define MAX_SIZE 307

typedef struct Slope
{
  int dx;
  int dy;
  int cnt;
} Slope;

int cal_gcd(int x, int y)
{
  if (x < 0)
    x = -x;
  if (y < 0)
    y = -y;

  while (y != 0)
  {
    int tmp = y;
    y = x % y;
    x = tmp;
  }

  return x;
}

int hash_slope(int dx, int dy)
{
  unsigned int hash = (unsigned int)dx * 1000003u ^ (unsigned int)dy * 9176u;

  return hash % MAX_SIZE;
}

int maxPoints(int **points, int pointsSize, int *pointsColSize)
{
  if (pointsSize <= 2)
    return pointsSize;

  int result = 0;

  for (int i = 0; i < pointsSize; i++)
  {
    Slope table[MAX_SIZE] = {0};
    int max = 1;

    for (int j = 0; j < pointsSize; j++)
    {
      if (i == j)
        continue;

      int dx = points[j][0] - points[i][0];
      int dy = points[j][1] - points[i][1];

      int gcd = cal_gcd(dx, dy);

      dx /= gcd;
      dy /= gcd;

      if (dx <= 0)
      {
        dx = -dx;
        dy = -dy;
      }

      int idx = hash_slope(dx, dy);
      while (table[idx].cnt != 0)
      {
        if (table[idx].dx == dx && table[idx].dy == dy)
        {
          table[idx].cnt++;

          if (max < table[idx].cnt)
            max = table[idx].cnt;

          break;
        }

        idx = (idx + 1) % MAX_SIZE;
      }

      if (table[idx].cnt == 0)
      {
        table[idx].dx = dx;
        table[idx].dy = dy;
        table[idx].cnt = 1;
      }
    }

    if (result < max + 1)
      result = max + 1;
  }

  return result;
}
