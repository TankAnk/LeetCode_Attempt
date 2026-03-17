#include <stdio.h>
#include <string.h>

int lengthOfLongestSubstring(char* s) {
    int last_seen[256];
    for (int i = 0; i < 256; i++) last_seen[i] = -1;
    
    int l = 0, r = 0, curr_len = 0, max_len = 0;
    for (r; r != '\0'; r++)
    {
    	unsigned char c = s[r];
    	
    	if (last_seen[c] >= l) l = last_seen[c] + 1;
    	
    	last_seen[c] = r;
    	
    	curr_len = r - l + 1;
    	if (curr_len > max_len) max_len = curr_len;
    }
    
    return max_len;
}

int main()
{
	int result = lengthOfLongestSubstring("abcabcbb");
	printf("%d\n", result);
	result = lengthOfLongestSubstring("bbbbb");
	printf("%d\n", result);
	result = lengthOfLongestSubstring("pwwkew");
	printf("%d\n", result);
	
	return 0;
}
