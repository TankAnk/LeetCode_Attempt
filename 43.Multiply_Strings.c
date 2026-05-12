#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_string(char **result, int result_len, char *num, int num_len)
{
  int carry = 0, result_digit, num_digit, sum;
  for (int i = result_len - 1, j = num_len - 1; i >= 0; i--, j--)
  {
    result_digit = (*result)[i] - '0';
    num_digit = (j < 0) ? 0 : num[j] - '0';
    sum = result_digit + num_digit + carry;
    (*result)[i] = sum % 10 + '0';
    carry = sum / 10;
  }
}

void add_string(char **result, int result_len, char *num, int num_len)
{
  int carry = 0, result_digit, num_digit, sum;
  for (int i = result_len - 1, j = num_len - 1; i >= 0; i--, j--)
  {
    result_digit = (*result)[i] - '0';
    num_digit = (j < 0) ? 0 : num[j] - '0';
    sum = result_digit + num_digit + carry;
    (*result)[i] = sum % 10 + '0';
    carry = sum / 10;
  }
}

char* multiply(char* num1, char* num2) {
  if (num1[0] == '0' || num2[0] == '0')
    return "0";
  
  int len1 = strlen(num1), len2 = strlen(num2);
  if (len1 == 1 && num1[0] == '1')
    return num2;

  if (len2 == 1 && num2[0] == '1')
    return num1;

  //Make sure the num1 has the longest length
  if (len1 < len2)
    return multiply(num2, num1);

  int result_len = len1 + len2;
  char *result = malloc(sizeof(*result) * (result_len + 1));
  memset(result, '0', result_len);
  result[result_len] = '\0';
  int offset = 0;
  
  for (int p2 = len2 - 1; p2 >= 0; p2--)
  {
    // 1 for '\0', 1 for extra carry case, offset for each multiply in num2 digit
    int tmp_len = len1 + 1 + offset;
    char *tmp = malloc(sizeof(*tmp) * (tmp_len + 1));
    memset(tmp, '0', tmp_len);
    tmp[tmp_len] = '\0';
    int tmp_idx = len1 + offset, carry = 0, num;
    for (int i = 0; i < offset; i++)
      tmp[tmp_idx--] = '0';
    
    for (int p1 = len1 - 1; p1 >= 0; p1--)
    {
      num = (num1[p1] - '0') * (num2[p2] - '0') + carry;
      tmp[tmp_idx--] = num % 10 + '0';
      carry = num / 10;
    }

    if (carry > 0)
      tmp[tmp_idx] = carry + '0';
    add_string(&result, result_len, tmp, tmp_len);
    offset++;
    free(tmp);
  }

  if (result[0] == '0')
    memmove(result, result + 1, result_len);

  return result;
}

int main()
{
  char num1[] = "111";
  char num2[] = "2";
  printf("%s\n", multiply(num1, num2));
  
  return 0;
}
