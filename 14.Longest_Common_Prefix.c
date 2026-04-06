#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* longestCommonPrefix(char** strs, int strsSize) {
    int r, c, idx = 0;
    char tmp, *result = malloc(201 * sizeof(*result));
    for (int i = 0; i < 201; i++)
        result[i] = '\0';
        
    for (c = 0; c < 200 && strs[0][c] != '\0'; c++)
    {
        tmp = strs[0][c];
        for (r = 1; r < strsSize; r++)
        {
            if (tmp != strs[r][c])
                return result;
        }
        result[idx] = tmp;
        idx++;
    }
    
    return result;
}

int main()
{
    char **s = malloc(200 * sizeof(*s));
    for (int i = 0; i < 200; i++)
        s[i] = malloc(201 * sizeof(**s));
    strcpy(s[0], "dog");
    strcpy(s[1], "racecar");
    strcpy(s[2], "car");
    printf("\"");
    printf("%s", longestCommonPrefix(s, 3));
    printf("\"\n");
    return 0;
}