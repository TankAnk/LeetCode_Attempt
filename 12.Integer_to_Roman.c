#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROMAN 15

int count_digit(int num)
{
    if (num == 0) return 1;
    int count = 0;
    while (num > 0)
    {
        num/=10;
        count++;
    }
    return count;
}

int extract_first_digit(int num)
{
    while (num >= 10)
        num/=10;
    return num;
}

char* intToRoman(int num)
{
    char *result = malloc((MAX_ROMAN + 1) * sizeof(*result));
    int i, digit, pow = 1, no_digit = count_digit(num);
    for (i = 0; i <= MAX_ROMAN; i++)
        result[i] = '\0';
    
    for (i = 0; i < no_digit - 1; i++)
        pow*=10;
    
    i = 0;
    while (num > 0 && i < MAX_ROMAN)
    {
        digit = extract_first_digit(num);
        no_digit = count_digit(num);
        pow = 1;
        for (int j = 0; j < no_digit - 1; j++)
            pow*=10;
            
        printf("i = %d: \n", i);
        printf("    Start - Num: %d Digit: %d Pow: %d\n", num, digit, pow);
        
        
        if (digit == 4)
        {
            if (pow == 100)
            {
                result[i] = 'C';
                result[i + 1] = 'D';
                i+=2;
            }
            
            else if (pow == 10)
            {
                result[i] = 'X';
                result[i + 1] = 'L';
                i+=2;
            }
            
            else
            {
                result[i] = 'I';
                result[i + 1] = 'V';
                i+=2;
            }   
        }
        
        else if (digit == 9)
        {
            if (pow == 100)
            {
                result[i] = 'C';
                result[i + 1] = 'M';
                i+=2;
            }
            
            else if (pow == 10)
            {
                result[i] = 'X';
                result[i + 1] = 'C';
                i+=2;
            }
            
            else
            {
                result[i] = 'I';
                result[i + 1] = 'X';
                i+=2;
            } 
        }
        
        else if (digit == 5)
        {
            if (pow == 100)
            {
                result[i] = 'D';
                i++;
            }
            
            else if (pow == 10)
            {
                result[i] = 'L';
                i++;
            }
            
            else
            {
                result[i] = 'V';
                i++;
            }   
        }
        
        else if (digit == 1)
        {
            if (pow == 1000)
            {
                result[i] = 'M';
                i++;
            }
            
            else if (pow == 100)
            {
                result[i] = 'C';
                i++;
            }
            
            else if (pow == 10)
            {
                result[i] = 'X';
                i++;
            }
            
            else
            {
                result[i] = 'I';
                i++;
            }
        }
        
        else if (2 <= digit && digit <= 3)
        {
            if (pow == 1000)
            {
                for (int j = 0; j < digit; j++)
                {
                    result[i] = 'M';
                    i++;
                }
            }
            
            else if (pow == 100)
            {
                for (int j = 0; j < digit; j++)
                {
                    result[i] = 'C';
                    i++;
                }
            }
            
            else if (pow == 10)
            {
               for (int j = 0; j < digit; j++)
                {
                    result[i] = 'X';
                    i++;
                }
            }
            
            else
            {
                for (int j = 0; j < digit; j++)
                {
                    result[i] = 'I';
                    i++;
                }
            }
        }
        
        else if (6 <= digit && digit <= 8)
        {
            if (pow == 100)
            {
                result[i] = 'D';
                i++;
                num-=pow*5;
                digit = extract_first_digit(num);
               
                for (int j = 0; j < digit; j++)
                {
                    result[i] = 'C';
                    i++;
                }
            }
            
            else if (pow == 10)
            {
                result[i] = 'L';
                i++;
                num-=pow*5;
                digit = extract_first_digit(num);
                for (int j = 0; j < digit; j++)
                {
                    result[i] = 'X';
                    i++;
                }
            }
             
            else
            {
                result[i] = 'V';
                i++;
                num-=pow*5;
                digit = extract_first_digit(num);
                for (int j = 0; j < digit; j++)
                {
                    result[i] = 'I';
                    i++;
                }
            }
        }
        
        num-=digit*pow;
        printf("    End - Num: %d Digit: %d Pow: %d\n", num, digit, pow);
        printf("    %s\n", result);
    }
    
    return result;
}

int main()
{
    printf("[");
    printf("%s", intToRoman(2888));
    printf("]");

    return 0;
}