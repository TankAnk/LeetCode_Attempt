#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char* convert(char* s, int numRows) {
    int len = strlen(s);
    
    if (numRows == 1 || len <= numRows)
        return s;

    char **rows = malloc(numRows * sizeof(*rows));
    for (int i = 0; i < numRows; i++)
        rows[i] = malloc(len * sizeof(**rows));

    int *col_size = calloc(numRows, sizeof(*col_size));    

    int r = 0;
    int going_down = 1;

    for (int i = 0; i < len; i++)
    {
        rows[r][col_size[r]] = s[i];
        col_size[r]++;

        if (going_down)
        {
            if (r == numRows - 1)
            {
                going_down = 0;
                r--;
            }
            
            else
            {
                r++;
            }
        }

        else 
        {
            if (r == 0)
            {
                going_down = 1;
                r++;
            }
            
            else
            {
                r--;
            }
        }
    }

    char *result = malloc(len + 1);
    int k = 0;

    for (int i = 0; i < numRows; i++)
        for (int j = 0; j < col_size[i]; j++) 
            result[k++] = rows[i][j];

    result[k] = '\0';

    for (int i = 0; i < numRows; i++)
        free(rows[i]);

    free(rows);
    free(col_size);

    return result;
}

int main()
{
    char s[] = "ABCDE";
    printf("%s\n", convert(s, 3));
    return 0;
}