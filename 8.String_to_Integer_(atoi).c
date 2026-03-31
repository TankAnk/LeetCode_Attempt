#include <stdio.h>
#include <string.h>
#include <limits.h>

/*

-2^31 = -2 147 483 648 = INT_MIN
2^31 - 1 = 2 147 483 647 = INT_MAX
+: 43
-: 45
0 - 9: 48 - 57
*/

void remove_space(char *s)
{
    while (s[0] == ' ')
    {
        int i;
        for (i = 0; s[i] != '\0'; i++)
            s[i] = s[i + 1];
    }
}

int is_valid(char c, int idx)
{
    if (c == 43 || c == 45)
        if (idx == 0)
            return 1;
            
    if (48 <= c && c <= 57) return 1;
    
    return 0;
}

int myAtoi(char* s)
{
    int i, digit, result = 0;
    remove_space(s);
    
    for (i = 0; s[i] != '\0'; i++)
    {
        if (!is_valid(s[i], i))
        {
            if (s[0] == '-') result*=-1;
            return result;
        }
        digit = s[i] - '0';
        if (digit < 0) digit = 0;
        if (result > (INT_MAX - digit) / 10)
            return (s[0] == '-') ? INT_MIN : INT_MAX;
        result = result * 10 + digit;
    }
    
    if (s[0] == '-') result*=-1;
    
    return result;
}


int main()
{
    printf("%d\n", myAtoi("  -2147483647"));
    //char s[] = "  -0012a42";
    //remove_space(s);
    //s[0] = 'Z';
    //printf("%s\n", s);
    return 0;
}