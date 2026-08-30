/* The read4 API is defined for you.
 *     int read4(char *buf4);
 */

/**
 * @param buf Destination buffer
 * @param n   Number of characters to read
 * @return    The number of actual characters read
 */
#define MAX_SIZE 1000

int read(char *buf, int n)
{
  int result = 0, remain = n;
  char tmp[4];

  while (remain > 0)
  {
    int char_read = read4(tmp);

    if (char_read == 0)
      return result;

    else if (char_read < remain)
    {
      memcpy(buf + result, tmp, char_read * sizeof(*buf));
      remain -= char_read;
      result += char_read;
    }

    else if (char_read >= remain)
    {
      memcpy(buf + result, tmp, remain * sizeof(*buf));
      result += remain;
      return result;
    }
  }
}
