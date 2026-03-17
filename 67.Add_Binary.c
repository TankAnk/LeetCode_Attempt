#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Attempt:
	- Start from the last element of EACH string, copy result of the sum of the 2 digit with the carry
	- If exceed the first element, treat the digit as 0
*/

char* addBinary(char* a, char* b) {
	int len_a = strlen(a);
	int len_b = strlen(b);
	int max_len = (len_a > len_b) ? len_a : len_b;
	
	char *sum_arr = malloc((max_len + 2) * sizeof(*sum_arr));
	if(!sum_arr) return NULL;
	sum_arr[max_len + 1] = '\0';
	
	//i for *a, j for *b
	int bit_a, bit_b, bit_sum, i = len_a - 1, j = len_b - 1, carry = 0;
	
	for (int k = max_len; k >= 0; k--)
	{
		bit_a = (i >= 0) ? a[i] - '0' : 0;
		bit_b = (j >= 0) ? b[j] - '0' : 0;
		bit_sum = bit_a + bit_b + carry;
		sum_arr[k] = (bit_sum % 2) + '0';
		carry = bit_sum/2;
		
		i--;
		j--;
	}
	
	if (sum_arr[0] == '0') memmove(sum_arr, sum_arr + 1, max_len + 1);
	return sum_arr;
}

int main()
{
	char *a = "1";
	char *b = "101";
	char *bi_sum = addBinary(a, b);
	for (int i = 0; i < strlen(bi_sum); i++)
		printf("Element %d is %c\n", i, bi_sum[i]);
	free(bi_sum);
	return 0;
}
