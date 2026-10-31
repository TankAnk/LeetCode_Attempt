/*
For number x:
0-9: 1
Total: 1

For number xx:
10-19: Count(0-9) + 10 = 11
20-29: Count(0-9) + 0 = 1
30-39: Count(0-9) + 0 = 1
...
90-99: Count(0-9) + 0 = 1
Total: 19 + 1 = 20

For number 1xx:
100-109: Count(00-09) + 10 = 11
110-119: Count(10-19) + 10 = 21
120-129: Count(20-29) + 10 = 11
...
190-199: Count(90-99) + 10 = 11
Total: 120 + 19 + 1 = 140

For number 2xx:
200-209: Count(00-09) + 0 = 1
210-219: Count(10-19) + 0 = 11
220-229: Count(20-29) + 0 = 1
...
290-299: Count(90-99) + 0 = 1
Total: 20 + 120 + 19 + 1 = 160

For number 3xx:
300-309: Count(00-09) + 0 = 1
310-319: Count(10-19) + 0 = 11
320-329: Count(20-29) + 0 = 1
...
390-399: Count(90-99) + 0 = 1
Total: 20 + 20 + 120 + 19 + 1 = 180

...............................
For number 9xx:
Total: 20 + 20 + 20 + 20 + 20 + 20 + 20 + 20 + 120 + 19 + 1 = 300

For number 1xxx:
1000-1999: Count(000-999) + 1000 = 1300
Total: 1300 + 20 + 20 + 20 + 20 + 20 + 20 + 20 + 20 + 120 + 19 + 1 = 1600

For number 2xxx:
2000-2999: Count(000-999) + 0 = 300
Total: 300 + 1300 + 20 + 20 + 20 + 20 + 20 + 20 + 20 + 20 + 120 + 19 + 1 = 1900
*/

/*
- If factor f is the place value (1, 10, 100, 1000,...) -> In every complete cycle of length 10f, the digit 1 appears exactly f times at that position.
Example:
+ f = 1 -> A complete cycle has 10 numbers (0-9) -> Digit 1 appear 1 time on position f.
+ f = 10 -> A complete cycle has 100 numbers (00-99) -> Digit 1 appear 10 times on position f.
+ f = 100 -> A complete cycle has 1000 numbers (000-999) -> Digit 1 appear 100 times on position f.

- At every position, check the upper, current digit and lower and count how many times digit 1 have appeared ON THIS POSITION:
  + upper: how many complete cycles passed.
  + current digit: curret digit duh.
  + lower: how far of the progress within the current block.
Example: n = 2345, factor = 100 -> 2|3|45

- If the current digit is 0:
  + We haven't completed the block in which the current digit equals 1.
  + We can only count the occurrences from the complete cycles that we've already passed.
  + Each complete cycle contributes exactly factor occurrences of digit 1 at this position.
  + Total: upper * factor.

- If the current digit is 1:
  + Just like when the current digit is 0.
  + However we've entered the block where the current digit is 1.
  + Within this block, the digit 1 has appeared for every number from the beginning of the block up to the current number.
  + Total: upper * factor + lower + 1.

- If the current digit is 2-9:
  + All higher complete cycles contribute upper * factor.
  + The current cycle has already passed the entire block where the digit was 1 which contributes another factor occurrences.
  + Total: upper * factor + factor = (upper + 1) * factor.
*/

int countDigitOne(int n)
{
  int result = 0;
  unsigned long factor = 1;

  while (factor <= (unsigned long)n)
  {
    unsigned long upper = n / (factor * 10);
    unsigned long curr_digit = (n / factor) % 10;
    unsigned long lower = n % factor;

    if (curr_digit == 0)
      result += upper * factor;

    else if (curr_digit == 1)
      result += upper * factor + lower + 1;

    else
      result += (upper + 1) * factor;

    factor *= 10;
  }

  return result;
}
