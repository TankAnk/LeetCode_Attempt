#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int expand(char *s, int len, int left, int right)
{
	while (left >= 0 && right < len && s[left] == s[right])
	{
		left--;
		right++;
	}
	return right - left - 1;
}

char* longestPalindrome(char* s) {
	int len_odd, len_even, start, max = 0;
	int s_len = strlen(s);
	if (len == 1) return s;
	int p[s_len];
	for (int i = 0; i < s_len; i++)
		p[i] = 1;
	for (int i = 0; i < s_len - 1; i++)
	{
		len_odd = expand(s, s_len, i, i);
		len_even = expand(s, s_len, i, i + 1);
		int curr_len = (len_odd > len_even) ? len_odd : len_even;
		p[i] = curr_len;
		if (max < curr_len)
		{
			max = curr_len;
			start = i - (curr_len - 1) / 2;
		}
	}
	
	for (int i = 0; i < s_len; i++)
		printf("%d ", p[i]);
	
	char *result = malloc((max + 1) * sizeof(*result));
	if (result == NULL) return NULL;
	result[max] = '\0';
	for (int i = 0; i < max; i++)
		result[i] = s[start + i];
		
	return result;
}

int main()
{
	char *s = longestPalindrome("abbbbz");
	printf("%s\n", s);
	free(s);

	return 0;
}
