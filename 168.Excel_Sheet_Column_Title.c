#define ALPHABET_SIZE 26

int no_letter(int n)
{
  unsigned mul = 1, bound = 0;
  int cnt = 0;

  while (n > bound)
  {
    cnt++;
    mul *= ALPHABET_SIZE;
    bound += mul;
  }

  return cnt;
}

char *convertToTitle(int columnNumber)
{
  int size = no_letter(columnNumber);
  char *result = malloc((size + 1) * sizeof(*result));
  result[size] = '\0';

  for (int i = size - 1; i >= 0; i--)
  {
    columnNumber--;
    result[i] = (columnNumber % ALPHABET_SIZE) + 'A';
    columnNumber /= ALPHABET_SIZE;
  }

  return result;
}

/* ASCII: A - Z = 65 - 90
   1 letter: 1 < x <= 26^1
   2 letter: 26^1 + 1 < x <= 26^2 + 26^1
   3 letter: 26^2 + 1 < x <= 26^3 + 26^2 + 26^1
   n letter: 26^(n - 1) + 1 < x <= sum of 26^k in [1, n]
*/
