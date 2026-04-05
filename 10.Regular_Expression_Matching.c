#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int occur(char *s, char c)
{
    for (int i = 0; s[i] != '\0'; i++)
        if (s[i] == c) return i;
        
    return -1;
}

bool isMatch(char* s, char* p) {
    // Attempt inspired by Sunny Sharma. Profile: https://leetcode.com/u/20Sunny/ 
    int m = strlen(s), n = strlen(p);
    // result[i][j] = if first i chars of s match first j chars of p
    // s[0 ... i-1] match p[0 ... j-1]?
    bool result[m + 1][n + 1];
    memset(result, false, sizeof(result));
    // Base case with 2 empty string
    result[0][0] = true;
    
    for (int j = 1; j < n + 1; j++)
        if (p[j - 1] == '*')
            result[0][j] = result[0][j - 2];
            
    for (int i = 1; i < m + 1; i++)
    {
        for (int j = 1; j < n + 1; j++)
        {
            if (s[i - 1] == p[j - 1] || p[j - 1] == '.')
                result[i][j] = result[i - 1][j - 1];
                
            else if (p[j - 1] == '*')
            {
                result[i][j] = result[i][j - 2];
                
                if (p[j - 2] == s[i - 1] || p[j - 2] == '.')
                    result[i][j] = result[j][j] || result[i - 1][j];
            }
        }
    }
    
    return result[m][n];            
}

int main()
{
    printf("%d\n", isMatch("mississippi", "mis*is*p*."));
    //printf("%d\n", strcmp("aaa", "ab*a*c*a"));
    
    return 0;
}