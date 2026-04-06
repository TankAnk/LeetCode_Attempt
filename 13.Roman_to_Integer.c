#include <stdio.h>
#include <string.h>

int romanToInt(char* s) {
    int i = 0, result = 0;
    while (s[i] != '\0')
    {
        if (s[i] == 'I')
        {
            if (s[i + 1] == 'V')
            {
                result += 4;
                i += 2;
            }
            
            else if (s[i + 1] == 'X')
            {
                result += 9;
                i += 2;
            }
            
            else
            {
                result += 1;
                i++;
            }
        }
        
        else if (s[i] == 'X')
        {
            if (s[i + 1] == 'L')
            {
                result += 40;
                i += 2;
            }
            
            else if (s[i + 1] == 'C')
            {
                result += 90;
                i += 2;
            }
            
            else
            {
                result += 10;
                i++;
            }
        }
        
        else if (s[i] == 'C')
        {
            if (s[i + 1] == 'D')
            {
                result += 400;
                i += 2;
            }
            
            else if (s[i + 1] == 'M')
            {
                result += 900;
                i += 2;
            }
            
            else
            {
                result += 100;
                i++;
            }
        }
        
        else if (s[i] == 'V')
        {
            result += 5;
            i++;
        }
        
        else if (s[i] == 'L')
        {
            result += 50;
            i++;
        }
        
        else if (s[i] == 'D')
        {
            result += 500;
            i++;
        }
        
        else
        {
            result += 1000;
            i++;
        }
        
        printf("result: %d\n", result);
    }
    
    return result;
}

int main()
{
    printf("%d\n", romanToInt("MCMXCIV"));

    return 0;
}