void dfs(char* digits, char **result, const char map[8][5], char *current, int pos, int *idx, int *fail)
{
    if (digits[pos] == '\0')
    {
        current[pos] = '\0';
        result[*idx] = malloc((pos + 1) * sizeof(**result));
        if (!result[*idx])
        {
            for (int i = 0; i < *idx; i++)
                free(result[i]);
            *fail = 1;
            return;
        }
        strcpy(result[*idx], current);
        (*idx)++;
        return;
    }
    
    int cur_row = digits[pos] - '2';
    for (int i = 0; map[cur_row][i] != '\0' && !(*fail); i++)
    {
        current[pos] = map[cur_row][i];
        dfs(digits, result, map, current, pos + 1, idx, fail);
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** letterCombinations(char* digits, int* returnSize) {
    if (digits[0] == '\0')
    {
        *returnSize = 0;
        return NULL;
    }

    const char map[8][5] = {
        "abc",
        "def",
        "ghi",
        "jkl",
        "mno",
        "pqrs",
        "tuv",
        "wxyz"
    };
    
    int result_row = 1;
    for (int i = 0; digits[i] != '\0'; i++)
    {
        if (digits[i] == '7' || digits[i] == '9')
            result_row *= 4;
            
        else
            result_row *= 3;
    }
    
    *returnSize = result_row;
    char **result = malloc(result_row * sizeof(*result));  
    if (!result) return NULL;
    
    int idx = 0, fail = 0;
    char current[5];
    dfs(digits, result, map, current, 0, &idx, &fail);
    if (fail)
    {
        free(result);
        return NULL;
    }
    
    return result;
}