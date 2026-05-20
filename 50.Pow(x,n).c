double myPow(double x, int n) {
  if (x == 0)
    return 0;
  if (n == 0)
    return 1;
  if (x == 1 || n == 1)
    return x;
  if (x == -1)
    return (n % 2 == 0) ? 1 : -1;
  if (n == -1)
    return 1/x;

  unsigned long exp = (n > 0) ? n : -(long)n;
  /*
  x^n = (x^(n/2))^2 with n even
  x^n = x * x^(n - 1) with n odd
  With n negative, simply result = 1/result
  */
  double result = myPow(x, exp/2);
  result *= result;

  if (exp % 2 != 0)
    result *= x;
  if (n < 0)
    result = 1/result;

  return result;
}
