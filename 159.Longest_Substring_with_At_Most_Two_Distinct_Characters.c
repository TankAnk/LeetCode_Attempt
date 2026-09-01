#include <stdio.h>
#include <string.h>

int lengthOfLongestSubstringTwoDistinct(char *s)
{
  int len = strlen(s);
  if (len <= 2)
    return len;

  int result = 0, left = 0, right = 0, char_cnt = 0;
  int memo[128] = {0};

  while (right < len)
  {
    if (memo[s[right]] == 0)
      char_cnt++;

    memo[s[right]]++;

    //If more than 2 chars in current window, shrink from the left
    while (char_cnt > 2)
    {
      memo[s[left]]--;
      if(memo[s[left]] == 0)
        char_cnt--;

      left++;
    }

    result = (result < right - left + 1) ? right - left + 1 : result;
    right++;
  }

  return result;
}

int main()
{
  char *s1 = "eceba";
  char *s2 = "ccaabbb";
  char *s3 = "AaBbAABbaaaBB";
  char *s4 = "aaabbbcccccccccbbbbbaaaaac";

  printf("s1: %d\n", lengthOfLongestSubstringTwoDistinct(s1)); //3
  printf("s2: %d\n", lengthOfLongestSubstringTwoDistinct(s2)); //5
  printf("s3: %d\n", lengthOfLongestSubstringTwoDistinct(s3)); //5
  printf("s4: %d\n", lengthOfLongestSubstringTwoDistinct(s4)); //17
}

/* Longest substring, at most 2 different chars
eceba -> ece | ba
ccaabbb -> cc | aabbb
*/
