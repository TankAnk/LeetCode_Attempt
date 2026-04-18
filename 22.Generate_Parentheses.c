#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **backtrack(int n, int *ans_count, int idx, int num_open, int num_close, char *curr_str, char **result)
{
    if (num_open > n || num_close > n || num_close > num_open)
        return result;
        
    else if (num_open == num_close && num_open == n)
    {
        (*ans_count)++;
        result = realloc(result, *ans_count * sizeof(*result));
        result[*ans_count - 1] = malloc((2 * n + 1) * sizeof(**result));
        strcpy(result[*ans_count - 1], curr_str);
        return result;
    }
    
    idx++;
    curr_str[idx] = '(';
    result = backtrack(n, ans_count, idx, num_open + 1, num_close, curr_str, result);
    
    curr_str[idx] = ')';
    result = backtrack(n, ans_count, idx, num_open, num_close + 1, curr_str, result);
    
    return result;
}

char** generateParenthesis(int n, int* returnSize) {
    *returnSize = 0;
    char **result = NULL;
    char *curr_str = malloc((2 * n + 1) * sizeof(*curr_str));
    curr_str[2*n] = '\0';
    result = backtrack(n, returnSize, -1, 0, 0, curr_str, result);
    free(curr_str);
    return result;
}
