/* The read4 API is defined for you.
 *     int read4(char *buf4);
 */

/**
 * @param buf Destination buffer
 * @param n   Number of characters to read
 * @return    The number of actual characters read
 */

/*abcdefgh
  read(buf, 1) -> buf contains "a" but file pointer is at "e" because read4() consumed "abcd"
  read(buf, 2) -> buf contains "ef" instead of "bc"
*/
#define MAX_BUF_SIZE 4

char memo[MAX_BUF_SIZE];
int memo_pos = 0, memo_size = 0;

int read(char *buf, int n)
{
  int remain = n, result = 0;
  char tmp[MAX_BUF_SIZE];

  while (remain > 0)
  {
    int add = (memo_size - memo_pos < remain) ? memo_size - memo_pos : remain;
    if (add > 0)
    {
      memcpy(buf + result, memo + memo_pos, add * sizeof(*buf));
      memo_pos += add;
      result += add;
      remain -= add;
    }

    if (remain == 0)
      return result;

    if (memo_pos == memo_size)
      memo_pos = memo_size = 0;

    int char_read = read4(tmp);
    if (char_read == 0)
      return result;

    else if (char_read <= remain)
    {
      memcpy(buf + result, tmp, char_read * sizeof(*buf));
      remain -= char_read;
      result += char_read;
    }

    else if (char_read > remain)
    {
      memcpy(buf + result, tmp, remain * sizeof(*buf));
      result += remain;
      remain -= remain;

      int extra = char_read - remain;
      memcpy(memo, tmp + remain, extra * sizeof(*memo));
      memo_size = extra;
    }
  }

  return result;
}
