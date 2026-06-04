#define BOUND 46340

int mySqrt(int x)
{
  if (x == 0 || x == 1)
    return x;

  int left = 2, mid;
  int right = (x / 2 < BOUND) ? x / 2 : BOUND;
  while (left <= right)
  {
    mid = left + (right - left) / 2;
    if (mid * mid == x)
      return mid;

    else if (mid * mid > x)
      right = mid - 1;

    else
      left = mid + 1;
  }

  return right;
}
