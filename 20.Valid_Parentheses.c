#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isValid(char* s) {
    size_t size = strlen(s);
    if (size < 2 || size % 2 != 0)
        return false;
        
    char stack[size];
    int top = -1;
    
    for (int i = 0; s[i] != '\0'; i++)
    {
        char c = s[i];
        if (c == '(' || c == '[' || c == '{')
            stack[++top] = c;
        
        else
        {
            if (top == -1)
                return false;
            
            else if (c == ')')
            {
                if (stack[top--] != '(')
                    return false;
            }
            
            else if (c == ']')
            {
                if (stack[top--] != '[')
                    return false;
            }
            
            else if (c == '}')
            {
                if (stack[top--] != '{')
                    return false;
            }
        }
    }
    
    return (top == -1);
}

int main()
{
    char s[] = "()[]{}";
    printf("%d\n", isValid(s));
    
    return 0;
}