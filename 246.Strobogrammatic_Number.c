/*
- Strobogrammatic number: number that appears the same when rotated upside down.
- Single digit strobogrammatic numbers: 0, 1, 8, 6, 9

0 1 2    0 1 2
6 1 9 -> 6 1 9

0 1    1 0
1 8 -> 8 1

0 1 2 3    3 2 1 0
1 0 6 9 -> 6 9 0 1

0 1 2     2 1 0
6 1 9 --> 6 1 9

0 1 2 3 4 5    5 4 3 2 1 0
6 8 8 8 8 9 -> 6 8 8 8 8 9

0 1 2 3 4 5    5 4 3 2 1 0
6 7 1 3 8 9 -> 6 8 3 1 7 9

With string of length n:
- Character at index i after flipped will land on index n - 1 - i.
- Compare each character from 2 ends of the array.
*/

bool same_rotated(char a, char b)
{
  return (
    (a == '0' && b == '0') ||
    (a == '1' && b == '1') ||
    (a == '8' && b == '8') ||
    (a == '6' && b == '9') ||
    (a == '9' && b == '6')
    );
}

bool isStrobogrammatic(char *num)
{
  for (int i = 0, len = strlen(num); i < (len + 1) / 2; i++)
    if (!same_rotated(num[i], num[len - 1 - i]))
      return false;

  return true;
}
